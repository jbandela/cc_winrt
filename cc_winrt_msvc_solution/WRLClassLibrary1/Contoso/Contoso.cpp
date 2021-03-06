#include "pch.h"
#include "ContosoInterface.hpp"

struct ImplementCalculator:public cc_winrt::implement_winrt_runtime_class<ImplementCalculator,Calculator_t>{

	std::int32_t factor_;
    std::int32_t Add(std::int32_t a,std::int32_t b){
        return factor_ * (a + b);
    }

	static std::int32_t AddStatic(std::int32_t a, std::int32_t b){ return a + b; }

	ImplementCalculator():factor_(1){}

	ImplementCalculator(std::int32_t f) : factor_(f){}
};



extern "C" HRESULT WINAPI DllGetActivationFactory(_In_ HSTRING activatibleClassId, _Deref_out_ IActivationFactory** factory)
{
    return cc_winrt::get_activation_factory<ImplementCalculator>(activatibleClassId,factory);

}


extern "C" HRESULT WINAPI DllCanUnloadNow()
{
    return cross_compiler_interface::object_counter::get().get_count() == 0 ? S_OK : S_FALSE;
}


