#include "../cross_compiler_call/cross_compiler_interface/cross_compiler_introspection.hpp"

#include <Hstring.h>
#include <string>

#include <Inspectable.h>
#include <Objbase.h>
#include <algorithm>
#include <Hstring.h>
#include <Winstring.h>
#include <wrl.h>



namespace cross_compiler_interface{

    template<>
    struct cross_conversion<HSTRING>:public trivial_conversion<HSTRING>{};

    template<>
    struct cross_conversion<TrustLevel>:public trivial_conversion<TrustLevel>{};
}

CROSS_COMPILER_INTERFACE_DEFINE_TYPE_INFORMATION(HSTRING);
CROSS_COMPILER_INTERFACE_DEFINE_TYPE_INFORMATION(TrustLevel);

namespace cc_winrt{
    using cross_compiler_interface::cross_function;
    using cross_compiler_interface::use_unknown;
    using cross_compiler_interface::use_interface;
    using cross_compiler_interface::implement_interface;
    using cross_compiler_interface::uuid;
    using cross_compiler_interface::uuid_base;
    using cross_compiler_interface::type_to_type;

    // Preserves HSTRING
    inline std::wstring WStringFromHSTRING(HSTRING h){
        if( ::WindowsIsStringEmpty(h)){
            return std::wstring();
        }
        UINT32 sz = 0;
        auto p = ::WindowsGetStringRawBuffer(h,&sz);
        std::wstring r(p,p+sz);

        return r;
    }  
    // Destructive to HSTRING
    inline std::wstring WStringFromHSTRING(HSTRING&& h){
        if( ::WindowsIsStringEmpty(h)){
            return std::wstring();
        }
        UINT32 sz = 0;
        auto p = ::WindowsGetStringRawBuffer(h,&sz);
        std::wstring r(p,p+sz);
        ::WindowsDeleteString(h);
        h = nullptr;
        return r;
    }

    inline HSTRING HSTRINGFromWString(const std::wstring& w){
        HSTRING r = nullptr;
        auto e = ::WindowsCreateString(w.c_str(),w.size(),&r);
        if(e < 0){
            cross_compiler_interface::general_error_mapper::exception_from_error_code(e);
        }
        return r;
    }

    struct unique_hstring{
        HSTRING hs_;
        unique_hstring(HSTRING h):hs_(h){}

        static HSTRING empty_string(){
            HSTRING hs;
            ::WindowsCreateString(nullptr,0,&hs);
            return hs;
        }

        HSTRING get(){return hs_;}
        HSTRING release(){
            HSTRING hs = hs_;
            hs_ = empty_string();
            return hs;
        }

        ~unique_hstring(){
            ::WindowsDeleteString(hs_);
            hs_ = empty_string();
        }
    };


    template<class WRC>
    struct RuntimeClassName{

        // std::wstring GetRuntimeClass(){return L"";}
    };

    namespace detail{
        template<class Iface,int Id>
        struct get_iids_cross_function
            :public cross_compiler_interface::custom_cross_function<Iface,Id,std::vector<cross_compiler_interface::uuid_base>(),cross_compiler_interface::error_code(cross_compiler_interface::portable_base*,ULONG*,cross_compiler_interface::uuid_base**),
            get_iids_cross_function<Iface,Id> >
        {
            std::vector<cross_compiler_interface::uuid_base*> call_vtable_function()const{
                portable_base* r = 0;
                ULONG count = 0;
                cross_compiler_interface::uuid_base* piids = 0;
                auto ret = this->get_vtable_fn()(this->get_portable_base(),&count,&piids);
                std::unique_ptr<decltype(piids)> uptr(piids,::CoTaskMemFree);
                if(ret < 0){
                    this->exception_from_error_code(ret);
                }
                if(!piids) {
                    throw cross_compiler_interface::error_pointer();
                }
                return std::vector<cross_compiler_interface::uuid_base*>(piids,piids+count);
            }
            template<class F>
            static cross_compiler_interface::error_code vtable_function(F f,cross_compiler_interface::portable_base* p,ULONG* pcount,cross_compiler_interface::uuid_base** iids){
                try{
                    if(!iids || *pcount){
                        return cross_compiler_interface::error_pointer::ec;
                    }
                    std::vector<cross_compiler_interface::uuid_base> v = f();
                    if(v.empty()){
                        *pcount = 0;
                        *iids = nullptr;
                    }
                    auto piids = static_cast<cross_compiler_interface::uuid_base*>(::CoTaskMemAlloc(v.size()*sizeof(v[0])));
                    if(!piids){
                        *pcount = 0;
                        return cross_compiler_interface::error_out_of_memory::ec;
                    }
                    std::copy(v.begin(),v.end(),piids);
                    *iids = piids;
                    *pcount = v.size();


                }
                catch(std::exception& e){
                    return cross_compiler_interface::general_error_mapper::error_code_from_exception(e);
                }
                return 0;
            }

            template<class F>
            void operator=(F f){
                this->set_function(f);

            }

            template<class T>
            get_iids_cross_function(T t):get_iids_cross_function::base_t(t){}



        };
    }

