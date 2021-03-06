#include <iostream>
#include "../../../cc_winrt.hpp"

// Define the interfaces - taken from windows.foundation.h

struct InterfaceUriRuntimeClass : public cppcomponents::define_interface <cppcomponents::uuid< 0x9E365E57, 0x48B2, 0x4160, 0x956F, 0xC7385120BBFC>,cc_winrt::InterfaceInspectable>{

        // Define a typedef for hstring
        typedef cc_winrt::hstring hstring;

        // Declare Interface so we can use it in our class
        template<class T> struct Interface;

        // Define the UUID for the class

        hstring GetAbsoluteUri();
        hstring GetDisplayUri();
        hstring GetDomain();
        hstring GetExtension();
        hstring GetFragment();
        hstring GetHost();
        hstring GetPassword();
        hstring GetPath();
        hstring GetQuery();

        // Change so we don't have to define Iwwwformdecoder
        cppcomponents::use<cc_winrt::InterfaceInspectable> GetQueryParsed();

        hstring GetRawUri();
        hstring GetSchemeName();
        hstring GetUserName();
        hstring GetPort();
        boolean GetSuspicious();
		boolean Equals(cppcomponents::use<InterfaceUriRuntimeClass>);
		cppcomponents::use<InterfaceUriRuntimeClass> CombineUri(hstring);



		CPPCOMPONENTS_CONSTRUCT(InterfaceUriRuntimeClass, GetAbsoluteUri, GetDisplayUri, GetDomain, GetExtension, GetFragment, GetHost, GetPassword, GetPath,
            GetQuery,GetQueryParsed,GetRawUri,GetSchemeName,GetUserName,GetPort,GetSuspicious,Equals,CombineUri);


    };

        //[uuid(758D9661-221C-480F-A339-50656673F46F)]
        //[version(0x06020000)]
        //[exclusiveto(Windows.Foundation.Uri)]
        //interface IUriRuntimeClassWithAbsoluteCanonicalUri : IInspectable
        //{
        //    [propget] HRESULT AbsoluteCanonicalUri([out] [retval] HSTRING* value);
        //    [propget] HRESULT DisplayIri([out] [retval] HSTRING* value);
        //}

struct InterfaceUriRuntimeClassWithAbsoluteCanonicalUri : cppcomponents::define_interface <cppcomponents::uuid< 0x758D9661, 0x221C, 0x480F, 0xA339, 0x50656673F46F>,cc_winrt::InterfaceInspectable>{
        cc_winrt::hstring AbsoluteCanonicalUri();
        cc_winrt::hstring DisplayIri();

		CPPCOMPONENTS_CONSTRUCT(InterfaceUriRuntimeClassWithAbsoluteCanonicalUri, AbsoluteCanonicalUri, DisplayIri);
        

    };

        //    [uuid(C1D432BA-C824-4452-A7FD-512BC3BBE9A1)]
        //[exclusiveto(Windows.Foundation.Uri)]
        //[version(0x06020000)]
        //interface IUriEscapeStatics : IInspectable
        //{
        //    HRESULT UnescapeComponent([in] HSTRING toUnescape, [out] [retval] HSTRING* value);
        //    HRESULT EscapeComponent([in] HSTRING toEscape, [out] [retval] HSTRING* value);
        //}

struct InterfaceUriEscapeStatics : cppcomponents::define_interface<cppcomponents::uuid<0xC1D432BA, 0xC824, 0x4452, 0xA7FD, 0x512BC3BBE9A1>, cc_winrt::InterfaceInspectable>{

        cc_winrt::hstring UnescapeComponent(cc_winrt::hstring toUnescape);
        cc_winrt::hstring EscapeComponent(cc_winrt::hstring toUnescape);

		CPPCOMPONENTS_CONSTRUCT(InterfaceUriEscapeStatics, UnescapeComponent, EscapeComponent);
    };

struct InterfaceUriRuntimeClassFactory : cppcomponents::define_interface<cppcomponents::uuid<0x44A9796F, 0x723E, 0x4FDF, 0xA218, 0x033E75B0C084>, cc_winrt::InterfaceInspectable>{

    typedef cc_winrt::hstring hstring;


    cppcomponents::use<InterfaceUriRuntimeClass> CreateUri(hstring);
	cppcomponents::use< InterfaceUriRuntimeClass > CreateWithRelativeUri(hstring, hstring);

    
	CPPCOMPONENTS_CONSTRUCT(InterfaceUriRuntimeClassFactory, CreateUri, CreateWithRelativeUri);

};






inline  cc_winrt::hstring FoundationUri(){return L"Windows.Foundation.Uri";}
typedef cc_winrt::winrt_runtime_class<FoundationUri,
	cppcomponents::object_interfaces<InterfaceUriRuntimeClass,InterfaceUriRuntimeClassWithAbsoluteCanonicalUri>,
	cppcomponents::factory_interface<InterfaceUriRuntimeClassFactory>,cppcomponents::static_interfaces<InterfaceUriEscapeStatics> > ClassUri_t;


typedef cc_winrt::use_winrt_runtime_class<ClassUri_t> CUri;


int main(){
    int sz = sizeof(RO_INIT_TYPE);
    try{
        // Initialize/deinitialize WinRT
        cc_winrt::unique_ro_initialize init;

        CUri uri(L"http://www.microsoft.com");

        std::wcout << L"Domain name: " << uri.GetDomain().c_str() << std::endl;

        std::wcout << L"Absolute Canonical Uri: " << uri.AbsoluteCanonicalUri().c_str() << std::endl;
        auto escaped = CUri::EscapeComponent(L"this is a test");
        std::wcout << escaped.c_str() << std::endl;
        auto unescaped = CUri::UnescapeComponent(escaped);
        std::wcout << unescaped.c_str() << std::endl;
        
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