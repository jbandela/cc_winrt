

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0595 */
/* at Sat May 11 18:18:36 2013
 */
/* Compiler settings for C:\Users\jrb\AppData\Local\Temp\Contoso.idl-e251ae85:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 8.00.0595 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __Contoso_h_h__
#define __Contoso_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#if defined(__cplusplus)
#if defined(__MIDL_USE_C_ENUM)
#define MIDL_ENUM enum
#else
#define MIDL_ENUM enum class
#endif
#endif


/* Forward Declarations */ 

#ifndef ____x_ABI_CContoso_CICalculator_FWD_DEFINED__
#define ____x_ABI_CContoso_CICalculator_FWD_DEFINED__
typedef interface __x_ABI_CContoso_CICalculator __x_ABI_CContoso_CICalculator;

#ifdef __cplusplus
namespace ABI {
    namespace Contoso {
        interface ICalculator;
    } /* end namespace */
} /* end namespace */

#endif /* __cplusplus */

#endif 	/* ____x_ABI_CContoso_CICalculator_FWD_DEFINED__ */


/* header files for imported files */
#include "inspectable.h"
#include "Windows.Foundation.h"

#ifdef __cplusplus
extern "C"{
#endif 


/* interface __MIDL_itf_Contoso_0000_0000 */
/* [local] */ 


#ifdef __cplusplus
namespace ABI {
namespace Contoso {
class Calculator;
} /*Contoso*/
}
#endif
#if !defined(____x_ABI_CContoso_CICalculator_INTERFACE_DEFINED__)
extern const __declspec(selectany) WCHAR InterfaceName_Contoso_ICalculator[] = L"Contoso.ICalculator";
#endif /* !defined(____x_ABI_CContoso_CICalculator_INTERFACE_DEFINED__) */


/* interface __MIDL_itf_Contoso_0000_0000 */
/* [local] */ 




extern RPC_IF_HANDLE __MIDL_itf_Contoso_0000_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_Contoso_0000_0000_v0_0_s_ifspec;

#ifndef ____x_ABI_CContoso_CICalculator_INTERFACE_DEFINED__
#define ____x_ABI_CContoso_CICalculator_INTERFACE_DEFINED__

/* interface __x_ABI_CContoso_CICalculator */
/* [uuid][object] */ 



/* interface ABI::Contoso::ICalculator */
/* [uuid][object] */ 


EXTERN_C const IID IID___x_ABI_CContoso_CICalculator;

#if defined(__cplusplus) && !defined(CINTERFACE)
    } /* end extern "C" */
    namespace ABI {
        namespace Contoso {
            
            MIDL_INTERFACE("d876445f-1574-4ff0-b448-db7243b21975")
            ICalculator : public IInspectable
            {
            public:
                virtual HRESULT STDMETHODCALLTYPE Add( 
                    /* [in] */ int a,
                    /* [in] */ int b,
                    /* [out][retval] */ int *value) = 0;
                
            };

            extern const __declspec(selectany) IID & IID_ICalculator = __uuidof(ICalculator);

            
        }  /* end namespace */
    }  /* end namespace */
    extern "C" { 
    
#else 	/* C style interface */

    typedef struct __x_ABI_CContoso_CICalculatorVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            __x_ABI_CContoso_CICalculator * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            __x_ABI_CContoso_CICalculator * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            __x_ABI_CContoso_CICalculator * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetIids )( 
            __x_ABI_CContoso_CICalculator * This,
            /* [out] */ ULONG *iidCount,
            /* [size_is][size_is][out] */ IID **iids);
        
        HRESULT ( STDMETHODCALLTYPE *GetRuntimeClassName )( 
            __x_ABI_CContoso_CICalculator * This,
            /* [out] */ HSTRING *className);
        
        HRESULT ( STDMETHODCALLTYPE *GetTrustLevel )( 
            __x_ABI_CContoso_CICalculator * This,
            /* [out] */ TrustLevel *trustLevel);
        
        HRESULT ( STDMETHODCALLTYPE *Add )( 
            __x_ABI_CContoso_CICalculator * This,
            /* [in] */ int a,
            /* [in] */ int b,
            /* [out][retval] */ int *value);
        
        END_INTERFACE
    } __x_ABI_CContoso_CICalculatorVtbl;

    interface __x_ABI_CContoso_CICalculator
    {
        CONST_VTBL struct __x_ABI_CContoso_CICalculatorVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define __x_ABI_CContoso_CICalculator_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define __x_ABI_CContoso_CICalculator_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define __x_ABI_CContoso_CICalculator_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define __x_ABI_CContoso_CICalculator_GetIids(This,iidCount,iids)	\
    ( (This)->lpVtbl -> GetIids(This,iidCount,iids) ) 

#define __x_ABI_CContoso_CICalculator_GetRuntimeClassName(This,className)	\
    ( (This)->lpVtbl -> GetRuntimeClassName(This,className) ) 

#define __x_ABI_CContoso_CICalculator_GetTrustLevel(This,trustLevel)	\
    ( (This)->lpVtbl -> GetTrustLevel(This,trustLevel) ) 


#define __x_ABI_CContoso_CICalculator_Add(This,a,b,value)	\
    ( (This)->lpVtbl -> Add(This,a,b,value) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* ____x_ABI_CContoso_CICalculator_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_Contoso_0000_0001 */
/* [local] */ 

#ifndef RUNTIMECLASS_Contoso_Calculator_DEFINED
#define RUNTIMECLASS_Contoso_Calculator_DEFINED
extern const __declspec(selectany) WCHAR RuntimeClass_Contoso_Calculator[] = L"Contoso.Calculator";
#endif


/* interface __MIDL_itf_Contoso_0000_0001 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_Contoso_0000_0001_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_Contoso_0000_0001_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


