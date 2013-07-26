#pragma once

#include "../../../cc_winrt.hpp"


using cppcomponents::use;
using cc_winrt::InterfaceInspectable;
using cc_winrt::hstring;

// Interfaces from C:\Program Files (x86)\Windows Kits\8.1\Include\winrt\windows.devices.enumeration.idl
// That we need. Note not all methods have been declared exactly, just ones we need

enum DeviceWatcherStatus
{
	DeviceWatcherStatus_Created = 0,
	DeviceWatcherStatus_Started = 1,
	DeviceWatcherStatus_EnumerationCompleted = 2,
	DeviceWatcherStatus_Stopping = 3,
	DeviceWatcherStatus_Stopped = 4,
	DeviceWatcherStatus_Aborted = 5
};


namespace cross_compiler_interface{
	template<>
	struct cross_conversion<DeviceWatcherStatus>:public trivial_conversion<DeviceWatcherStatus>{};
}
struct InterfaceDeviceWatcher : public cppcomponents::define_interface <cppcomponents::uuid<0xC9EAB97D, 0x8F6B, 0x4F96, 0xA9F4, 0xABC814E22271>, cc_winrt::InterfaceInspectable>{

	// Our delegates
	typedef cppcomponents::event_delegate < void(use<InterfaceDeviceWatcher>, void*), cppcomponents::uuid<0x03c5a07b, 0x990c, 0x5d09, 0xb0b8, 0x5734eaa38222>> AddHandler;
	typedef cppcomponents::event_delegate < void(use<InterfaceDeviceWatcher>, void*), cppcomponents::uuid<0x906f1254, 0x79ad, 0x54fc, 0x93c4, 0xcdb99b437899>> UpdateHandler;
	typedef cppcomponents::event_delegate < void(use<InterfaceDeviceWatcher>, use<InterfaceInspectable>), cppcomponents::uuid<0x9234630f, 0x1ff4, 0x54f6, 0x9e3f, 0xac20369b7725>> CompletedHandler;
	typedef cppcomponents::event_delegate < void(use<InterfaceDeviceWatcher>, use<InterfaceInspectable>), cppcomponents::uuid<0x9234630f, 0x1ff4, 0x54f6, 0x9e3f, 0xac20369b7725>> StoppedHandler;


	std::int64_t add_Added(use<AddHandler>);
	void remove_Added(std::int64_t);

	std::int64_t add_Updated(use<UpdateHandler>);
	void remove_Updated(std::int64_t);

	// Not use removed handler so just accept IUnknown
	std::int64_t add_Removed(use<cppcomponents::InterfaceUnknown>);
	void remove_Removed(std::int64_t);

	std::int64_t add_EnumerationCompleted(use<CompletedHandler>);
	void remove_EnumerationCompleted(std::int64_t);

	std::int64_t add_Stopped(use<StoppedHandler>);
	void remove_Stopped(std::int64_t);


	DeviceWatcherStatus get_Status();

	void Start();

	void Stop();

	CPPCOMPONENTS_CONSTRUCT(InterfaceDeviceWatcher, add_Added, remove_Added, add_Updated, remove_Updated, add_Removed, remove_Removed, add_EnumerationCompleted, remove_EnumerationCompleted,
		add_Stopped, remove_Stopped, get_Status, Start, Stop);

	// Define the properties and events
	CPPCOMPONENTS_INTERFACE_EXTRAS{

		CPPCOMPONENTS_R_PROPERTY(get_Status) Status;

		CPPCOMPONENTS_EVENT(AddHandler, add_Added, remove_Added) Added;
		CPPCOMPONENTS_EVENT(UpdateHandler, add_Updated, remove_Updated) Updated;
		CPPCOMPONENTS_EVENT(CompletedHandler, add_EnumerationCompleted, remove_EnumerationCompleted) EnumerationCompleted;
		CPPCOMPONENTS_EVENT(StoppedHandler, add_Stopped, remove_Stopped) Stopped;

		CPPCOMPONENTS_INTERFACE_EXTRAS_CONSTRUCTOR(Status, Added, Updated, EnumerationCompleted, Stopped);

	};

};

struct InterfaceDeviceInformationStatics : cppcomponents::define_interface < cppcomponents::uuid<0xC17F100E, 0x3A46, 0x4A78, 0x8013, 0x769DC9B97390>, cc_winrt::InterfaceInspectable>{


	use<InterfaceInspectable> CreateFromIdAsync(hstring);
	use<InterfaceInspectable> CreateFromIdAsyncAdditionalProperties(hstring, use<InterfaceInspectable>);
	use<InterfaceInspectable> FindAllAsync();
	use<InterfaceInspectable> FindAllAsyncDeviceClass(std::int32_t);
	use<InterfaceInspectable> FindAllAsyncAqsFilter(hstring);
	use<InterfaceInspectable> FindAllAsyncAqsFilterAndAdditionalProperties(hstring, use<InterfaceInspectable>);
	use<InterfaceDeviceWatcher> CreateWatcher();
	use<InterfaceInspectable> CreateWatcherDeviceClass(std::int32_t);
	use<InterfaceInspectable> CreateWatcherAqsFilter(hstring);
	use<InterfaceInspectable> CreateWatcherAqsFilterAndAdditionalProperties(hstring, use<InterfaceInspectable>);


	CPPCOMPONENTS_CONSTRUCT(InterfaceDeviceInformationStatics, CreateFromIdAsync, CreateFromIdAsyncAdditionalProperties, FindAllAsync, FindAllAsyncDeviceClass,
		FindAllAsyncAqsFilter, FindAllAsyncAqsFilterAndAdditionalProperties, CreateWatcher, CreateWatcherDeviceClass, CreateWatcherAqsFilter, CreateWatcherAqsFilterAndAdditionalProperties);


};








inline hstring DeviceStatusId(){ return L"Windows.Devices.Enumeration.DeviceInformation"; };

typedef cc_winrt::winrt_runtime_class<DeviceStatusId, 
	cppcomponents::static_interfaces<InterfaceDeviceInformationStatics>> DeviceInformation_t;

typedef cc_winrt::use_winrt_runtime_class<DeviceInformation_t> DeviceInformation;

