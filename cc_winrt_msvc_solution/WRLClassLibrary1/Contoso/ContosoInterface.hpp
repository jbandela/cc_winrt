#include "../../../cc_winrt.hpp"

//namespace Contoso
//{
//    interface ICalculator;
//    runtimeclass Calculator;
//
//    [uuid(d876445f-1574-4ff0-b448-db7243b21975), version(COMPONENT_VERSION), exclusiveto(Calculator)] 
//    interface ICalculator : IInspectable
//    {
//        HRESULT Add([in] int a, [in] int b, [out, retval] int* value);
//    }
//
//    [version(COMPONENT_VERSION), activatable(COMPONENT_VERSION)]
//    runtimeclass Calculator
//    {
//        [default] interface ICalculator;
//    }
//}

struct InterfaceCalculator : public cppcomponents::define_interface <cppcomponents::uuid< 0xd876445f, 0x1574, 0x4ff0, 0xb448, 0xdb7243b21975>,cc_winrt::InterfaceInspectable>{


    std::int32_t Add(std::int32_t a, std::int32_t b);

    CPPCOMPONENTS_CONSTRUCT(InterfaceCalculator,Add);



};

struct InterfaceCalculatorFactory : public cppcomponents::define_interface <cppcomponents::uuid< 0xd876445f, 0x1574, 0x4ff0, 0xb448, 0xdb7243b21978>, cc_winrt::InterfaceInspectable>{

	cppcomponents::use<cppcomponents::InterfaceUnknown> Create(std::int32_t b);

	CPPCOMPONENTS_CONSTRUCT(InterfaceCalculatorFactory, Create);


}; struct InterfaceCalculatorStatic : public cppcomponents::define_interface < cppcomponents::uuid<0xd876445f, 0x1574, 0x4ff0, 0xb448, 0xdb7243b21979>, cc_winrt::InterfaceInspectable>{

	std::int32_t AddStatic(std::int32_t a,std::int32_t b);

	CPPCOMPONENTS_CONSTRUCT(InterfaceCalculatorStatic, AddStatic);


};
//template<class T>
//struct InterfaceCalculator:public cc_winrt::define_inspectable_interface<T,
//    cppcomponents::uuid<0xd876445f,0x1574,0x4ff0,0xb4,0x48,0xdb,0x72,0x43,0xb2,0x19,0x75>>{
//
//        cc_winrt::cross_function<InterfaceCalculator,0,int(int,int)> Add;
//
//        InterfaceCalculator():Add(this){}
//};
//
//
//CROSS_COMPILER_INTERFACE_DEFINE_INTERFACE_INFORMATION(InterfaceCalculator,Add);


inline cc_winrt::hstring ContosoCalculatorName(){return L"Contoso.Calculator";}

typedef cc_winrt::winrt_runtime_class<ContosoCalculatorName, cppcomponents::object_interfaces<InterfaceCalculator>,
	cppcomponents::factory_interface<InterfaceCalculatorFactory>,cppcomponents::static_interfaces<InterfaceCalculatorStatic> > Calculator_t;




