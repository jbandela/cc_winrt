
#include <Inspectable.h>
#include <Objbase.h>
#include <Roapi.h> 

#include "hstring_utilities.hpp"
#include "../cross_compiler_call/cross_compiler_interface/cross_compiler_component.hpp"


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


	

    // Implementation of object count 
    inline HRESULT dll_can_unload_now(){
        auto count = cross_compiler_interface::object_counter::get().get_count();
        return count == 0 ? S_OK : S_FALSE;
    }

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


    typedef cross_compiler_interface::cross_compiler_interface_error_base hresult_error;
    typedef cross_compiler_interface::general_error_mapper error_mapper;

	using cppcomponents::InterfaceUnknown;

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
    struct InterfaceInspectable{
    template<class T>
    struct Interface:public cross_compiler_interface::define_unknown_interface<T,cross_compiler_interface::uuid<0xAF86E2E0,0xB12D,0x4c6a,0x9C,0x5A,0xD7,0xAA,0x65,0x10,0x1E,0x90>, cppcomponents::InterfaceUnknown::Interface>{

		detail::get_iids_cross_function<Interface, 0> GetIids;
		cross_compiler_interface::cross_function<Interface, 1, HSTRING()> GetRuntimeClassName;
		cross_compiler_interface::cross_function<Interface, 2, TrustLevel()> GetTrustLevel;


		CROSS_COMPILER_INTERFACE_HELPER_DEFINE_INTERFACE_CONSTRUCTOR_INTROSPECTION_NO_METHODS(InterfaceInspectable);
		Interface() : GetIids(this), GetRuntimeClassName(this), GetTrustLevel(this){}

    };    
    };

#define CCWINRT_CONSTRUCT(T,...)  \
	CPPCOMPONENTS_CONSTRUCT_WITH_BASE(T, cc_winrt::InterfaceInspectable, __VA_ARGS__)
#define CCWINRT_CONSTRUCT_WITH_BASE(T,B,...)  \
	CPPCOMPONENTS_CONSTRUCT_WITH_BASE(T, B, __VA_ARGS__)

#define CCWINRT_CONSTRUCT_NO_METHODS(T)  \
	CPPCOMPONENTS_CONSTRUCT_NO_METHODS_WITH_BASE(T, cc_winrt::InterfaceInspectable)
