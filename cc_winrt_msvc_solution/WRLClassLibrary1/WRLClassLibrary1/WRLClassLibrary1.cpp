#include "pch.h"
#include "WRLClassLibrary1_h.h"
#include <wrl.h>
#include "../../../cc_winrt.hpp"

using namespace Microsoft::WRL;
using namespace Windows::Foundation;

namespace ABI
{
	namespace WRLClassLibrary1
	{
		class WinRTClass: public RuntimeClass<IWinRTClass>
		{
			InspectableClass(L"WRLClassLibrary1.WinRTClass", BaseTrust)

			public:
			WinRTClass()
			{

			}

            HRESULT STDMETHODCALLTYPE Test(HSTRING* result){
                Microsoft::WRL::Wrappers::HString h;
                return S_OK;

            }
		};

		ActivatableClass(WinRTClass);
	}
}