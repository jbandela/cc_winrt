

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0595 */
/* at Sat May 11 14:18:25 2013
 */
/* Compiler settings for C:\Users\jrb\AppData\Local\Temp\WRLWidgetComponent.idl-a7441994:
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

#ifndef __WRLWidgetComponent_h_h__
#define __WRLWidgetComponent_h_h__

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

#ifndef ____x_ABI_CWRLWidgetComponent_CIWidget_FWD_DEFINED__
#define ____x_ABI_CWRLWidgetComponent_CIWidget_FWD_DEFINED__
typedef interface __x_ABI_CWRLWidgetComponent_CIWidget __x_ABI_CWRLWidgetComponent_CIWidget;

#ifdef __cplusplus
namespace ABI {
    namespace WRLWidgetComponent {
        interface IWidget;
    } /* end namespace */
} /* end namespace */

#endif /* __cplusplus */

#endif 	/* ____x_ABI_CWRLWidgetComponent_CIWidget_FWD_DEFINED__ */


#ifndef ____x_ABI_CWRLWidgetComponent_CIWidgetFactory_FWD_DEFINED__
#define ____x_ABI_CWRLWidgetComponent_CIWidgetFactory_FWD_DEFINED__
typedef interface __x_ABI_CWRLWidgetComponent_CIWidgetFactory __x_ABI_CWRLWidgetComponent_CIWidgetFactory;

#ifdef __cplusplus
namespace ABI {
    namespace WRLWidgetComponent {
        interface IWidgetFactory;
    } /* end namespace */
} /* end namespace */

#endif /* __cplusplus */

#endif 	/* ____x_ABI_CWRLWidgetComponent_CIWidgetFactory_FWD_DEFINED__ */


/* header files for imported files */
#include "inspectable.h"