#define CCWINRT_CONSTRUCT_NO_METHODS_WITH_BASE(T,B)  \
	CPPCOMPONENTS_CONSTRUCT_NO_METHODS_WITH_BASE(T, B)


    // Implement interfaces derived from IInspectable and provide implementations of IUknown and IInspectable Methods
    template<class Derived, class... Interfaces>
    struct implement_inspectable_interfaces{

    private:



        template<class First, class... Rest>
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
                auto& u = typename First::uuid::get();
                v.push_back(u);

                helper<Rest...>::add_iids(v);
            }

        };
        template<class First>
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
                auto& u = typename First::uuid::get();
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
            helper<Interfaces...>::set_mem_functions(static_cast<Derived*>(this));
        }
    };

    // IActivationFactory
	struct InterfaceActivationFactory{
		typedef cppcomponents::uuid<0x00000035, 0x0000, 0x0000, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46> uuid;


		cppcomponents::use<cppcomponents::InterfaceUnknown> ActivateInstance();

		CCWINRT_CONSTRUCT(InterfaceActivationFactory, ActivateInstance);

	};



	

	namespace detail{

		template<class FactoryInterface,class StaticInterface>
		struct check_activation_factory_present{
			typedef cppcomponents::static_interfaces<StaticInterface, InterfaceActivationFactory> type;
		};

		template<class StaticInterface>
		struct check_activation_factory_present<InterfaceActivationFactory, StaticInterface>{
			typedef StaticInterface type;
		};

		template<class FactoryInterface, class... StaticInterfaces>
		struct check_activation_factory_present < FactoryInterface, cppcomponents::static_interfaces<StaticInterfaces...> >{
			typedef cppcomponents::static_interfaces<StaticInterfaces..., FactoryInterface> type;
		};

	}

	// Defines a winrt_runtime class
	template<hstring(*pfun_runtime_class_name)(), class DefaultInterface, class FactoryInterface, class StaticInterface, class... OtherInterfaces>
	struct winrt_runtime_class{

		// Make sure that activation factory is present, if not add to list as static interface
		typedef typename detail::check_activation_factory_present<FactoryInterface, StaticInterface>::type si_t;
		typedef cppcomponents::runtime_class_base<hstring, pfun_runtime_class_name, DefaultInterface, FactoryInterface, si_t, OtherInterfaces...> type;
	};

	namespace detail{

		template<class Derived,class RCB>
		struct inherit_from_implement_inspectable{};

		template < class Derived, hstring(*pfun_runtime_class_name)(), class DefaultInterface, class FactoryInterface, class StaticInterface, class... OtherInterfaces>
		struct inherit_from_implement_inspectable<Derived, cppcomponents::runtime_class_base<hstring, pfun_runtime_class_name, DefaultInterface, FactoryInterface, StaticInterface, OtherInterfaces...>>{
			typedef implement_inspectable_interfaces<Derived, DefaultInterface, OtherInterfaces...> object_type;

			template<class F, class S>
			struct helper{
				typedef implement_inspectable_interfaces<Derived, F, S> type;
			};
			template<class F,class... S>
			struct helper < F, cppcomponents::static_interfaces<S...> >{
				typedef implement_inspectable_interfaces<Derived, F, S...> type;
			};

			typedef typename helper<FactoryInterface, StaticInterface>::type static_type;
		};


	}

    // Enables implementing runtime class
    template<class Derived, class WRC>
    struct implement_winrt_runtime_class
	:public cppcomponents::implement_runtime_class_base<Derived,typename WRC::type>
	,public detail::inherit_from_implement_inspectable<Derived,typename WRC::type>::object_type{
	
		typedef cppcomponents::implement_runtime_class_base<Derived, typename WRC::type> imp_rcb_t;
		struct implement_factory_static_interfaces
			: public imp_rcb_t::implement_factory_static_interfaces
			, public detail::inherit_from_implement_inspectable<Derived, typename WRC::type>::static_type{


		};
		static TrustLevel GetTrustLevel(){ return BaseTrust; }
	};




    template<class...Imps>
    HRESULT get_activation_factory( HSTRING activatibleClassId, IActivationFactory** factory){

		return cppcomponents::get_activation_factory(cppcomponents::type_list<Imps...>(), activatibleClassId,reinterpret_cast<cppcomponents::portable_base**>(factory));


    }


	// Usage






	namespace detail{
          // Holds factory and a ro_init call
        // This assures that we won't be destructing after last RoInitializeCalled
        struct activation_factory_holder{


            activation_factory_holder(hstring hs):af_(get_activation_factory(hs)){};
			cppcomponents::use<InterfaceUnknown> get(){ return af_.QueryInterface<cppcomponents::InterfaceUnknown>(); };

			static cppcomponents::use<cppcomponents::InterfaceUnknown> create(hstring hs){
				return get_activation_factory(hs).QueryInterface<cppcomponents::InterfaceUnknown>();
			}
		private:
            unique_ro_initialize init_;
            cppcomponents::use<InterfaceActivationFactory> af_;

			static cppcomponents::use<InterfaceActivationFactory> get_activation_factory(const hstring& id){
				cross_compiler_interface::portable_base* paf = nullptr;
				auto e = ::RoGetActivationFactory(id.value(), cppcomponents::use<InterfaceActivationFactory>::uuid::get_windows_guid<GUID>(), reinterpret_cast<void**>(&paf));
				if (e < 0){
					cross_compiler_interface::general_error_mapper::exception_from_error_code(e);
				}
				cppcomponents::use<InterfaceActivationFactory> ret(cross_compiler_interface::reinterpret_portable_base<InterfaceActivationFactory::Interface>(paf), false);
				return ret;
			}
		};
    }


	template<class RC>
	struct use_winrt_runtime_class : public cppcomponents::use_runtime_class_base<typename RC::type, detail::activation_factory_holder>{
		typedef cppcomponents::use_runtime_class_base<typename RC::type, detail::activation_factory_holder> base_t;



		use_winrt_runtime_class(const base_t& b) : base_t{ b }{}

		template<class P0>
		explicit use_winrt_runtime_class(P0 && p0) : base_t{ std::forward<P0>(p0) }{}

		template<class P0, class... P>
		explicit use_winrt_runtime_class(P0 && p0, P && ... p) : base_t{ std::forward<P0>(p0), std::forward<P>(p)... }{}

		use_winrt_runtime_class() : base_t{base_t::from_interface(base_t::factory_interface().QueryInterface<InterfaceActivationFactory>().ActivateInstance())}{}

		

	};
 

}




