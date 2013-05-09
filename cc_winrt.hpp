
#include <Inspectable.h>
#include <Objbase.h>
#include <Roapi.h> 

#include "hstring_utilities.hpp"
#include "../cross_compiler_call/cross_compiler_interface/cross_compiler_introspection.hpp"


// Allow HSTRING and TrustLevel to be used in cross_function signatures
namespace cross_compiler_interface{

    template<>
    struct cross_conversion<HSTRING>:public trivial_conversion<HSTRING>{};

    template<>
    struct cross_conversion<TrustLevel>:public trivial_conversion<TrustLevel>{};
}


// Allow introspection on those types
CROSS_COMPILER_INTERFACE_DEFINE_TYPE_INFORMATION(HSTRING);
CROSS_COMPILER_INTERFACE_DEFINE_TYPE_INFORMATION(TrustLevel);

namespace cc_winrt{


    struct unique_ro_initialize{
        unique_ro_initialize(RO_INIT_TYPE rinit = default_init()){
            auto e = ::RoInitialize(rinit);
            if(e < 0){
                cross_compiler_interface::general_error_mapper::exception_from_error_code(e);
            }
        }
        ~unique_ro_initialize(){
            ::RoUninitialize();
        }

        // Allows us to change the threading model
        // WARNING: NOT multithread safe
        static RO_INIT_TYPE& default_init(){
            static RO_INIT_TYPE init_ = RO_INIT_MULTITHREADED;
            return init_;
        }
    };

    // Use the following templates from cross_compiler_interface
    using cross_compiler_interface::cross_function;
    using cross_compiler_interface::use_unknown;
    using cross_compiler_interface::use_interface;
    using cross_compiler_interface::implement_interface;
    using cross_compiler_interface::uuid;

    typedef cross_compiler_interface::cross_compiler_interface_error_base hresult_error;
    typedef cross_compiler_interface::general_error_mapper error_mapper;

    namespace detail{

        // A custom_cross_function for GetIids. 
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
#ifdef _MSC_VER
                    std::copy(v.begin(),v.end(),stdext::checked_array_iterator<decltype(piids)>(piids,v.size()));
#else
                    std::copy(v.begin(),v.end(),piids);
#endif
                    auto p = piids;
                    for(const auto& i:v){
                        *p++ = i;
                    }
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

    // IInspectable
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

    // Define an interface derived from IInspectable
    template<class T,class uuid_type, template<class> class Base = InterfaceInspectable_ >
    struct define_inspectable_interface
        :public cross_compiler_interface::define_unknown_interface<T,uuid_type,Base>
    {


    };

    // Implement interfaces derived from IInspectable and provide implementations of IUknown and IInspectable Methods
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
            return typename Derived::runtime_class_t::get_runtime_class_name().release();
        }

        TrustLevel GetTrustLevel(){
            return Derived::GetTrustLevel();
        }

