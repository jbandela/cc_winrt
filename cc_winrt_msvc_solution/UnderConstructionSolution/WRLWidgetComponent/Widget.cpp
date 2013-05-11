#include "../widget_interface.h"


// To implement a widget derive from cc_winrt::implement_winrt_runtime_class
struct ImplementWidget :public cc_winrt::implement_winrt_runtime_class<ImplementWidget,Widget_t>
{

    int number_;
    
    // Implementation of the interface
    std::int32_t GetNumber(){
        return number_;
    }

    // cc_winrt will automatically map from factory interface to Constructors
    ImplementWidget():number_(0){ }
    ImplementWidget(std::int32_t i):number_(i){}
    ImplementWidget(std::int32_t i,std::int32_t j):number_(i+j){}

};

// We have to change the definition of DllGetActivationFactory and DllCanUnloadNow to use cc_winrt instead of WRL
extern "C" HRESULT WINAPI DllGetActivationFactory(_In_ HSTRING activatibleClassId, _Deref_out_ IActivationFactory** factory)
{
    return cc_winrt::get_activation_factory<ImplementWidget>(activatibleClassId,factory);
}


extern "C" HRESULT WINAPI DllCanUnloadNow()
{
   return cc_winrt::dll_can_unload_now();
}

// Automatic linking with OLE2 for CoTaskMemAlloc
#pragma comment(lib,"ole32")