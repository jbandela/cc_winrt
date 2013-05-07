#include <Hstring.h>
#include <Winstring.h>
#include <string>
#include "../cross_compiler_call/cross_compiler_interface/cross_compiler_interface.hpp"

namespace cc_winrt{

    // Preserves HSTRING
    inline std::wstring WStringFromHSTRING(HSTRING h){
        if( ::WindowsIsStringEmpty(h)){
            return std::wstring();
        }
        UINT32 sz = 0;
        auto p = ::WindowsGetStringRawBuffer(h,&sz);
        std::wstring r(p,p+sz);

        return r;
    }  
    // Destructive to HSTRING
    inline std::wstring WStringFromHSTRING(HSTRING&& h){
        if( ::WindowsIsStringEmpty(h)){
            return std::wstring();
        }
        UINT32 sz = 0;
        auto p = ::WindowsGetStringRawBuffer(h,&sz);
        std::wstring r(p,p+sz);
        ::WindowsDeleteString(h);
        h = nullptr;
        return r;
    }

    inline HSTRING HSTRINGFromWString(const std::wstring& w){
        HSTRING r = nullptr;
        auto e = ::WindowsCreateString(w.c_str(),w.size(),&r);
        if(e < 0){
            cross_compiler_interface::general_error_mapper::exception_from_error_code(e);
        }
        return r;
    }

    struct unique_hstring{
        HSTRING hs_;
        unique_hstring(HSTRING h):hs_(h){}

        static HSTRING empty_string(){
            HSTRING hs;
            ::WindowsCreateString(nullptr,0,&hs);
            return hs;
        }

        HSTRING get(){return hs_;}
        HSTRING release(){
            HSTRING hs = hs_;
            hs_ = empty_string();
            return hs;
        }

        ~unique_hstring(){
            ::WindowsDeleteString(hs_);
            hs_ = empty_string();
        }
    };
}