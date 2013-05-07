#include "../cross_compiler_call/cross_compiler_interface/cross_compiler_introspection.hpp"

#include <Hstring.h>
#include <string>

#include <Inspectable.h>
#include <Objbase.h>
#include <algorithm>


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

    template<class T,class uuid_type, template<class> class Base = InterfaceInspectable >
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
            return HSTRINGFromWString(Derived::GetRuntimeClass());
        }

        TrustLevel GetTrustLevel(){
            return Derived::GetTrustLevel();
        }

		implement_inspectable_interfaces(){
			helper<Interfaces...>::set_mem_functions(this);
		}
	};

    typedef cross_compiler_interface::use_unknown<InterfaceInspectable> UseInterfaceInspectable;

    template<class T>
    struct InterfaceActivationFactory
        :public define_inspectable_interface<T,cross_compiler_interface::uuid<0xAF86E2E0,0xB12D,0x4c6a,0x9C,0x5A,0xD7,0xAA,0x65,0x10,0x1E,0x90>>
    {
        cross_function<InterfaceActivationFactory,0,UseInterfaceInspectable()> ActivateInstance;


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
        cross_compiler_interface::implement_interface<DefaultInterface>* default_interface(){
            return this->get_implementation<DefaultInterface>();

        }

        static TrustLevel GetTrustLevel(){return TrustLevel::BaseTrust;}

        static         HSTRING GetRuntimeClassName(){
            return HSTRINGFromWString(Derived::GetRuntimeClass());
        }



        struct implement_factory_static_interfaces
            :public detail::implement_factory_static_helper<typename Derived::ImplementFactoryStaticInterfaces,FactoryInterface,StaticInterface>{
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
                return HSTRINGFromWString(Derived::GetRuntimeClass());
            }
            static std::wstring GetRuntimeClass(){
                return Derived::GetRuntimeClass();
            }
        };
        static use_unknown<InterfaceActivationFactory> GetActivationFactory(HSTRING hs){
            auto w = WStringFromHSTRING(hs);
            if(w==Derived::GetRuntimeClass()){
                return implement_factory_static_interfaces::create.QueryInterface<InterfaceActivationFactory>();
            }
        }
        implement_winrt_runtime_class(){

        }

    };





}


CROSS_COMPILER_INTERFACE_DEFINE_INTERFACE_INFORMATION(cc_winrt::InterfaceInspectable,GetIids,GetRuntimeClassName,GetTrustLevel);
CROSS_COMPILER_INTERFACE_DEFINE_INTERFACE_INFORMATION(cc_winrt::InterfaceActivationFactory,ActivateInstance);
