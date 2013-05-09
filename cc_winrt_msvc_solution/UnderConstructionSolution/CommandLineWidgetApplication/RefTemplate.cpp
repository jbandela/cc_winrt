// RefTemplate.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <wrl.h>
#include "C:\Users\jrb\Downloads\UnderConstructionSolution\UnderConstructionSolution\WRLWidgetComponent\WRLWidgetComponent_h.h"
using namespace std;

using namespace Platform;

using namespace Microsoft::WRL::Wrappers;
using namespace Microsoft::WRL;


typedef WRLWidgetComponent::Widget   WRLWidget;

int main(Platform::Array<Platform::String^>^ args)
{
    // Demonstrate default construction of both:
    WRLWidget^   defaultConstructedWrlWidget   = ref new WRLWidget();

    // Demonstrate factory construction of both:
    WRLWidget^   factoryConstructedWrlWidget   = ref new WRLWidget(42);

      HStringReference classId(RuntimeClass_WidgetComponent_Widget);
    
    ComPtr<IWidgetFactory> factory;
    RoGetActivationFactory(
        classId.Get(),
        __uuidof(IWidgetFactory),
        reinterpret_cast<void**>(factory.GetAddressOf()));
    
    ComPtr<IWidget> widget;
    factory->CreateInstance(42, widget.GetAddressOf());
}


