#include "WRLWidgetComponent_h.h"

#include <wrl.h>
#include "..\widget_interface.h"

struct ImplementWidget :public cc_winrt::implement_winrt_runtime_class<ImplementWidget,Widget_t>
{

    int number_;

    void init(){
        default_interface()->GetNumber = [this](){return number_;};
    }

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
   auto count = cross_compiler_interface::object_counter::get().get_count();
   return count == 0 ? S_OK : S_FALSE;
}


