#include "pch.h"
#include "ContosoInterface.hpp"

struct ImplementCalculator:public cc_winrt::implement_winrt_runtime_class<ImplementCalculator,Calculator_t>{

    struct ImplementFactoryStaticInterfaces:public implement_factory_static_interfaces{};

    ImplementCalculator(){
        default_interface()->Add = [](int a,int b){ 
            return a + b; 
        };

    }

};



extern "C" HRESULT WINAPI DllGetActivationFactory(_In_ HSTRING activatibleClassId, _Deref_out_ IActivationFactory** factory)
{
    return cc_winrt::get_activation_factory<ImplementCalculator>(activatibleClassId,factory);
    //auto &module = Microsoft::WRL::Module<Microsoft::WRL::InProc>::GetModule();
    //return module.GetActivationFactory(activatibleClassId, factory);
}


extern "C" HRESULT WINAPI DllCanUnloadNow()
{
    //const auto &module = Microsoft::WRL::Module<Microsoft::WRL::InProc>::GetModule();    
    return cross_compiler_interface::object_counter::get().get_count() == 0 ? S_OK : S_FALSE;
}
//#include "Contoso_h.h"
//#include <wrl.h>
//
//using namespace Microsoft::WRL;
//using namespace Windows::Foundation;
//
//namespace ABI
//{
//	namespace Contoso
//	{
//		class Calculator: public RuntimeClass<ICalculator>
//		{
//			InspectableClass(L"Contoso.Calculator", BaseTrust)
//
//			public:
//			Calculator()
//			{
//			}
//
//            HRESULT __stdcall Add(_In_ int a, _In_ int b, _Out_ int* value)
//            {
//                if (value == nullptr)
//                {
//                    return E_POINTER;
//                }
//                *value = a + b;
//                return S_OK;
//            }
//		};
//
//		ActivatableClass(Calculator);
//	}
//}


