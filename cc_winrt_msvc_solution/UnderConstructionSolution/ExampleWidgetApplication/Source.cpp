#include "..\widget_interface.h"


typedef CxxCXWidgetComponent::Widget CxxCXWidget;
typedef WRLWidgetComponent::Widget   WRLWidget;

int main(Platform::Array<Platform::String^>^ args)
{
    // Demonstrate default construction of both:
    CxxCXWidget^ defaultConstructedCxxCXWidget = ref new CxxCXWidget();
    WRLWidget^   defaultConstructedWrlWidget   = ref new WRLWidget();

    Widget w;

    auto a = w.GetNumber();

    auto i = defaultConstructedWrlWidget->GetNumber();

    // Demonstrate factory construction of both:
    CxxCXWidget^ factoryConstructedCxxCXWidget = ref new CxxCXWidget(42);
    WRLWidget^   factoryConstructedWrlWidget   = ref new WRLWidget(42);

    Widget w2(42);
    auto a2 = w2.GetNumber();
    Widget w3(42,7);
    auto a3 = w3.GetNumber();

    auto i2 = factoryConstructedWrlWidget->GetNumber();
}
