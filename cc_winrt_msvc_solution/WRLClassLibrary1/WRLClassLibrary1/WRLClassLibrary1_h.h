

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0602 */
/* at Mon Jul 08 10:28:41 2013
 */
/* Compiler settings for C:\Users\jrb\AppData\Local\Temp\WRLClassLibrary1.idl-5f39ea43:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 8.00.0602 
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

#ifndef __WRLClassLibrary1_h_h__
#define __WRLClassLibrary1_h_h__

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

#ifndef ____x_ABI_CWRLClassLibrary1_CIWinRTClass_FWD_DEFINED__
#define ____x_ABI_CWRLClassLibrary1_CIWinRTClass_FWD_DEFINED__
typedef interface __x_ABI_CWRLClassLibrary1_CIWinRTClass __x_ABI_CWRLClassLibrary1_CIWinRTClass;

#ifdef __cplusplus
namespace ABI {
    namespace WRLClassLibrary1 {
        interface IWinRTClass;
    } /* end namespace */
} /* end namespace */

#endif /* __cplusplus */

#endif 	/* ____x_ABI_CWRLClassLibrary1_CIWinRTClass_FWD_DEFINED__ */


/* header files for imported files */
#include "inspectable.h"

#ifdef __cplusplus
extern "C"{
#endif 


/* interface __MIDL_itf_WRLClassLibrary1_0000_0000 */
/* [local] */ 


#ifdef __cplusplus
namespace ABI {
namespace WRLClassLibrary1 {
class WinRTClass;
} /*WRLClassLibrary1*/
}
#endif
#if !defined(____x_ABI_CWRLClassLibrary1_CIWinRTClass_INTERFACE_DEFINED__)
extern const __declspec(selectany) _Null_terminated_ WCHAR InterfaceName_WRLClassLibrary1_IWinRTClass[] = L"WRLClassLibrary1.IWinRTClass";
#endif /* !defined(____x_ABI_CWRLClassLibrary1_CIWinRTClass_INTERFACE_DEFINED__) */


/* interface __MIDL_itf_WRLClassLibrary1_0000_0000 */
/* [local] */ 




extern RPC_IF_HANDLE __MIDL_itf_WRLClassLibrary1_0000_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_WRLClassLibrary1_0000_0000_v0_0_s_ifspec;

#ifndef ____x_ABI_CWRLClassLibrary1_CIWinRTClass_INTERFACE_DEFINED__
#define ____x_ABI_CWRLClassLibrary1_CIWinRTClass_INTERFACE_DEFINED__

/* interface __x_ABI_CWRLClassLibrary1_CIWinRTClass */
/* [uuid][object] */ 



/* interface ABI::WRLClassLibrary1::IWinRTClass */
/* [uuid][object] */ 


EXTERN_C const IID IID___x_ABI_CWRLClassLibrary1_CIWinRTClass;

#if defined(__cplusplus) && !defined(CINTERFACE)
    } /* end extern "C" */
    namespace ABI {
        namespace WRLClassLibrary1 {
            
            MIDL_INTERFACE("84f86918-9412-4353-96a7-1874f24a8179")
            IWinRTClass : public IInspectable
            {
            public:
                virtual HRESULT STDMETHODCALLTYPE Test( 
                    /* [out][retval] */ HSTRING *result) = 0;
                
            };

            extern const __declspec(selectany) IID & IID_IWinRTClass = __uuidof(IWinRTClass);

            
        }  /* end namespace */
    }  /* end namespace */
    extern "C" { 
    
#else 	/* C style interface */

    typedef struct __x_ABI_CWRLClassLibrary1_CIWinRTClassVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            __x_ABI_CWRLClassLibrary1_CIWinRTClass * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            __x_ABI_CWRLClassLibrary1_CIWinRTClass * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            __x_ABI_CWRLClassLibrary1_CIWinRTClass * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetIids )( 
            __x_ABI_CWRLClassLibrary1_CIWinRTClass * This,
            /* [out] */ ULONG *iidCount,
            /* [size_is][size_is][out] */ IID **iids);
        
        HRESULT ( STDMETHODCALLTYPE *GetRuntimeClassName )( 
            __x_ABI_CWRLClassLibrary1_CIWinRTClass * This,
            /* [out] */ HSTRING *className);
        
        HRESULT ( STDMETHODCALLTYPE *GetTrustLevel )( 
            __x_ABI_CWRLClassLibrary1_CIWinRTClass * This,
            /* [out] */ TrustLevel *trustLevel);
        
        HRESULT ( STDMETHODCALLTYPE *Test )( 
            __x_ABI_CWRLClassLibrary1_CIWinRTClass * This,
            /* [out][retval] */ HSTRING *result);
        
        END_INTERFACE
    } __x_ABI_CWRLClassLibrary1_CIWinRTClassVtbl;

    interface __x_ABI_CWRLClassLibrary1_CIWinRTClass
    {
        CONST_VTBL struct __x_ABI_CWRLClassLibrary1_CIWinRTClassVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define __x_ABI_CWRLClassLibrary1_CIWinRTClass_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define __x_ABI_CWRLClassLibrary1_CIWinRTClass_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define __x_ABI_CWRLClassLibrary1_CIWinRTClass_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define __x_ABI_CWRLClassLibrary1_CIWinRTClass_GetIids(This,iidCount,iids)	\
    ( (This)->lpVtbl -> GetIids(This,iidCount,iids) ) 

#define __x_ABI_CWRLClassLibrary1_CIWinRTClass_GetRuntimeClassName(This,className)	\
    ( (This)->lpVtbl -> GetRuntimeClassName(This,className) ) 

#define __x_ABI_CWRLClassLibrary1_CIWinRTClass_GetTrustLevel(This,trustLevel)	\
    ( (This)->lpVtbl -> GetTrustLevel(This,trustLevel) ) 


#define __x_ABI_CWRLClassLibrary1_CIWinRTClass_Test(This,result)	\
    ( (This)->lpVtbl -> Test(This,result) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* ____x_ABI_CWRLClassLibrary1_CIWinRTClass_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_WRLClassLibrary1_0000_0001 */
/* [local] */ 

#ifndef RUNTIMECLASS_WRLClassLibrary1_WinRTClass_DEFINED
#define RUNTIMECLASS_WRLClassLibrary1_WinRTClass_DEFINED
extern const __declspec(selectany) _Null_terminated_ WCHAR RuntimeClass_WRLClassLibrary1_WinRTClass[] = L"WRLClassLibrary1.WinRTClass";
#endif


/* interface __MIDL_itf_WRLClassLibrary1_0000_0001 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_WRLClassLibrary1_0000_0001_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_WRLClassLibrary1_0000_0001_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  HSTRING_UserSize(     unsigned long *, unsigned long            , HSTRING * ); 
unsigned char * __RPC_USER  HSTRING_UserMarshal(  unsigned long *, unsigned char *, HSTRING * ); 
unsigned char * __RPC_USER  HSTRING_UserUnmarshal(unsigned long *, unsigned char *, HSTRING * ); 
void                      __RPC_USER  HSTRING_UserFree(     unsigned long *, HSTRING * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