    template<class T>
    struct InterfaceInspectable:public cross_compiler_interface::define_unknown_interface<T,cross_compiler_interface::uuid<0xAF86E2E0,0xB12D,0x4c6a,0x9C,0x5A,0xD7,0xAA,0x65,0x10,0x1E,0x90>>{

        detail::get_iids_cross_function<InterfaceInspectable,0> GetIids;
        cross_function<InterfaceInspectable,1,HSTRING()> GetRuntimeClassName;
        cross_function<InterfaceInspectable,2,TrustLevel()> GetTrustLevel;

        InterfaceInspectable():GetIids(this),GetRuntimeClassName(this),GetTrustLevel(this){}

    };    
    // This interface is for use with define_inspectable_interface
    // The reason we have this is so in the derived interfaces, use of InterfaceInspectable with yield a template and not a class
    template<class T>
    struct InterfaceInspectable_:public cross_compiler_interface::define_unknown_interface<T,cross_compiler_interface::uuid<0xAF86E2E0,0xB12D,0x4c6a,0x9C,0x5A,0xD7,0xAA,0x65,0x10,0x1E,0x90>>{

        detail::get_iids_cross_function<InterfaceInspectable_,0> GetIids;
        cross_function<InterfaceInspectable_,1,HSTRING()> GetRuntimeClassName;
        cross_function<InterfaceInspectable_,2,TrustLevel()> GetTrustLevel;

        InterfaceInspectable_():GetIids(this),GetRuntimeClassName(this),GetTrustLevel(this){}

    };    

    template<class T,class uuid_type, template<class> class Base = InterfaceInspectable_ >
    struct define_inspectable_interface
        :public cross_compiler_interface::define_unknown_interface<T,uuid_type,Base>
    {


    };

    template<class Derived, template<class> class... Interfaces>
    struct implement_inspectable_interfaces:public cross_compiler_interface::implement_unknown_interfaces<Derived,Interfaces...>{

    private:



        template<template<class> class First, template<class> class... Rest>
        struct helper{


            template<class T>
            static void set_mem_functions(T* t){
                auto p = t->template get_implementation<First>();
                p->GetIids.template set_mem_fn<implement_inspectable_interfaces,
                    &implement_inspectable_interfaces::GetIids>(t);
                p->GetRuntimeClassName.template set_mem_fn<implement_inspectable_interfaces,
                    &implement_inspectable_interfaces::GetRuntimeClassName>(t);
                p->GetTrustLevel.template set_mem_fn<implement_inspectable_interfaces,
                    &implement_inspectable_interfaces::GetTrustLevel>(t);


                helper<Rest...>::set_mem_functions(t);
            }

            static void add_iids(std::vector<cross_compiler_interface::uuid_base>& v){
                auto& u = typename cross_compiler_interface::implement_interface<First>::uuid::get();
                v.push_back(u);

                helper<Rest...>::add_iids(v);
            }

        };
        template<template<class> class First>
        struct helper<First>{

            template<class T>
            static void set_mem_functions(T* t){
                auto p = t->template get_implementation<First>();
                p->GetIids.template set_mem_fn<implement_inspectable_interfaces,
                    &implement_inspectable_interfaces::GetIids>(t);
                p->GetRuntimeClassName.template set_mem_fn<implement_inspectable_interfaces,
                    &implement_inspectable_interfaces::GetRuntimeClassName>(t);
                p->GetTrustLevel.template set_mem_fn<implement_inspectable_interfaces,
                    &implement_inspectable_interfaces::GetTrustLevel>(t);

            }

            static void add_iids(std::vector<cross_compiler_interface::uuid_base>& v){
                auto& u = typename cross_compiler_interface::implement_interface<First>::uuid::get();
                v.push_back(u);
            }

        };



    public:
        std::vector<cross_compiler_interface::uuid_base> GetIids(){
            std::vector<cross_compiler_interface::uuid_base> v;
            helper<Interfaces...>::add_iids(v);
            return v;
        }

