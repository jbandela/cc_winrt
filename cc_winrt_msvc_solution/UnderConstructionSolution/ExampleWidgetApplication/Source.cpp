#include "..\widget_interface.h"


typedef CxxCXWidgetComponent::Widget CxxCXWidget;
typedef WRLWidgetComponent::Widget   WRLWidget;

int main(Platform::Array<Platform::String^>^ args)
{
    // Demonstrate default construction of both:
    CxxCXWidget^ defaultConstructedCxxCXWidget = ref new CxxCXWidget();
    WRLWidget^   defaultConstructedWrlWidget   = ref new WRLWidget();



    // Demonstrate factory construction of both:
    CxxCXWidget^ factoryConstructedCxxCXWidget = ref new CxxCXWidget(42);
    WRLWidget^   factoryConstructedWrlWidget   = ref new WRLWidget(42);


    // Demonstrate using cc_winrt

    // Default constructed
    Widget w;

    // Call Function - notice real return
    auto a = w.GetNumber();

    // Constructed with int parameter
    Widget w2(42);
    auto a2 = w2.GetNumber();

    // We have another constructor that takes 2 parameters
    Widget w3(42,7);
    auto a3 = w3.GetNumber();

}
