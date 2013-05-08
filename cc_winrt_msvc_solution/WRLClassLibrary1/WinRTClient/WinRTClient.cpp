#include <iostream>
#include "../../../cc_winrt.hpp"

// Define the interfaces - taken from windows.foundation.h

template<class T>
struct InterfaceUriRuntimeClass;

// we typedef this because if we InterfaceUriRuntimeClass used inside the template it gets turned into a class
typedef cc_winrt::use_unknown<InterfaceUriRuntimeClass> PInterfaceUriRuntimeClass;

template<class T>
struct InterfaceUriRuntimeClass
    :public cc_winrt::define_inspectable_interface<T,cc_winrt::uuid<0x9E365E57,0x48B2,0x4160,0x95,0x6F,0xC7,0x38,0x51,0x20,0xBB,0xFC>>
{

    cc_winrt::cross_function<InterfaceUriRuntimeClass,0,cc_winrt::hstring()> GetAbsoluteUri;
    cc_winrt::cross_function<InterfaceUriRuntimeClass,1,cc_winrt::hstring()> GetDisplayUri;
    cc_winrt::cross_function<InterfaceUriRuntimeClass,2,cc_winrt::hstring()> GetDomain;
    cc_winrt::cross_function<InterfaceUriRuntimeClass,3,cc_winrt::hstring()> GetExtension;
    cc_winrt::cross_function<InterfaceUriRuntimeClass,4,cc_winrt::hstring()> GetFragment;
    cc_winrt::cross_function<InterfaceUriRuntimeClass,5,cc_winrt::hstring()> GetHost;
    cc_winrt::cross_function<InterfaceUriRuntimeClass,6,cc_winrt::hstring()> GetPassword;
    cc_winrt::cross_function<InterfaceUriRuntimeClass,7,cc_winrt::hstring()> GetPath;
    cc_winrt::cross_function<InterfaceUriRuntimeClass,8,cc_winrt::hstring()> GetQuery;

    // Change so we don't have to define Iwwwformdecoder
    cc_winrt::cross_function<InterfaceUriRuntimeClass,9,cc_winrt::use_interface<cc_winrt::InterfaceInspectable>()> GetQueryParsed;

    cc_winrt::cross_function<InterfaceUriRuntimeClass,10,cc_winrt::hstring()> GetRawUri;
    cc_winrt::cross_function<InterfaceUriRuntimeClass,11,cc_winrt::hstring()> GetSchemeName;
    cc_winrt::cross_function<InterfaceUriRuntimeClass,12,cc_winrt::hstring()> GetUserName;
    cc_winrt::cross_function<InterfaceUriRuntimeClass,13,cc_winrt::hstring()> GetPort;
    cc_winrt::cross_function<InterfaceUriRuntimeClass,14,boolean()> GetSuspicious;
    cc_winrt::cross_function<InterfaceUriRuntimeClass,15,boolean(PInterfaceUriRuntimeClass)> Equals;
    cc_winrt::cross_function<InterfaceUriRuntimeClass,16,PInterfaceUriRuntimeClass(cc_winrt::hstring)> CombineUri;

    InterfaceUriRuntimeClass()
        :GetAbsoluteUri(this),GetDisplayUri(this),GetDomain(this),GetExtension(this),GetFragment(this),GetHost(this),GetPassword(this),GetPath(this),
        GetQuery(this),GetQueryParsed(this),GetRawUri(this),GetSchemeName(this),GetUserName(this),GetPort(this),GetSuspicious(this),Equals(this),CombineUri(this)
    {}

};

CROSS_COMPILER_INTERFACE_DEFINE_INTERFACE_INFORMATION(InterfaceUriRuntimeClass,GetAbsoluteUri,GetDisplayUri,GetDomain,GetExtension,GetFragment,GetHost,GetPassword,GetPath,
        GetQuery,GetQueryParsed,GetRawUri,GetSchemeName,GetUserName,GetPort,GetSuspicious,Equals,CombineUri);

// Define the class factory
template<class T>
struct InterfaceUriRuntimeClassFactory:public cc_winrt::define_inspectable_interface<T,cc_winrt::uuid<0x44A9796F,0x723E,0x4FDF,0xA2,0x18,0x03,0x3E,0x75,0xB0,0xC0,0x84>>{

    cc_winrt::cross_function<InterfaceUriRuntimeClassFactory,0,cc_winrt::use_unknown<InterfaceUriRuntimeClass>(cc_winrt::hstring)> CreateUri;
    cc_winrt::cross_function<InterfaceUriRuntimeClassFactory,1,cc_winrt::use_unknown<InterfaceUriRuntimeClass>(cc_winrt::hstring,cc_winrt::hstring)> CreateWithRelativeUri;


    InterfaceUriRuntimeClassFactory()
        :CreateUri(this),CreateWithRelativeUri(this)
    {}
};

CROSS_COMPILER_INTERFACE_DEFINE_INTERFACE_INFORMATION(InterfaceUriRuntimeClassFactory,CreateUri,CreateWithRelativeUri);

inline  cc_winrt::hstring FoundationUri(){return L"Windows.Foundation.Uri";}
typedef cc_winrt::winrt_runtime_class<FoundationUri,InterfaceUriRuntimeClass,InterfaceUriRuntimeClassFactory,cc_winrt::InterfaceInspectable_> ClassUri_t;


typedef cc_winrt::use_winrt_runtime_class<ClassUri_t> CUri;


int main(){
    try{
        // Initialize/deinitialize WinRT
        cc_winrt::unique_ro_initialize init;

        CUri uri(L"http://www.microsoft.com");

        std::wcout << L"Domain name: " << uri.GetDomain().c_str() << std::endl;
    }

    catch(std::exception& e){
        std::cerr << "Error. " << e.what() << "\n";
    }  
}

// Below is the original program
  
//int wmain()
//{
//    // Initialize the Windows Runtime.
//    RoInitializeWrapper initialize(RO_INIT_MULTITHREADED);
//    if (FAILED(initialize))
//    {
//        return PrintError(__LINE__, initialize);
//    }
//
//    // Get the activation factory for the IUriRuntimeClass interface.
//    ComPtr<IUriRuntimeClassFactory> uriFactory;
//    HRESULT hr = GetActivationFactory(HStringReference(RuntimeClass_Windows_Foundation_Uri).Get(), &uriFactory);
//    if (FAILED(hr))
//    {
//        return PrintError(__LINE__, hr);
//    }
//
//    // Create a string that represents a URI.
//    HString uriHString;
//    hr = uriHString.Set(L"http://www.microsoft.com");
//    if (FAILED(hr))
//    {
//        return PrintError(__LINE__, hr);
//    }
//
//    // Create the IUriRuntimeClass object.
//    ComPtr<IUriRuntimeClass> uri;
//    hr = uriFactory->CreateUri(uriHString.Get(), &uri);
//    if (FAILED(hr))
//    {
//        return PrintError(__LINE__, hr);
//    }
//
//    // Get the domain part of the URI.
//    HString domainName;
//    hr = uri->get_Domain(domainName.GetAddressOf());
//    if (FAILED(hr))
//    {
//        return PrintError(__LINE__, hr);
//    }
//
//    // Print the domain name and return.
//    wprintf_s(L"Domain name: %s\n", domainName.GetRawBuffer(nullptr));
//
//    // All smart pointers and RAII objects go out of scope here.
//}
///*
//Output:
//Domain name: microsoft.com
//*/