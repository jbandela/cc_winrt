#include <C:\Users\jrb\Source\Repos\cc_winrt\cc_winrt.hpp>

// Define the interface
// Same syntax as cross_compiler_call



    struct InterfaceWidget{
        typedef cc_winrt::uuid<0xada06666,0x5abd,0x4691,0x8a,0x44,0x56,0x70,0x3e,0x02,0x0d,0x64> uuid;

        std::int32_t GetNumber();

        CC_WINRT_CONSTRUCT_INSPECTABLE_INTERFACE(InterfaceWidget,GetNumber);


    };

    struct InterfaceWidgetFactory{
        typedef cc_winrt::uuid<0x5b197688,0x2f57,0x4d01,0x92,0xcd,0xa8,0x88,0xf1,0x0d,0xcd,0x90> uuid;

        typedef cc_winrt::use_unknown<InterfaceWidget::Interface> IWidget;

        IWidget CreateInstance1(std::int32_t);
        IWidget CreateInstance2(std::int32_t, std::int32_t);

        CC_WINRT_CONSTRUCT_INSPECTABLE_INTERFACE(InterfaceWidgetFactory,CreateInstance1,CreateInstance2);



    };


//template<class T>
//struct InterfaceWidget:public cc_winrt::define_inspectable_interface<T,>
//{
//    cc_winrt::cross_function<InterfaceWidget,0,std::int32_t()> GetNumber;
//
//    InterfaceWidget():GetNumber(this){}
//};
//
//// Define the introspection/reflection type information
//CROSS_COMPILER_INTERFACE_DEFINE_INTERFACE_INFORMATION(InterfaceWidget,GetNumber);
//
//
//// Define the factory
//template<class T>
//struct InterfaceWidgetFactory:public cc_winrt::define_inspectable_interface<T,
//{
//    cc_winrt::cross_function<InterfaceWidgetFactory,0,cc_winrt::use_unknown<InterfaceWidget>(std::int32_t)> CreateInstance1;
//    cc_winrt::cross_function<InterfaceWidgetFactory,1,cc_winrt::use_unknown<InterfaceWidget>(std::int32_t,std::int32_t)> CreateInstance2;
//
//    InterfaceWidgetFactory():CreateInstance1(this),CreateInstance2(this){}
//
//};
//
//// Define the introspection/reflection type information
//CROSS_COMPILER_INTERFACE_DEFINE_INTERFACE_INFORMATION(InterfaceWidgetFactory,CreateInstance1,CreateInstance2);

// Tells what the RuntimeClassName is
inline cc_winrt::hstring WidgetRuntimeClassName(){return L"WRLWidgetComponent.Widget";}

// Define a runtime class
typedef cc_winrt::winrt_runtime_class<WidgetRuntimeClassName,InterfaceWidget::Interface,InterfaceWidgetFactory::Interface,cc_winrt::InterfaceInspectable> Widget_t;

// Define a typedef for use_winrt_runtime_class
typedef cc_winrt::use_winrt_runtime_class<Widget_t> Widget;
