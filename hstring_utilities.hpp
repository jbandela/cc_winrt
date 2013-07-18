//          Copyright John R. Bandela 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#pragma once
#ifndef INCLUDE_GUARD_CC_WINRT_HSTRING_UTILITIES_HPP_07_18_2013
#define INCLUDE_GUARD_CC_WINRT_HSTRING_UTILITIES_HPP_07_18_2013

#include <Hstring.h>
#include <Winstring.h>
#include <string>
#include "../cppcomponents/cross_compiler_interface/cross_compiler_introspection.hpp"
#ifdef max
#undef max
#endif
#ifdef min
#undef min
#endif

namespace cc_winrt{

    // Preserves HSTRING
    inline std::wstring wstring_from_hstring(const HSTRING& h){
        if( ::WindowsIsStringEmpty(h)){
            return std::wstring();
        }
        UINT32 sz = 0;
        auto p = ::WindowsGetStringRawBuffer(h,&sz);
        std::wstring r(p,p+sz);

        return r;
    }  
    // Destructive to HSTRING
    inline std::wstring wstring_from_hstring(HSTRING&& h){
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

    inline HSTRING hstring_from_wstring(const std::wstring& w){
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

        HSTRING& get(){return hs_;}
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

    // Adapted from CxxReflect utility.hpp
    //                            Copyright James P. McNellis 2011 - 2013.                            //
    //                   Distributed under the Boost Software License, Version 1.0.                   //
    //     (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)    //
    // Modified by John R. Bandela

    void throw_on_failure(HRESULT e){
        if( e < 0){
            cross_compiler_interface::general_error_mapper::exception_from_error_code(e);
        }
    }

}

// We want to use hstring as in cross_compiler_interface interfaces
// However, MSVC Milan has a namespace bug in the implementation of variadic templats
// There is a workaround in place for std
// We have to do this instead


       class namespace_cc_winrt_hstring
    {
    public:

        typedef wchar_t           value_type;
        typedef std::size_t         size_type;
        typedef std::ptrdiff_t   difference_type;

        typedef value_type const& reference;
        typedef value_type const& const_reference;
        typedef value_type const* pointer;
        typedef value_type const* const_pointer;

        typedef pointer           iterator;
        typedef const_pointer     const_iterator;

        typedef std::reverse_iterator<iterator>       reverse_iterator;
        typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

        namespace_cc_winrt_hstring()
            : _value()
        {
        }

        namespace_cc_winrt_hstring(const_pointer const s)
        {
            cc_winrt::throw_on_failure(WindowsCreateString(s, static_cast<DWORD>(::wcslen(s)), &_value));
        }

        explicit namespace_cc_winrt_hstring(const std::wstring& w):_value(cc_winrt::hstring_from_wstring(w)){
        }

        namespace_cc_winrt_hstring(namespace_cc_winrt_hstring const& other)
        {
            cc_winrt::throw_on_failure(WindowsDuplicateString(other._value, &_value));
        }

        namespace_cc_winrt_hstring(namespace_cc_winrt_hstring&& other)
            : _value(other._value)
        {
            other._value = nullptr;
        }

        namespace_cc_winrt_hstring(const HSTRING& h){
            cc_winrt::throw_on_failure(WindowsDuplicateString(h,&_value));
        }

        namespace_cc_winrt_hstring(HSTRING&& h){
            _value = h;
            h = nullptr;
        }

        auto operator=(namespace_cc_winrt_hstring other) -> namespace_cc_winrt_hstring&
        {
            swap(other);
            return *this;
        }

        auto operator=(namespace_cc_winrt_hstring&& other) -> namespace_cc_winrt_hstring&
        {
            cc_winrt::throw_on_failure(WindowsDeleteString(_value));
            _value = other._value;
            other._value = nullptr;
            return *this;
        }

        auto operator=(HSTRING&& h) -> namespace_cc_winrt_hstring&
        {
            _value = h;
            h = nullptr;
            return *this;
        }

        auto operator=(const std::wstring& w) -> namespace_cc_winrt_hstring&
        {
            _value = cc_winrt::hstring_from_wstring(w);
            return *this;
        }

        ~namespace_cc_winrt_hstring()
        {
            WindowsDeleteString(_value);
        }

        auto swap(namespace_cc_winrt_hstring& other) -> void
        {
            std::swap(_value, other._value);
        }

        auto begin()  const -> const_iterator { return get_buffer_begin(); }
        auto end()    const -> const_iterator { return get_buffer_end();   }
        auto cbegin() const -> const_iterator { return begin();            }
        auto cend()   const -> const_iterator { return end();              }

        auto rbegin()  const -> const_reverse_iterator { return reverse_iterator(get_buffer_end());   }
        auto rend()    const -> const_reverse_iterator { return reverse_iterator(get_buffer_begin()); }
        auto crbegin() const -> const_reverse_iterator { return rbegin();                             }
        auto crend()   const -> const_reverse_iterator { return rend();                               }

        auto size()     const -> size_type { return static_cast<size_type>(end() - begin()); }
        auto length()   const -> size_type { return size();                                  }
        auto max_size() const -> size_type { return std::numeric_limits<size_type>::max();   }
        auto capacity() const -> size_type { return size();                                  }
        auto empty()    const -> bool      { return size() == 0;                             }

        auto operator[](size_type const n) const -> const_reference
        {
            return get_buffer_begin()[n];
        }

        auto at(size_type const n) const -> const_reference
        {
            if (n >= size())
                throw cross_compiler_interface::error_out_of_range();

            return get_buffer_begin()[n];
        }

        auto front() const -> const_reference { return *get_buffer_begin();     }
        auto back()  const -> const_reference { return *(get_buffer_end() - 1); }

        auto c_str() const -> const_pointer { return get_buffer_begin(); }
        auto data()  const -> const_pointer { return get_buffer_begin(); }

        auto to_wstring() const -> std::wstring {return cc_winrt::wstring_from_hstring(_value); }


        // A reference proxy, returned by proxy(), that can be passed into a function expecting an
        // HSTRING*.  When the reference proxy is destroyed, it sets the value of the SmartHString
        // from which it was created.
        class reference_proxy
        {
        public:

            reference_proxy(namespace_cc_winrt_hstring* const value)
                : _value(value), _proxy(value->_value)
            {
            }

            ~reference_proxy()
            {
                if (_value->_value == _proxy)
                    return;

                namespace_cc_winrt_hstring new_string;
                new_string._value = _proxy;

                _value->swap(new_string);
            }

            operator HSTRING*() { return &_proxy; }

        private:

            // Note that this type is copyable though it is not intended to be copied, aside from
            // when it is returned from SmartHString::proxy().
            auto operator=(reference_proxy const&) -> reference_proxy&;

            HSTRING        _proxy;
            namespace_cc_winrt_hstring* _value;
        };

        auto proxy()       -> reference_proxy { return reference_proxy(this);                          }
        auto value() const -> HSTRING         { return _value;                                         }
        auto release()     -> HSTRING         { HSTRING value(_value); _value = nullptr; return value; }

        friend auto operator==(namespace_cc_winrt_hstring const& lhs, namespace_cc_winrt_hstring const& rhs) -> bool
        {
            return compare(lhs, rhs) ==  0;
        }

        friend auto operator<(namespace_cc_winrt_hstring const& lhs, namespace_cc_winrt_hstring const& rhs) -> bool
        {
            return compare(lhs, rhs) == -1;
        }

        friend auto operator!=(namespace_cc_winrt_hstring const& lhs, namespace_cc_winrt_hstring const& rhs) -> bool { return !(lhs == rhs); }
        friend auto operator> (namespace_cc_winrt_hstring const& lhs, namespace_cc_winrt_hstring const& rhs) -> bool { return   rhs <  lhs ; }
        friend auto operator>=(namespace_cc_winrt_hstring const& lhs, namespace_cc_winrt_hstring const& rhs) -> bool { return !(lhs <  rhs); }
        friend auto operator<=(namespace_cc_winrt_hstring const& lhs, namespace_cc_winrt_hstring const& rhs) -> bool { return !(rhs <  lhs); }

    private:

        auto get_buffer_begin() const -> const_pointer
        {
            const_pointer const result(WindowsGetStringRawBuffer(_value, nullptr));
            return result == nullptr ? get_empty_string() : result;
        }

        auto get_buffer_end() const -> const_pointer
        {
            std::uint32_t length(0);
            const_pointer const first(WindowsGetStringRawBuffer(_value, &length));
            return first == nullptr ? get_empty_string() : first + length;
        }

        static auto get_empty_string() -> const_pointer
        {
            static const_pointer const value(L"");
            return value;
        }

        static auto compare(namespace_cc_winrt_hstring const& lhs, namespace_cc_winrt_hstring const& rhs) -> int
        {
            std::int32_t result(0);
            cc_winrt::throw_on_failure(WindowsCompareStringOrdinal(lhs._value, rhs._value, &result));
            return result;
        }

        HSTRING _value;
    };

    namespace cc_winrt{
        typedef namespace_cc_winrt_hstring hstring;
    }

// allow hstring to be used in interface definitions
namespace cross_compiler_interface{
	template<>
	struct cross_conversion<cc_winrt::hstring>{
		typedef cc_winrt::hstring original_type;
		typedef HSTRING converted_type;
		static converted_type to_converted_type(const original_type& h){
			return h.value();
		}
		static  original_type to_original_type(HSTRING c){
            return cc_winrt::hstring(c);
		}

	};
	template<>
	struct cross_conversion_return<cc_winrt::hstring>{
		typedef cross_conversion<cc_winrt::hstring> cc;
		typedef cc_winrt::hstring return_type;
		typedef HSTRING converted_type;

		static void initialize_return(return_type& r, converted_type& c){
			
		}

		static void do_return(cc_winrt::hstring&& r,HSTRING& h){
            h = r.release();
            cc_winrt::throw_on_failure(::WindowsDuplicateString(r.value(),&h));
		}
		static void finalize_return(return_type& r,converted_type& c){

            r = std::move(c);
		}

	};
}

CROSS_COMPILER_INTERFACE_DEFINE_TYPE_INFORMATION(cc_winrt::hstring);

#endif