#ifdef __cplusplus
extern "C"{
#endif 


/* interface __MIDL_itf_WRLWidgetComponent_0000_0000 */
/* [local] */ 

#ifdef __cplusplus
namespace ABI {
namespace WRLWidgetComponent {
class Widget;
} /*WRLWidgetComponent*/
}
#endif

#if !defined(____x_ABI_CWRLWidgetComponent_CIWidget_INTERFACE_DEFINED__)
extern const __declspec(selectany) WCHAR InterfaceName_WRLWidgetComponent_IWidget[] = L"WRLWidgetComponent.IWidget";
#endif /* !defined(____x_ABI_CWRLWidgetComponent_CIWidget_INTERFACE_DEFINED__) */


/* interface __MIDL_itf_WRLWidgetComponent_0000_0000 */
/* [local] */ 




extern RPC_IF_HANDLE __MIDL_itf_WRLWidgetComponent_0000_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_WRLWidgetComponent_0000_0000_v0_0_s_ifspec;

#ifndef ____x_ABI_CWRLWidgetComponent_CIWidget_INTERFACE_DEFINED__
#define ____x_ABI_CWRLWidgetComponent_CIWidget_INTERFACE_DEFINED__

/* interface __x_ABI_CWRLWidgetComponent_CIWidget */
/* [uuid][object] */ 



/* interface ABI::WRLWidgetComponent::IWidget */
/* [uuid][object] */ 


EXTERN_C const IID IID___x_ABI_CWRLWidgetComponent_CIWidget;

#if defined(__cplusplus) && !defined(CINTERFACE)
    } /* end extern "C" */
    namespace ABI {
        namespace WRLWidgetComponent {
            
            MIDL_INTERFACE("ada06666-5abd-4691-8a44-56703e020d64")
            IWidget : public IInspectable
            {
            public:
                virtual HRESULT STDMETHODCALLTYPE GetNumber( 
                    /* [out][retval] */ int *number) = 0;
                
            };

            extern const __declspec(selectany) IID & IID_IWidget = __uuidof(IWidget);

            
        }  /* end namespace */
    }  /* end namespace */
    extern "C" { 
    
#else 	/* C style interface */

    typedef struct __x_ABI_CWRLWidgetComponent_CIWidgetVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            __x_ABI_CWRLWidgetComponent_CIWidget * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            __x_ABI_CWRLWidgetComponent_CIWidget * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            __x_ABI_CWRLWidgetComponent_CIWidget * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetIids )( 
            __x_ABI_CWRLWidgetComponent_CIWidget * This,
            /* [out] */ ULONG *iidCount,
            /* [size_is][size_is][out] */ IID **iids);
        
        HRESULT ( STDMETHODCALLTYPE *GetRuntimeClassName )( 
            __x_ABI_CWRLWidgetComponent_CIWidget * This,
            /* [out] */ HSTRING *className);
        
        HRESULT ( STDMETHODCALLTYPE *GetTrustLevel )( 
            __x_ABI_CWRLWidgetComponent_CIWidget * This,
            /* [out] */ TrustLevel *trustLevel);
        
        HRESULT ( STDMETHODCALLTYPE *GetNumber )( 
            __x_ABI_CWRLWidgetComponent_CIWidget * This,
            /* [out][retval] */ int *number);
        
        END_INTERFACE
    } __x_ABI_CWRLWidgetComponent_CIWidgetVtbl;

    interface __x_ABI_CWRLWidgetComponent_CIWidget
    {
        CONST_VTBL struct __x_ABI_CWRLWidgetComponent_CIWidgetVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define __x_ABI_CWRLWidgetComponent_CIWidget_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define __x_ABI_CWRLWidgetComponent_CIWidget_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define __x_ABI_CWRLWidgetComponent_CIWidget_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define __x_ABI_CWRLWidgetComponent_CIWidget_GetIids(This,iidCount,iids)	\
    ( (This)->lpVtbl -> GetIids(This,iidCount,iids) ) 

#define __x_ABI_CWRLWidgetComponent_CIWidget_GetRuntimeClassName(This,className)	\
    ( (This)->lpVtbl -> GetRuntimeClassName(This,className) ) 

#define __x_ABI_CWRLWidgetComponent_CIWidget_GetTrustLevel(This,trustLevel)	\
    ( (This)->lpVtbl -> GetTrustLevel(This,trustLevel) ) 


#define __x_ABI_CWRLWidgetComponent_CIWidget_GetNumber(This,number)	\
    ( (This)->lpVtbl -> GetNumber(This,number) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* ____x_ABI_CWRLWidgetComponent_CIWidget_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_WRLWidgetComponent_0000_0001 */
/* [local] */ 

#if !defined(____x_ABI_CWRLWidgetComponent_CIWidgetFactory_INTERFACE_DEFINED__)
extern const __declspec(selectany) WCHAR InterfaceName_WRLWidgetComponent_IWidgetFactory[] = L"WRLWidgetComponent.IWidgetFactory";
#endif /* !defined(____x_ABI_CWRLWidgetComponent_CIWidgetFactory_INTERFACE_DEFINED__) */


/* interface __MIDL_itf_WRLWidgetComponent_0000_0001 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_WRLWidgetComponent_0000_0001_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_WRLWidgetComponent_0000_0001_v0_0_s_ifspec;

#ifndef ____x_ABI_CWRLWidgetComponent_CIWidgetFactory_INTERFACE_DEFINED__
#define ____x_ABI_CWRLWidgetComponent_CIWidgetFactory_INTERFACE_DEFINED__

/* interface __x_ABI_CWRLWidgetComponent_CIWidgetFactory */
/* [uuid][object] */ 



/* interface ABI::WRLWidgetComponent::IWidgetFactory */
/* [uuid][object] */ 


EXTERN_C const IID IID___x_ABI_CWRLWidgetComponent_CIWidgetFactory;

#if defined(__cplusplus) && !defined(CINTERFACE)
    } /* end extern "C" */
    namespace ABI {
        namespace WRLWidgetComponent {
            
            MIDL_INTERFACE("5b197688-2f57-4d01-92cd-a888f10dcd90")
            IWidgetFactory : public IInspectable
            {
            public:
                virtual HRESULT STDMETHODCALLTYPE CreateInstance4( 
                    /* [in] */ int value,
                    /* [out][retval] */ ABI::WRLWidgetComponent::IWidget **widget) = 0;
                
            };

            extern const __declspec(selectany) IID & IID_IWidgetFactory = __uuidof(IWidgetFactory);

            
        }  /* end namespace */
    }  /* end namespace */
    extern "C" { 
    
#else 	/* C style interface */

    typedef struct __x_ABI_CWRLWidgetComponent_CIWidgetFactoryVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            __x_ABI_CWRLWidgetComponent_CIWidgetFactory * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            __x_ABI_CWRLWidgetComponent_CIWidgetFactory * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            __x_ABI_CWRLWidgetComponent_CIWidgetFactory * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetIids )( 
            __x_ABI_CWRLWidgetComponent_CIWidgetFactory * This,
            /* [out] */ ULONG *iidCount,
            /* [size_is][size_is][out] */ IID **iids);
        
        HRESULT ( STDMETHODCALLTYPE *GetRuntimeClassName )( 
            __x_ABI_CWRLWidgetComponent_CIWidgetFactory * This,
            /* [out] */ HSTRING *className);
        
        HRESULT ( STDMETHODCALLTYPE *GetTrustLevel )( 
            __x_ABI_CWRLWidgetComponent_CIWidgetFactory * This,
            /* [out] */ TrustLevel *trustLevel);
        
        HRESULT ( STDMETHODCALLTYPE *CreateInstance4 )( 
            __x_ABI_CWRLWidgetComponent_CIWidgetFactory * This,
            /* [in] */ int value,
            /* [out][retval] */ __x_ABI_CWRLWidgetComponent_CIWidget **widget);
        
        END_INTERFACE
    } __x_ABI_CWRLWidgetComponent_CIWidgetFactoryVtbl;

    interface __x_ABI_CWRLWidgetComponent_CIWidgetFactory
    {
        CONST_VTBL struct __x_ABI_CWRLWidgetComponent_CIWidgetFactoryVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define __x_ABI_CWRLWidgetComponent_CIWidgetFactory_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define __x_ABI_CWRLWidgetComponent_CIWidgetFactory_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define __x_ABI_CWRLWidgetComponent_CIWidgetFactory_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define __x_ABI_CWRLWidgetComponent_CIWidgetFactory_GetIids(This,iidCount,iids)	\
    ( (This)->lpVtbl -> GetIids(This,iidCount,iids) ) 

#define __x_ABI_CWRLWidgetComponent_CIWidgetFactory_GetRuntimeClassName(This,className)	\
    ( (This)->lpVtbl -> GetRuntimeClassName(This,className) ) 

#define __x_ABI_CWRLWidgetComponent_CIWidgetFactory_GetTrustLevel(This,trustLevel)	\
    ( (This)->lpVtbl -> GetTrustLevel(This,trustLevel) ) 


#define __x_ABI_CWRLWidgetComponent_CIWidgetFactory_CreateInstance4(This,value,widget)	\
    ( (This)->lpVtbl -> CreateInstance4(This,value,widget) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* ____x_ABI_CWRLWidgetComponent_CIWidgetFactory_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_WRLWidgetComponent_0000_0002 */
/* [local] */ 

#ifndef RUNTIMECLASS_WRLWidgetComponent_Widget_DEFINED
#define RUNTIMECLASS_WRLWidgetComponent_Widget_DEFINED
extern const __declspec(selectany) WCHAR RuntimeClass_WRLWidgetComponent_Widget[] = L"WRLWidgetComponent.Widget";
#endif


/* interface __MIDL_itf_WRLWidgetComponent_0000_0002 */
/* [local] */ 



extern RPC_IF_HANDLE __MIDL_itf_WRLWidgetComponent_0000_0002_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_WRLWidgetComponent_0000_0002_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