        implement_inspectable_interfaces(){
            helper<Interfaces...>::set_mem_functions(this);
        }
    };

    // IActivationFactory
    template<class T>
    struct InterfaceActivationFactory                     
        :public define_inspectable_interface<T,cross_compiler_interface::uuid<0x00000035,0x0000,0x0000,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46>>
    {
        cross_function<InterfaceActivationFactory,0,cross_compiler_interface::use_unknown<InterfaceInspectable>()> ActivateInstance;


        InterfaceActivationFactory():ActivateInstance(this){}
    };

    // Defines a winrt_runtime class
    template<hstring(*pfun_runtime_class_name)(),template<class> class DefaultInterface,template <class> class FactoryInterface,template<class> class StaticInterface, template<class> class... OtherInterfaces>
    struct winrt_runtime_class{
        static  hstring get_runtime_class_name(){
            return pfun_runtime_class_name();
        }
    };



    // Enables implementing runtime class
    template<class Derived, class WRC>
    struct implement_winrt_runtime_class{};

    namespace detail{
        // All Factories must support IActivationFactory as baseline, plus may support more in addition to IActivationFactory
        
        template<class Derived, template<class>class FactoryInterface,template<class> class StaticInterface>
        struct implement_factory_static_helper
            :public implement_inspectable_interfaces<Derived,InterfaceActivationFactory,FactoryInterface,StaticInterface>{

        };
        template<class Derived, template<class> class StaticInterface>
        struct implement_factory_static_helper<Derived,InterfaceActivationFactory,StaticInterface>
            :public implement_inspectable_interfaces<Derived,InterfaceActivationFactory,StaticInterface>{

        };

        template<template<class> class Iface, class T>
        void caster(use_unknown<Iface>& r, T& t){
            r = t.QueryInterface<Iface>();
        }


        // Helpers for using constructors to automatically map interface
        template<class CF, class F>
        struct factory_to_constructor_helper{};

        template<class CF, class R, class... Parms>
        struct factory_to_constructor_helper<CF,R(Parms...)>{
            template<class ImpFactHelper, class MPS,class Interface>

            static void set(ImpFactHelper& helper, MPS& m,Interface& i){
                auto ptm = m.get<CF>();
                (i.*ptm) = [&helper](Parms... p)->R{
                    R ret;
                    auto t = helper.activate_instance_parms(p...);
                    caster(ret,t);
                    return ret;
                };

            }
        };  

        template<class... CF>
        struct factory_to_constructor{};

        template<class First>
        struct factory_to_constructor<First>{
            template<class ImpFactHelper, class MPS,class Interface>
            static void set(ImpFactHelper& helper, MPS& m,Interface& i){
                factory_to_constructor_helper<First, typename First::function_signature>::set(helper,m,i);
            }
        };

        template<class First, class... Rest>
        struct factory_to_constructor<First,Rest...>{
            template<class ImpFactHelper, class MPS,class Interface>
            static void set(ImpFactHelper& helper, MPS& m,Interface& i){
                factory_to_constructor_helper<First, typename First::function_signature>::set(helper,m,i);
                factory_to_constructor<Rest...>::set(helper,m,i);
            }


        };

        template<class TypesList>
        struct forward_to_factory_to_constructor{};

        template<class... T>
        struct forward_to_factory_to_constructor<cross_compiler_interface::type_list<T...>>{
            typedef factory_to_constructor<T...> type;
        };

    }
    // Template to help implement a winrt runtime class
    // You inherit from this class, providing the name of your class in derived
    template<hstring(*pfun_runtime_class_name)(),class Derived, template<class> class DefaultInterface, template<class> class FactoryInterface, template<class> class StaticInterface, template<class> class... Others>
    struct implement_winrt_runtime_class<Derived,winrt_runtime_class<pfun_runtime_class_name,DefaultInterface,FactoryInterface,StaticInterface,Others...>>
        :public implement_inspectable_interfaces<Derived,DefaultInterface,Others...>
    {

        // The runtime class default interface
        typedef winrt_runtime_class<pfun_runtime_class_name,DefaultInterface,FactoryInterface,StaticInterface,Others...> runtime_class_t;
        cross_compiler_interface::implement_interface<DefaultInterface>* default_interface(){
            return this->get_implementation<DefaultInterface>();

        }

        static TrustLevel GetTrustLevel(){return TrustLevel::BaseTrust;}





        struct implement_factory_static_interfaces
            :public detail::implement_factory_static_helper<typename Derived::ImplementFactoryStaticInterfaces,FactoryInterface,StaticInterface>{

                typedef winrt_runtime_class<pfun_runtime_class_name,DefaultInterface,FactoryInterface,StaticInterface,Others...> runtime_class_t;

                cross_compiler_interface::implement_interface<FactoryInterface>* factory_interface(){
                    return this->get_implementation<FactoryInterface>();
                }

                cross_compiler_interface::implement_interface<InterfaceActivationFactory>* activation_factory_interface(){
                    return this->get_implementation<InterfaceActivationFactory>();
                }

                cross_compiler_interface::implement_interface<StaticInterface>* static_interface(){
                    return this->get_implementation<StaticInterface>();
                }

                static TrustLevel GetTrustLevel(){return TrustLevel::BaseTrust;}

                template<class... T>
                cc_winrt::use_unknown<cc_winrt::InterfaceInspectable> activate_instance_parms(T... t){
                    return Derived::create(t...).QueryInterface<cc_winrt::InterfaceInspectable>();
                }

                cc_winrt::use_unknown<cc_winrt::InterfaceInspectable> activate_instance(){
                    return Derived::create().QueryInterface<cc_winrt::InterfaceInspectable>();
                }
                implement_factory_static_interfaces(){


                    auto memp = cross_compiler_interface::type_information<cross_compiler_interface::implement_interface<FactoryInterface>>::get_ptrs_to_members();
                    typedef typename detail::forward_to_factory_to_constructor<typename cross_compiler_interface::type_information<cross_compiler_interface::implement_interface<FactoryInterface>>::functions>::type f_t;
                    f_t::set(*this,memp,*factory_interface());
                    activation_factory_interface()->ActivateInstance.template set_mem_fn<
                        implement_factory_static_interfaces,&implement_factory_static_interfaces::activate_instance>(this);
                }

               
                

        };

        typedef implement_factory_static_interfaces ImplementFactoryStaticInterfaces;

        static use_unknown<InterfaceActivationFactory> get_activation_factory(hstring hs){
            if(hs==runtime_class_t::get_runtime_class_name()){
                return implement_factory_static_interfaces::create().QueryInterface<InterfaceActivationFactory>();
            }
            else{
                return nullptr;
            }
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

        template<template<class> class Interface, class Base>
        struct inherit_use_interface_helper:public use_unknown<Interface>,Base{};

        template<template<class> class... Interfaces>
        struct inherit_use_interfaces_linearly{};

        template<template<class> class First,template<class> class... Rest>
        struct inherit_use_interfaces_linearly<First,Rest...>:public inherit_use_interface_helper<First,inherit_use_interfaces_linearly<Rest...>> {;

        };

        struct inspectable_holder{
            use_unknown<InterfaceInspectable> inspectable_;

            inspectable_holder(use_unknown<InterfaceInspectable> i):inspectable_(i){}

            use_unknown<InterfaceInspectable>& get_inspectable(){
                return inspectable_;
            }

        };


    }

    inline use_unknown<InterfaceActivationFactory> get_activation_factory(const hstring& id){
        cross_compiler_interface::portable_base* paf = nullptr;
        auto e = ::RoGetActivationFactory(id.value(),use_unknown<InterfaceActivationFactory>::uuid::get_windows_guid<GUID>(),reinterpret_cast<void**>(&paf));
        if(e < 0){
            cross_compiler_interface::general_error_mapper::exception_from_error_code(e);
        }
        use_unknown<InterfaceActivationFactory> ret(cross_compiler_interface::reinterpret_portable_base<InterfaceActivationFactory>(paf),false);
        return ret;
    }
    namespace detail{
          template<template<class> class... Interfaces>
        struct use_runtime_class_helper{};

        template<>
        struct use_runtime_class_helper<>{
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

        template<class Base,class CF, class F>
        struct interface_overload_function_helper{


        };
        template<class Base,class CF, class R, class... Parms>
        struct interface_overload_function_helper<Base,CF,R(Parms...)>:public Base{

             static R overloaded_call(cross_compiler_interface::portable_base* p, Parms... parms){
                CF cf(p);
                return cf(parms...);
            }


        };
                template<class Base,class CF>
        struct interface_overload_function:public interface_overload_function_helper<Base,CF,typename CF::function_signature>{
            using interface_overload_function_helper::overloaded_call;
            using Base::overloaded_call;

        };



        template<class... CF>
        struct inheritance_overload_helper{};
        template<class First,class... CF>
        struct inheritance_overload_helper<First,CF...>:public interface_overload_function<inheritance_overload_helper<CF...>,First>{
            typedef First first_cf_type;
            typedef inheritance_overload_helper<CF...> rest_cf_types;

        };
        template<>
        struct inheritance_overload_helper<>{
        
            // All calls to overloaded call have portable_base as first parameter so this will not resolve
            void overloaded_call();
        
        };

        template<class TypeList>
        struct forward_to_inheritance_overload_helper{};

        template<class... T>
        struct forward_to_inheritance_overload_helper<cross_compiler_interface::type_list<T...>>{
            typedef inheritance_overload_helper<T...> type;
        };

        template<class Interface,class... Parms>
        static use_unknown<InterfaceInspectable> overloaded_creator(Interface i,Parms... p){
            typedef typename cross_compiler_interface::type_information<Interface>::functions functions;
            typedef typename forward_to_inheritance_overload_helper<functions>::type helper;
            cross_compiler_interface::portable_base* pb = i.get_portable_base();
            return helper::overloaded_call(pb,p...).QueryInterface<InterfaceInspectable>();
        }

        // Holds factory and a ro_init call
        // This assures that we won't be destructing after last RoInitializeCalled
        struct activation_factory_holder{

            unique_ro_initialize init_;
            use_unknown<InterfaceActivationFactory> af_;

            activation_factory_holder(use_unknown<InterfaceActivationFactory> af):af_(af){};


        };
    }


    template<hstring(*pfun_runtime_class_name)(),template<class> class DefaultInterface, template<class> class FactoryInterface, template<class> class StaticInterface, template<class> class... Others>
    struct use_winrt_runtime_class<winrt_runtime_class<pfun_runtime_class_name,DefaultInterface,FactoryInterface,StaticInterface,Others...>>
        :private detail::inspectable_holder,
        public detail::inherit_use_interfaces_linearly<DefaultInterface,Others...>
    {
        typedef winrt_runtime_class<pfun_runtime_class_name,DefaultInterface,FactoryInterface,StaticInterface,Others...> runtime_class_t;
        cross_compiler_interface::use_unknown<DefaultInterface> default_interface(){
            return this->get_implementation<DefaultInterface>();

        } 
        template<template<class> class Interface>
        cross_compiler_interface::use_unknown<Interface> as(){
            return this->get_inspectable().QueryInterface<Interface>();
        }

        static use_unknown<InterfaceActivationFactory> activation_factory_interface(){
            // Cache the activation factory
            static detail::activation_factory_holder afh_(get_activation_factory(runtime_class_t::get_runtime_class_name()));
            return afh_.af_;

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
            typedef detail::use_runtime_class_helper<DefaultInterface,Others...> h_t;
            h_t::set_use_unknown(this);
        }

        template<class P,class... Parms>
        use_winrt_runtime_class(P p0,Parms... p)
            :detail::inspectable_holder(detail::overloaded_creator(factory_interface(),p0,p...))
        {
            typedef detail::use_runtime_class_helper<DefaultInterface,Others...> h_t;
            h_t::set_use_unknown(this);
        }
    private:



    };

 

}


CROSS_COMPILER_INTERFACE_DEFINE_INTERFACE_INFORMATION(cc_winrt::InterfaceInspectable,GetIids,GetRuntimeClassName,GetTrustLevel);
CROSS_COMPILER_INTERFACE_DEFINE_INTERFACE_INFORMATION(cc_winrt::InterfaceActivationFactory,ActivateInstance);