        HSTRING GetRuntimeClassName(){
            return HSTRINGFromWString(RuntimeClassName<typename Derived::runtime_class_t>::Get());
        }

        TrustLevel GetTrustLevel(){
            return Derived::GetTrustLevel();
        }

        implement_inspectable_interfaces(){
            helper<Interfaces...>::set_mem_functions(this);
        }
    };


    template<class T>
    struct InterfaceActivationFactory                     
        :public define_inspectable_interface<T,cross_compiler_interface::uuid<0x00000035,0x0000,0x0000,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46>>
    {
        cross_function<InterfaceActivationFactory,0,cross_compiler_interface::use_unknown<InterfaceInspectable>()> ActivateInstance;


        InterfaceActivationFactory():ActivateInstance(this){}
    };

    template<template<class> class DefaultInterface,template <class> class FactoryInterface,template<class> class StaticInterface, template<class> class... OtherInterfaces>
    struct winrt_runtime_class{};


    template<class Derived, class WRC>
    struct implement_winrt_runtime_class{};

    namespace detail{
        // All Factories must support IActivationFactory as baseline, plus may support more in addition to
        template<class Derived, template<class>class FactoryInterface,template<class> class StaticInterface>
        struct implement_factory_static_helper
            :public implement_inspectable_interfaces<Derived,InterfaceActivationFactory,FactoryInterface,StaticInterface>{

        };
        template<class Derived, template<class> class StaticInterface>
        struct implement_factory_static_helper<Derived,InterfaceActivationFactory,StaticInterface>
            :public implement_inspectable_interfaces<Derived,InterfaceActivationFactory,StaticInterface>{

        };
    }

    template<class Derived, template<class> class DefaultInterface, template<class> class FactoryInterface, template<class> class StaticInterface, template<class> class... Others>
    struct implement_winrt_runtime_class<Derived,winrt_runtime_class<DefaultInterface,FactoryInterface,StaticInterface,Others...>>
        :public implement_inspectable_interfaces<Derived,DefaultInterface,Others...>
    {
        typedef winrt_runtime_class<DefaultInterface,FactoryInterface,StaticInterface,Others...> runtime_class_t;
        cross_compiler_interface::implement_interface<DefaultInterface>* default_interface(){
            return this->get_implementation<DefaultInterface>();

        }

        static TrustLevel GetTrustLevel(){return TrustLevel::BaseTrust;}

        static         HSTRING GetRuntimeClassName(){
            return HSTRINGFromWString(GetRuntimeClass(runtime_class_t()));
        }



        struct implement_factory_static_interfaces
            :public detail::implement_factory_static_helper<typename Derived::ImplementFactoryStaticInterfaces,FactoryInterface,StaticInterface>{

                typedef winrt_runtime_class<DefaultInterface,FactoryInterface,StaticInterface,Others...> runtime_class_t;

                cross_compiler_interface::implement_interface<FactoryInterface>* factory_interface(){
                    return this->get_implementation<FactoryInterface>();
                }

                cross_compiler_interface::implement_interface<InterfaceActivationFactory>* activation_factory_interface(){
                    return this->get_implementation<InterfaceActivationFactory>();
                }

                cross_compiler_interface::implement_interface<StaticInterface> static_interface(){
                    return this->get_implementation<StaticInterface>();
                }

                static TrustLevel GetTrustLevel(){return TrustLevel::BaseTrust;}

                static HSTRING GetRuntimeClassName(){
                    return HSTRINGFromWString(GetRuntimeClass(runtime_class_t()));
                }
                static std::wstring GetRuntimeClass(){
                    return GetRuntimeClass(runtime_class_t());
                }

                auto activate_instance()->cc_winrt::use_unknown<cc_winrt::InterfaceInspectable>{
                    return Derived::create().QueryInterface<cc_winrt::InterfaceInspectable>();
                }
                implement_factory_static_interfaces(){

                    activation_factory_interface()->ActivateInstance.template set_mem_fn<
                        implement_factory_static_interfaces,&implement_factory_static_interfaces::activate_instance>(this);
                }

                static std::wstring get_runtime_class(){return GetRuntimeClass(runtime_class_t());}

        };
        static use_unknown<InterfaceActivationFactory> get_activation_factory(HSTRING hs){
            auto w = WStringFromHSTRING(hs);
            if(w==RuntimeClassName<runtime_class_t>::Get()){
                return implement_factory_static_interfaces::create().QueryInterface<InterfaceActivationFactory>();
            }
            else{
                return nullptr;
            }
        }
        implement_winrt_runtime_class(){

        }

    };


