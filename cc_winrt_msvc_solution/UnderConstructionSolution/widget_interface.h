#include <C:\Users\jrb\Source\Repos\cc_winrt\cc_winrt.hpp>

template<class T>
struct InterfaceWidget:public cc_winrt::define_inspectable_interface<T,cross_compiler_interface::uuid<0xada06666,0x5abd,0x4691,0x8a,0x44,0x56,0x70,0x3e,0x02,0x0d,0x64>>
{
    cc_winrt::cross_function<InterfaceWidget,0,std::int32_t()> GetNumber;

    InterfaceWidget():GetNumber(this){}
};

CROSS_COMPILER_INTERFACE_DEFINE_INTERFACE_INFORMATION(InterfaceWidget,GetNumber);

template<class T>
struct InterfaceWidgetFactory:public cc_winrt::define_inspectable_interface<T,cc_winrt::uuid<0x5b197688,0x2f57,0x4d01,0x92,0xcd,0xa8,0x88,0xf1,0x0d,0xcd,0x90>>
{
    cc_winrt::cross_function<InterfaceWidgetFactory,0,cc_winrt::use_unknown<InterfaceWidget>(std::int32_t)> CreateInstance1;
    cc_winrt::cross_function<InterfaceWidgetFactory,1,cc_winrt::use_unknown<InterfaceWidget>(std::int32_t,std::int32_t)> CreateInstance2;

    InterfaceWidgetFactory():CreateInstance1(this),CreateInstance2(this){}

};
CROSS_COMPILER_INTERFACE_DEFINE_INTERFACE_INFORMATION(InterfaceWidgetFactory,CreateInstance1,CreateInstance2);

inline cc_winrt::hstring WidgetRuntimeClassName(){return L"WRLWidgetComponent.Widget";}
typedef cc_winrt::winrt_runtime_class<WidgetRuntimeClassName,InterfaceWidget,InterfaceWidgetFactory,cc_winrt::InterfaceInspectable> Widget_t;

typedef cc_winrt::use_winrt_runtime_class<Widget_t> Widget;
