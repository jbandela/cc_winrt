#include "..\widget_interface.h"

struct ImplementWidget :public cc_winrt::implement_winrt_runtime_class<ImplementWidget,Widget_t>
{

    int number_;
    // Sets the implementation for the cross_functions
    void init(){
        default_interface()->GetNumber = [this](){return number_;};
    }

    // cc_winrt will automatically map from factory interface to Constructors
    ImplementWidget():number_(0){init();}
    ImplementWidget(std::int32_t i):number_(i){init();}
    ImplementWidget(std::int32_t i,std::int32_t j):number_(i+j){init();}

};

extern "C" HRESULT WINAPI DllGetActivationFactory(_In_ HSTRING activatibleClassId, _Deref_out_ IActivationFactory** factory)
{
    return cc_winrt::get_activation_factory<ImplementWidget>(activatibleClassId,factory);
}


extern "C" HRESULT WINAPI DllCanUnloadNow()
{
   return cc_winrt::dll_can_unload_now();
}


#pragma comment(lib,"ole32")