    template<class... Imps>
    struct get_activation_factory_helper{
        template<class... I>
        struct helper{};

        template<class First, class... Rest>
        struct helper<First,Rest...>{
            static use_unknown<InterfaceActivationFactory> get_activation_factory(HSTRING hs){
                auto r = First::get_activation_factory(hs);
                if(r){
                    return r;
                }
                else{
                    helper<Rest...>::get_activation_factory(hs);

                }
            }

        };

        template<class First>
        struct helper<First>{
            static use_unknown<InterfaceActivationFactory> get_activation_factory(HSTRING hs){
                auto r = First::get_activation_factory(hs);
                if(r){
                    return r;
                }
                else{
                    return nullptr;
                }
            }

        };
        static use_unknown<InterfaceActivationFactory> get_activation_factory(HSTRING hs){
            return helper<Imps...>::get_activation_factory(hs);
        }

    };

    template<class...Imps>
    HRESULT get_activation_factory( HSTRING activatibleClassId, IActivationFactory** factory){
        try{
            auto r = get_activation_factory_helper<Imps...>::get_activation_factory(activatibleClassId);
            if(r){
                *factory = reinterpret_cast<IActivationFactory*>(r.get_portable_base_addref());
                return S_OK;
            }
            else{
                return cross_compiler_interface::error_no_interface::ec;
            }
        }
        catch(std::exception& e){
            return cross_compiler_interface::general_error_mapper::error_code_from_exception(e);
        }
    }


    // Usage
    template<class WRC>
    struct use_winrt_runtime_class{};


    namespace detail{

        template<template<class> class... Interfaces>
        struct inherit_use_interfaces_linearly{};

        template<template<class> class First>
        struct inherit_use_interfaces_linearly<First>:public use_unknown<First>{
        };

        // MSVC Milan has a compiler crash that we can fix
        // by appending InterfaceInspectable_ to the list of interfaces to inherit from
        // This specialization filters that out
        template<>
        struct inherit_use_interfaces_linearly<InterfaceInspectable_>{
        };

        template<template<class> class First,template<class> class... Rest>
        struct inherit_use_interfaces_linearly<First,Rest...>:public use_unknown<First>,public inherit_use_interfaces_linearly<Rest...>{;

        };

        struct inspectable_holder{
            use_unknown<InterfaceInspectable> inspectable_;

            inspectable_holder(use_unknown<InterfaceInspectable> i):inspectable_(i){}

            use_unknown<InterfaceInspectable>& get_inspectable(){
                return inspectable_;
            }

        };

    }

    inline use_unknown<InterfaceActivationFactory> get_activation_factory(const std::wstring id){
        unique_hstring hs(HSTRINGFromWString(id));
        cross_compiler_interface::portable_base* paf = nullptr;
        auto e = ::RoGetActivationFactory(hs.get(),use_unknown<InterfaceActivationFactory>::uuid::get_windows_guid<GUID>(),reinterpret_cast<void**>(&paf));
        if(e < 0){
            cross_compiler_interface::general_error_mapper::exception_from_error_code(e);
        }
        use_unknown<InterfaceActivationFactory> ret(cross_compiler_interface::reinterpret_portable_base<InterfaceActivationFactory>(paf),false);
        return ret;
    }
    namespace detail{
          template<template<class> class... Interfaces>
        struct use_runtime_class_helper{};
        // MSVC Milan has a compiler crash that we can fix
        // by appending InterfaceInspectable to the list of interfaces to inherit from
        // This specialization filters that out
        template<>
        struct use_runtime_class_helper<InterfaceInspectable>{
            template<class T>
            static void set_use_unknown(T* pthis){
                // do nothing
            }
        }; 
        template<template<class> class First, template<class> class... Rest>
        struct use_runtime_class_helper<First,Rest...>{
            template<class T>
            static void set_use_unknown(T* pthis){
                use_unknown<First>* pfirst = pthis;
                *pfirst = pthis->as<First>();

                use_runtime_class_helper<Rest...>::set_use_unknown(pthis);
            }
        };

    }

