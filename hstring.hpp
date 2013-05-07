 /// A std::wstring-like wrapper around HSTRING
    ///
    /// Useful for Windows Runtime interop code, this class provides most of the const parts of the
    /// std::wstring interface.  For mutation, it is recommended to convert to std::wstring, mutate,
    /// then convert back to SmartHString.
    class smart_hstring
    {
    public:

        typedef wchar_t           value_type;
        typedef size_type         size_type;
        typedef difference_type   difference_type;

        typedef value_type const& reference;
        typedef value_type const& const_reference;
        typedef value_type const* pointer;
        typedef value_type const* const_pointer;

        typedef pointer           iterator;
        typedef const_pointer     const_iterator;

        typedef std::reverse_iterator<iterator>       reverse_iterator;
        typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

        smart_hstring()
            : _value()
        {
        }

        explicit smart_hstring(const_pointer const s)
        {
            throw_on_failure(WindowsCreateString(s, static_cast<DWORD>(::wcslen(s)), &_value));
        }

        smart_hstring(smart_hstring const& other)
        {
            throw_on_failure(WindowsDuplicateString(other._value, &_value));
        }

        smart_hstring(smart_hstring&& other)
            : _value(other._value)
        {
            other._value = nullptr;
        }

        auto operator=(smart_hstring other) -> smart_hstring&
        {
            swap(other);
            return *this;
        }

        auto operator=(smart_hstring&& other) -> smart_hstring&
        {
            throw_on_failure(WindowsDeleteString(_value));
            _value = other._value;
            other._value = nullptr;
            return *this;
        }

        ~smart_hstring()
        {
            WindowsDeleteString(_value);
        }

        auto swap(smart_hstring& other) -> void
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
                throw hresult_error(E_BOUNDS);

            return get_buffer_begin()[n];
        }

        auto front() const -> const_reference { return *get_buffer_begin();     }
        auto back()  const -> const_reference { return *(get_buffer_end() - 1); }

        auto c_str() const -> const_pointer { return get_buffer_begin(); }
        auto data()  const -> const_pointer { return get_buffer_begin(); }

        // A reference proxy, returned by proxy(), that can be passed into a function expecting an
        // HSTRING*.  When the reference proxy is destroyed, it sets the value of the SmartHString
        // from which it was created.
        class reference_proxy
        {
        public:

            reference_proxy(smart_hstring* const value)
                : _value(value), _proxy(value->_value)
            {
            }

            ~reference_proxy()
            {
                if (_value->_value == _proxy)
                    return;

                smart_hstring new_string;
                new_string._value = _proxy;

                _value->swap(new_string);
            }

            operator HSTRING*() { return &_proxy; }

        private:

            // Note that this type is copyable though it is not intended to be copied, aside from
            // when it is returned from SmartHString::proxy().
            auto operator=(reference_proxy const&) -> reference_proxy&;

            HSTRING        _proxy;
            smart_hstring* _value;
        };

        auto proxy()       -> reference_proxy { return reference_proxy(this);                          }
        auto value() const -> HSTRING         { return _value;                                         }
        auto release()     -> HSTRING         { HSTRING value(_value); _value = nullptr; return value; }

        friend auto operator==(smart_hstring const& lhs, smart_hstring const& rhs) -> bool
        {
            return compare(lhs, rhs) ==  0;
        }

        friend auto operator<(smart_hstring const& lhs, smart_hstring const& rhs) -> bool
        {
            return compare(lhs, rhs) == -1;
        }

        friend auto operator!=(smart_hstring const& lhs, smart_hstring const& rhs) -> bool { return !(lhs == rhs); }
        friend auto operator> (smart_hstring const& lhs, smart_hstring const& rhs) -> bool { return   rhs <  lhs ; }
        friend auto operator>=(smart_hstring const& lhs, smart_hstring const& rhs) -> bool { return !(lhs <  rhs); }
        friend auto operator<=(smart_hstring const& lhs, smart_hstring const& rhs) -> bool { return !(rhs <  lhs); }

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

        static auto compare(smart_hstring const& lhs, smart_hstring const& rhs) -> int
        {
            std::int32_t result(0);
            throw_on_failure(WindowsCompareStringOrdinal(lhs._value, rhs._value, &result));
            return result;
        }

        HSTRING _value;
    };