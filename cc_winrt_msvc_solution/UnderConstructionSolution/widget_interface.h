#include <C:\Users\jrb\Source\Repos\cc_winrt\cc_winrt.hpp>

// Define the Interface for the Widget
struct InterfaceWidget{
    // Every interface needs a unique uuid
    typedef cc_winrt::uuid<0xada06666,0x5abd,0x4691,0x8a,0x44,0x56,0x70,0x3e,0x02,0x0d,0x64> uuid;

    // Define the member functions of the interface
    std::int32_t GetNumber();

    // Defines the interface
    CC_WINRT_CONSTRUCT_INSPECTABLE_INTERFACE(InterfaceWidget,GetNumber);
};

// Define the Widget Factory
struct InterfaceWidgetFactory{

    // Every interface needs a unique uuid
    typedef cc_winrt::uuid<0x5b197688,0x2f57,0x4d01,0x92,0xcd,0xa8,0x88,0xf1,0x0d,0xcd,0x90> uuid;

    typedef cc_winrt::use_unknown<InterfaceWidget::Interface> IWidget;

    // Define the member functions of the interface
    IWidget CreateInstance1(std::int32_t);
    IWidget CreateInstance2(std::int32_t, std::int32_t);

    CC_WINRT_CONSTRUCT_INSPECTABLE_INTERFACE(InterfaceWidgetFactory,CreateInstance1,CreateInstance2);
};


// Tells what the RuntimeClassName is
inline cc_winrt::hstring WidgetRuntimeClassName(){return L"WRLWidgetComponent.Widget";}

// Define a runtime class
typedef cc_winrt::winrt_runtime_class<WidgetRuntimeClassName,InterfaceWidget::Interface,InterfaceWidgetFactory::Interface,cc_winrt::InterfaceInspectable> Widget_t;

// Define a typedef for use_winrt_runtime_class
typedef cc_winrt::use_winrt_runtime_class<Widget_t> Widget;