    template<template<class> class DefaultInterface, template<class> class FactoryInterface, template<class> class StaticInterface, template<class> class... Others>
    struct use_winrt_runtime_class<winrt_runtime_class<DefaultInterface,FactoryInterface,StaticInterface,Others...>>
        :private detail::inspectable_holder,
        public detail::inherit_use_interfaces_linearly<DefaultInterface,Others...,InterfaceInspectable_>
    {
        typedef winrt_runtime_class<DefaultInterface,FactoryInterface,StaticInterface,Others...> runtime_class_t;
        cross_compiler_interface::use_unknown<DefaultInterface> default_interface(){
            return this->get_implementation<DefaultInterface>();

        } 
        template<template<class> class Interface>
        cross_compiler_interface::use_unknown<Interface> as(){
            return this->get_inspectable().QueryInterface<Interface>();
        }

        static use_unknown<InterfaceActivationFactory> activation_factory_interface(){
            static use_unknown<InterfaceActivationFactory> af_(get_activation_factory(RuntimeClassName<runtime_class_t>::Get()));
            return af_;

        }

        static use_unknown<FactoryInterface> factory_interface(){
            return activation_factory_interface().QueryInterface<FactoryInterface>();
        }

        static use_unknown<StaticInterface> static_interface(){
            return activation_factory_interface().QueryInterface<StaticInterface>();
        }

        use_winrt_runtime_class()
            :detail::inspectable_holder(activation_factory_interface().ActivateInstance())
        {
            typedef detail::use_runtime_class_helper<DefaultInterface,Others...,InterfaceInspectable> h_t;
            h_t::set_use_unknown(this);
        }

    private:
  

    };

    //namespace detail{
    //    // All Factories must support IActivationFactory as baseline, plus may support more in addition to
    //    template<class Derived, template<class>class FactoryInterface,template<class> class StaticInterface>
    //    struct use_factory_static_helper
    //        :public use_unknown<InterfaceActivationFactory>,use_unknown<FactoryInterface>,use_unknown<StaticInterface>{

    //    };
    //    template<class Derived, template<class> class StaticInterface>
    //    struct use_factory_static_helper<Derived,InterfaceActivationFactory,StaticInterface>
    //        :public implement_inspectable_interfaces<Derived,InterfaceActivationFactory,StaticInterface>{

    //    };
    //}

    //template<class Derived, template<class> class DefaultInterface, template<class> class FactoryInterface, template<class> class StaticInterface, template<class> class... Others>
    //struct implement_winrt_runtime_class<Derived,winrt_runtime_class<DefaultInterface,FactoryInterface,StaticInterface,Others...>>
    //    :public implement_inspectable_interfaces<Derived,DefaultInterface,Others...>
    //{
    //    cross_compiler_interface::implement_interface<DefaultInterface>* default_interface(){
    //        return this->get_implementation<DefaultInterface>();

    //    }

    //    static TrustLevel GetTrustLevel(){return TrustLevel::BaseTrust;}

    //    static         HSTRING GetRuntimeClassName(){
    //        return HSTRINGFromWString(Derived::GetRuntimeClass());
    //    }



    //    struct implement_factory_static_interfaces
    //        :public detail::implement_factory_static_helper<typename Derived::ImplementFactoryStaticInterfaces,FactoryInterface,StaticInterface>{
    //        cross_compiler_interface::implement_interface<FactoryInterface>* factory_interface(){
    //            return this->get_implementation<FactoryInterface>();
    //        }

    //        cross_compiler_interface::implement_interface<InterfaceActivationFactory>* activation_factory_interface(){
    //            return this->get_implementation<InterfaceActivationFactory>();
    //        }

    //        cross_compiler_interface::implement_interface<StaticInterface> static_interface(){
    //            return this->get_implementation<StaticInterface>();
    //        }

    //        static TrustLevel GetTrustLevel(){return TrustLevel::BaseTrust;}

    //        static HSTRING GetRuntimeClassName(){
    //            return HSTRINGFromWString(Derived::GetRuntimeClass());
    //        }
    //        static std::wstring GetRuntimeClass(){
    //            return Derived::GetRuntimeClass();
    //        }
    //    };
    //    static use_unknown<InterfaceActivationFactory> get_activation_factory(HSTRING hs){
    //        auto w = WStringFromHSTRING(hs);
    //        if(w==Derived::GetRuntimeClass()){
    //            return implement_factory_static_interfaces::create().QueryInterface<InterfaceActivationFactory>();
    //        }
    //        else{
    //            return nullptr;
    //        }
    //    }
    //    implement_winrt_runtime_class(){

    //    }

    //};


}


CROSS_COMPILER_INTERFACE_DEFINE_INTERFACE_INFORMATION(cc_winrt::InterfaceInspectable,GetIids,GetRuntimeClassName,GetTrustLevel);
CROSS_COMPILER_INTERFACE_DEFINE_INTERFACE_INFORMATION(cc_winrt::InterfaceActivationFactory,ActivateInstance);