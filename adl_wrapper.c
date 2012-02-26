/* Copyright (c) 2012 The adl_wrapper Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license
 * that can be found in the LICENSE.txt file.
 */

#if defined (_WIN32) || defined (_WIN64)
#include <windows.h>
#include <tchar.h>
#elif defined (__linux__)
#include <unistd.h>
#else
#error Unknown OS platform
#endif

#define INCLUDE_IN_ADL_WRAPPER_C
#include "adl_wrapper.h"
#undef INCLUDE_IN_ADL_WRAPPER_C

#include <stdio.h>
#include <stdlib.h>
#include <adl_sdk.h>

#ifndef DIRECT_LINK_ADL

static HMODULE gDll;

#define PREFIX_LENGTH (sizeof("Index_Of_") - 1)
static enum Indices {
	Index_Of_ADL_Main_Control_Create = 0,
	Index_Of_ADL_Main_Control_Refresh,
	Index_Of_ADL_Main_Control_Destroy,
	Index_Of_ADL_Graphics_Platform_Get,
	Index_Of_ADL_Adapter_Active_Get,
	Index_Of_ADL_Adapter_NumberOfAdapters_Get,
	Index_Of_ADL_Adapter_AdapterInfo_Get,
	Index_Of_ADL_Adapter_ASICFamilyType_Get,
	Index_Of_ADL_Adapter_Speed_Caps,
	Index_Of_ADL_Adapter_Speed_Get,
	Index_Of_ADL_Adapter_Speed_Set,
	Index_Of_ADL_Adapter_Accessibility_Get,
	Index_Of_ADL_Adapter_VideoBiosInfo_Get,
	Index_Of_ADL_Adapter_ID_Get,
	Index_Of_ADL_Adapter_CrossdisplayAdapterRole_Caps,
	Index_Of_ADL_Adapter_CrossdisplayInfo_Get,
	Index_Of_ADL_Adapter_CrossdisplayInfo_Set,
	Index_Of_ADL_Adapter_Crossfire_Caps,
	Index_Of_ADL_Adapter_Crossfire_Get,
	Index_Of_ADL_Adapter_Crossfire_Set,
	Index_Of_ADL_Display_DisplayInfo_Get,
	Index_Of_ADL_Display_NumberOfDisplays_Get,
	Index_Of_ADL_Display_PreservedAspectRatio_Get,
	Index_Of_ADL_Display_PreservedAspectRatio_Set,
	Index_Of_ADL_Display_ImageExpansion_Get,
	Index_Of_ADL_Display_ImageExpansion_Set,
	Index_Of_ADL_Display_Position_Get,
	Index_Of_ADL_Display_Position_Set,
	Index_Of_ADL_Display_Size_Get,
	Index_Of_ADL_Display_Size_Set,
	Index_Of_ADL_Display_AdjustCaps_Get,
	Index_Of_ADL_Display_Capabilities_Get,
	Index_Of_ADL_Display_ConnectedDisplays_Get,
	Index_Of_ADL_Display_DeviceConfig_Get,
	Index_Of_ADL_Display_Property_Get,
	Index_Of_ADL_Display_Property_Set,
	Index_Of_ADL_Display_SwitchingCapability_Get,
	Index_Of_ADL_Display_DitherState_Get,
	Index_Of_ADL_Display_DitherState_Set,
	Index_Of_ADL_Display_SupportedPixelFormat_Get,
	Index_Of_ADL_Display_PixelFormat_Get,
	Index_Of_ADL_Display_PixelFormat_Set,
	Index_Of_ADL_Display_ODClockInfo_Get,
	Index_Of_ADL_Display_ODClockConfig_Set,
	Index_Of_ADL_Display_AdjustmentCoherent_Get,
	Index_Of_ADL_Display_AdjustmentCoherent_Set,
	Index_Of_ADL_Display_ReducedBlanking_Get,
	Index_Of_ADL_Display_ReducedBlanking_Set,
	Index_Of_ADL_Display_FormatsOverride_Get,
	Index_Of_ADL_Display_FormatsOverride_Set,
	Index_Of_ADL_Display_MVPUCaps_Get,
	Index_Of_ADL_Display_MVPUStatus_Get,
	Index_Of_ADL_Adapter_Active_Set,
	Index_Of_ADL_Adapter_Active_SetPrefer,
	Index_Of_ADL_Adapter_Primary_Get,
	Index_Of_ADL_Adapter_Primary_Set,
	Index_Of_ADL_Adapter_ModeSwitch,
	Index_Of_ADL_Display_Modes_Get,
	Index_Of_ADL_Display_Modes_Set,
	Index_Of_ADL_Display_PossibleMode_Get,
	Index_Of_ADL_Display_ForcibleDisplay_Get,
	Index_Of_ADL_Display_ForcibleDisplay_Set,
	Index_Of_ADL_Adapter_NumberOfActivatableSources_Get,
	Index_Of_ADL_Adapter_Display_Caps,
	Index_Of_ADL_Display_DisplayMapConfig_Get,
	Index_Of_ADL_Display_DisplayMapConfig_Set,
	Index_Of_ADL_Display_PossibleMapping_Get,
	Index_Of_ADL_Display_DisplayMapConfig_Validate,
	Index_Of_ADL_Display_DisplayMapConfig_PossibleAddAndRemove,
	Index_Of_ADL_Display_SLSGrid_Caps,
	Index_Of_ADL_Display_SLSMapIndexList_Get,
	Index_Of_ADL_Display_SLSMapIndex_Get,
	Index_Of_ADL_Display_SLSMapConfig_Get,
	Index_Of_ADL_Display_SLSMapConfig_Create,
	Index_Of_ADL_Display_SLSMapConfig_Delete,
	Index_Of_ADL_Display_SLSMapConfig_SetState,
	Index_Of_ADL_Display_SLSMapConfig_Rearrange,
	Index_Of_ADL_Display_PossibleMode_WinXP_Get,
	Index_Of_ADL_Display_BezelOffsetSteppingSize_Get,
	Index_Of_ADL_Display_BezelOffset_Set,
	Index_Of_ADL_Display_BezelSupported_Validate,
	Index_Of_ADL_Display_ColorCaps_Get,
	Index_Of_ADL_Display_Color_Set,
	Index_Of_ADL_Display_Color_Get,
	Index_Of_ADL_Display_ColorTemperatureSource_Get,
	Index_Of_ADL_Display_ColorTemperatureSource_Set,
	Index_Of_ADL_Display_ModeTimingOverride_Get,
	Index_Of_ADL_Display_ModeTimingOverride_Set,
	Index_Of_ADL_Display_ModeTimingOverrideList_Get,
	Index_Of_ADL_Display_CustomizedModeListNum_Get,
	Index_Of_ADL_Display_CustomizedModeList_Get,
	Index_Of_ADL_Display_CustomizedMode_Add,
	Index_Of_ADL_Display_CustomizedMode_Delete,
	Index_Of_ADL_Display_CustomizedMode_Validate,
	Index_Of_ADL_Display_Underscan_Set,
	Index_Of_ADL_Display_Underscan_Get,
	Index_Of_ADL_Display_Overscan_Set,
	Index_Of_ADL_Display_Overscan_Get,
	Index_Of_ADL_Display_ControllerOverlayAdjustmentCaps_Get,
	Index_Of_ADL_Display_ControllerOverlayAdjustmentData_Get,
	Index_Of_ADL_Display_ControllerOverlayAdjustmentData_Set,
	Index_Of_ADL_Display_PowerXpressVersion_Get,
	Index_Of_ADL_Display_PowerXpressActiveGPU_Get,
	Index_Of_ADL_Display_PowerXpressActiveGPU_Set,
	Index_Of_ADL_Display_PowerXpress_AutoSwitchConfig_Get,
	Index_Of_ADL_Display_PowerXpress_AutoSwitchConfig_Set,
	Index_Of_ADL_DFP_BaseAudioSupport_Get,
	Index_Of_ADL_DFP_HDMISupport_Get,
	Index_Of_ADL_DFP_MVPUAnalogSupport_Get,
	Index_Of_ADL_DFP_PixelFormat_Caps,
	Index_Of_ADL_DFP_PixelFormat_Get,
	Index_Of_ADL_DFP_PixelFormat_Set,
	Index_Of_ADL_DFP_GPUScalingEnable_Get,
	Index_Of_ADL_DFP_GPUScalingEnable_Set,
	Index_Of_ADL_DFP_AllowOnlyCETimings_Get,
	Index_Of_ADL_DFP_AllowOnlyCETimings_Set,
	Index_Of_ADL_Display_TVCaps_Get,
	Index_Of_ADL_TV_Standard_Set,
	Index_Of_ADL_TV_Standard_Get,
	Index_Of_ADL_CV_DongleSettings_Get,
	Index_Of_ADL_CV_DongleSettings_Set,
	Index_Of_ADL_CV_DongleSettings_Reset,
	Index_Of_ADL_Overdrive5_CurrentActivity_Get,
	Index_Of_ADL_Overdrive5_ThermalDevices_Enum,
	Index_Of_ADL_Overdrive5_Temperature_Get,
	Index_Of_ADL_Overdrive5_FanSpeedInfo_Get,
	Index_Of_ADL_Overdrive5_FanSpeed_Get,
	Index_Of_ADL_Overdrive5_FanSpeed_Set,
	Index_Of_ADL_Overdrive5_FanSpeedToDefault_Set,
	Index_Of_ADL_Overdrive5_ODParameters_Get,
	Index_Of_ADL_Overdrive5_ODPerformanceLevels_Get,
	Index_Of_ADL_Overdrive5_ODPerformanceLevels_Set,
	Index_Of_ADL_Display_WriteAndReadI2CRev_Get,
	Index_Of_ADL_Display_WriteAndReadI2C,
	Index_Of_ADL_Display_DDCBlockAccess_Get,
	Index_Of_ADL_Display_DDCInfo_Get,
	Index_Of_ADL_Display_EdidData_Get,
	Index_Of_ADL_Workstation_Caps,
	Index_Of_ADL_Workstation_Stereo_Get,
	Index_Of_ADL_Workstation_Stereo_Set,
	Index_Of_ADL_Workstation_AdapterNumOfGLSyncConnectors_Get,
	Index_Of_ADL_Workstation_DisplayGenlockCapable_Get,
	Index_Of_ADL_Workstation_GLSyncModuleDetect_Get,
	Index_Of_ADL_Workstation_GLSyncModuleInfo_Get,
	Index_Of_ADL_Workstation_GLSyncGenlockConfiguration_Get,
	Index_Of_ADL_Workstation_GLSyncGenlockConfiguration_Set,
	Index_Of_ADL_Workstation_GLSyncPortState_Get,
	Index_Of_ADL_Workstation_GLSyncPortState_Set,
	Index_Of_ADL_Workstation_DisplayGLSyncMode_Get,
	Index_Of_ADL_Workstation_DisplayGLSyncMode_Set,
	Index_Of_ADL_Workstation_GLSyncSupportedTopology_Get,
	Index_Of_ADL_Workstation_LoadBalancing_Get,
	Index_Of_ADL_Workstation_LoadBalancing_Set,
	Index_Of_ADL_Workstation_LoadBalancing_Caps,

#ifdef __linux__
	Index_Of_ADL_Adapter_MemoryInfo_Get,
	Index_Of_ADL_Controller_Color_Set,
	Index_Of_ADL_Controller_Color_Get,
	Index_Of_ADL_DesktopConfig_Get,
	Index_Of_ADL_DesktopConfig_Set,
	Index_Of_ADL_NumberOfDisplayEnable_Get,
	Index_Of_ADL_DisplayEnable_Set,
	Index_Of_ADL_Display_IdentifyDisplay,
	Index_Of_ADL_Display_LUTColor_Set,
	Index_Of_ADL_Display_LUTColor_Get,
	Index_Of_ADL_Adapter_XScreenInfo_Get,
	Index_Of_ADL_Display_XrandrDisplayName_Get,
#endif

	Proc_Count
};

#define TO_PROC_NAME(symbol) (#symbol + PREFIX_LENGTH)
static const char* const gProcNames[Proc_Count] = {
	/*
	* The order of the entries in this array should be synced with enum Indices.
	*
	* If C99 Designated Initializers is supported that will be great.
	 * We can totally ignore the order of the entires define in this array.
	 *
	 * [Index_Of_ADL_Main_Control_Destroy] = TO_PROC_NAME(Index_Of_ADL_Main_Control_Destroy),
	 * [Index_Of_ADL_Main_Control_Create] = TO_PROC_NAME(Index_Of_ADL_Main_Control_Create),
	 */
	TO_PROC_NAME(Index_Of_ADL_Main_Control_Create), // will become "ADL_Main_Control_Create"
	TO_PROC_NAME(Index_Of_ADL_Main_Control_Refresh),
	TO_PROC_NAME(Index_Of_ADL_Main_Control_Destroy),
	TO_PROC_NAME(Index_Of_ADL_Graphics_Platform_Get),
	TO_PROC_NAME(Index_Of_ADL_Adapter_Active_Get),
	TO_PROC_NAME(Index_Of_ADL_Adapter_NumberOfAdapters_Get),
	TO_PROC_NAME(Index_Of_ADL_Adapter_AdapterInfo_Get),
	TO_PROC_NAME(Index_Of_ADL_Adapter_ASICFamilyType_Get),
	TO_PROC_NAME(Index_Of_ADL_Adapter_Speed_Caps),
	TO_PROC_NAME(Index_Of_ADL_Adapter_Speed_Get),
	TO_PROC_NAME(Index_Of_ADL_Adapter_Speed_Set),
	TO_PROC_NAME(Index_Of_ADL_Adapter_Accessibility_Get),
	TO_PROC_NAME(Index_Of_ADL_Adapter_VideoBiosInfo_Get),
	TO_PROC_NAME(Index_Of_ADL_Adapter_ID_Get),
	TO_PROC_NAME(Index_Of_ADL_Adapter_CrossdisplayAdapterRole_Caps),
	TO_PROC_NAME(Index_Of_ADL_Adapter_CrossdisplayInfo_Get),
	TO_PROC_NAME(Index_Of_ADL_Adapter_CrossdisplayInfo_Set),
	TO_PROC_NAME(Index_Of_ADL_Adapter_Crossfire_Caps),
	TO_PROC_NAME(Index_Of_ADL_Adapter_Crossfire_Get),
	TO_PROC_NAME(Index_Of_ADL_Adapter_Crossfire_Set),
	TO_PROC_NAME(Index_Of_ADL_Display_DisplayInfo_Get),
	TO_PROC_NAME(Index_Of_ADL_Display_NumberOfDisplays_Get),
	TO_PROC_NAME(Index_Of_ADL_Display_PreservedAspectRatio_Get),
	TO_PROC_NAME(Index_Of_ADL_Display_PreservedAspectRatio_Set),
	TO_PROC_NAME(Index_Of_ADL_Display_ImageExpansion_Get),
	TO_PROC_NAME(Index_Of_ADL_Display_ImageExpansion_Set),
	TO_PROC_NAME(Index_Of_ADL_Display_Position_Get),
	TO_PROC_NAME(Index_Of_ADL_Display_Position_Set),
	TO_PROC_NAME(Index_Of_ADL_Display_Size_Get),
	TO_PROC_NAME(Index_Of_ADL_Display_Size_Set),
	TO_PROC_NAME(Index_Of_ADL_Display_AdjustCaps_Get),
	TO_PROC_NAME(Index_Of_ADL_Display_Capabilities_Get),
	TO_PROC_NAME(Index_Of_ADL_Display_ConnectedDisplays_Get),
	TO_PROC_NAME(Index_Of_ADL_Display_DeviceConfig_Get),
	TO_PROC_NAME(Index_Of_ADL_Display_Property_Get),
	TO_PROC_NAME(Index_Of_ADL_Display_Property_Set),
	TO_PROC_NAME(Index_Of_ADL_Display_SwitchingCapability_Get),
	TO_PROC_NAME(Index_Of_ADL_Display_DitherState_Get),
	TO_PROC_NAME(Index_Of_ADL_Display_DitherState_Set),
	TO_PROC_NAME(Index_Of_ADL_Display_SupportedPixelFormat_Get),
	TO_PROC_NAME(Index_Of_ADL_Display_PixelFormat_Get),
	TO_PROC_NAME(Index_Of_ADL_Display_PixelFormat_Set),
	TO_PROC_NAME(Index_Of_ADL_Display_ODClockInfo_Get),
	TO_PROC_NAME(Index_Of_ADL_Display_ODClockConfig_Set),
	TO_PROC_NAME(Index_Of_ADL_Display_AdjustmentCoherent_Get),
	TO_PROC_NAME(Index_Of_ADL_Display_AdjustmentCoherent_Set),
	TO_PROC_NAME(Index_Of_ADL_Display_ReducedBlanking_Get),
	TO_PROC_NAME(Index_Of_ADL_Display_ReducedBlanking_Set),
	TO_PROC_NAME(Index_Of_ADL_Display_FormatsOverride_Get),
	TO_PROC_NAME(Index_Of_ADL_Display_FormatsOverride_Set),
	TO_PROC_NAME(Index_Of_ADL_Display_MVPUCaps_Get),
	TO_PROC_NAME(Index_Of_ADL_Display_MVPUStatus_Get),
	TO_PROC_NAME(Index_Of_ADL_Adapter_Active_Set),
	TO_PROC_NAME(Index_Of_ADL_Adapter_Active_SetPrefer),
	TO_PROC_NAME(Index_Of_ADL_Adapter_Primary_Get),
	TO_PROC_NAME(Index_Of_ADL_Adapter_Primary_Set),
	TO_PROC_NAME(Index_Of_ADL_Adapter_ModeSwitch),
	TO_PROC_NAME(Index_Of_ADL_Display_Modes_Get),
	TO_PROC_NAME(Index_Of_ADL_Display_Modes_Set),
	TO_PROC_NAME(Index_Of_ADL_Display_PossibleMode_Get),
	TO_PROC_NAME(Index_Of_ADL_Display_ForcibleDisplay_Get),
	TO_PROC_NAME(Index_Of_ADL_Display_ForcibleDisplay_Set),
	TO_PROC_NAME(Index_Of_ADL_Adapter_NumberOfActivatableSources_Get),
	TO_PROC_NAME(Index_Of_ADL_Adapter_Display_Caps),
	TO_PROC_NAME(Index_Of_ADL_Display_DisplayMapConfig_Get),
	TO_PROC_NAME(Index_Of_ADL_Display_DisplayMapConfig_Set),
	TO_PROC_NAME(Index_Of_ADL_Display_PossibleMapping_Get),
	TO_PROC_NAME(Index_Of_ADL_Display_DisplayMapConfig_Validate),
	TO_PROC_NAME(Index_Of_ADL_Display_DisplayMapConfig_PossibleAddAndRemove),
	TO_PROC_NAME(Index_Of_ADL_Display_SLSGrid_Caps),
	TO_PROC_NAME(Index_Of_ADL_Display_SLSMapIndexList_Get),
	TO_PROC_NAME(Index_Of_ADL_Display_SLSMapIndex_Get),
	TO_PROC_NAME(Index_Of_ADL_Display_SLSMapConfig_Get),
	TO_PROC_NAME(Index_Of_ADL_Display_SLSMapConfig_Create),
	TO_PROC_NAME(Index_Of_ADL_Display_SLSMapConfig_Delete),
	TO_PROC_NAME(Index_Of_ADL_Display_SLSMapConfig_SetState),
	TO_PROC_NAME(Index_Of_ADL_Display_SLSMapConfig_Rearrange),
	TO_PROC_NAME(Index_Of_ADL_Display_PossibleMode_WinXP_Get),
	TO_PROC_NAME(Index_Of_ADL_Display_BezelOffsetSteppingSize_Get),
	TO_PROC_NAME(Index_Of_ADL_Display_BezelOffset_Set),
	TO_PROC_NAME(Index_Of_ADL_Display_BezelSupported_Validate),
	TO_PROC_NAME(Index_Of_ADL_Display_ColorCaps_Get),
	TO_PROC_NAME(Index_Of_ADL_Display_Color_Set),
	TO_PROC_NAME(Index_Of_ADL_Display_Color_Get),
	TO_PROC_NAME(Index_Of_ADL_Display_ColorTemperatureSource_Get),
	TO_PROC_NAME(Index_Of_ADL_Display_ColorTemperatureSource_Set),
	TO_PROC_NAME(Index_Of_ADL_Display_ModeTimingOverride_Get),
	TO_PROC_NAME(Index_Of_ADL_Display_ModeTimingOverride_Set),
	TO_PROC_NAME(Index_Of_ADL_Display_ModeTimingOverrideList_Get),
	TO_PROC_NAME(Index_Of_ADL_Display_CustomizedModeListNum_Get),
	TO_PROC_NAME(Index_Of_ADL_Display_CustomizedModeList_Get),
	TO_PROC_NAME(Index_Of_ADL_Display_CustomizedMode_Add),
	TO_PROC_NAME(Index_Of_ADL_Display_CustomizedMode_Delete),
	TO_PROC_NAME(Index_Of_ADL_Display_CustomizedMode_Validate),
	TO_PROC_NAME(Index_Of_ADL_Display_Underscan_Set),
	TO_PROC_NAME(Index_Of_ADL_Display_Underscan_Get),
	TO_PROC_NAME(Index_Of_ADL_Display_Overscan_Set),
	TO_PROC_NAME(Index_Of_ADL_Display_Overscan_Get),
	TO_PROC_NAME(Index_Of_ADL_Display_ControllerOverlayAdjustmentCaps_Get),
	TO_PROC_NAME(Index_Of_ADL_Display_ControllerOverlayAdjustmentData_Get),
	TO_PROC_NAME(Index_Of_ADL_Display_ControllerOverlayAdjustmentData_Set),
	TO_PROC_NAME(Index_Of_ADL_Display_PowerXpressVersion_Get),
	TO_PROC_NAME(Index_Of_ADL_Display_PowerXpressActiveGPU_Get),
	TO_PROC_NAME(Index_Of_ADL_Display_PowerXpressActiveGPU_Set),
	TO_PROC_NAME(Index_Of_ADL_Display_PowerXpress_AutoSwitchConfig_Get),
	TO_PROC_NAME(Index_Of_ADL_Display_PowerXpress_AutoSwitchConfig_Set),
	TO_PROC_NAME(Index_Of_ADL_DFP_BaseAudioSupport_Get),
	TO_PROC_NAME(Index_Of_ADL_DFP_HDMISupport_Get),
	TO_PROC_NAME(Index_Of_ADL_DFP_MVPUAnalogSupport_Get),
	TO_PROC_NAME(Index_Of_ADL_DFP_PixelFormat_Caps),
	TO_PROC_NAME(Index_Of_ADL_DFP_PixelFormat_Get),
	TO_PROC_NAME(Index_Of_ADL_DFP_PixelFormat_Set),
	TO_PROC_NAME(Index_Of_ADL_DFP_GPUScalingEnable_Get),
	TO_PROC_NAME(Index_Of_ADL_DFP_GPUScalingEnable_Set),
	TO_PROC_NAME(Index_Of_ADL_DFP_AllowOnlyCETimings_Get),
	TO_PROC_NAME(Index_Of_ADL_DFP_AllowOnlyCETimings_Set),
	TO_PROC_NAME(Index_Of_ADL_Display_TVCaps_Get),
	TO_PROC_NAME(Index_Of_ADL_TV_Standard_Set),
	TO_PROC_NAME(Index_Of_ADL_TV_Standard_Get),
	TO_PROC_NAME(Index_Of_ADL_CV_DongleSettings_Get),
	TO_PROC_NAME(Index_Of_ADL_CV_DongleSettings_Set),
	TO_PROC_NAME(Index_Of_ADL_CV_DongleSettings_Reset),
	TO_PROC_NAME(Index_Of_ADL_Overdrive5_CurrentActivity_Get),
	TO_PROC_NAME(Index_Of_ADL_Overdrive5_ThermalDevices_Enum),
	TO_PROC_NAME(Index_Of_ADL_Overdrive5_Temperature_Get),
	TO_PROC_NAME(Index_Of_ADL_Overdrive5_FanSpeedInfo_Get),
	TO_PROC_NAME(Index_Of_ADL_Overdrive5_FanSpeed_Get),
	TO_PROC_NAME(Index_Of_ADL_Overdrive5_FanSpeed_Set),
	TO_PROC_NAME(Index_Of_ADL_Overdrive5_FanSpeedToDefault_Set),
	TO_PROC_NAME(Index_Of_ADL_Overdrive5_ODParameters_Get),
	TO_PROC_NAME(Index_Of_ADL_Overdrive5_ODPerformanceLevels_Get),
	TO_PROC_NAME(Index_Of_ADL_Overdrive5_ODPerformanceLevels_Set),
	TO_PROC_NAME(Index_Of_ADL_Display_WriteAndReadI2CRev_Get),
	TO_PROC_NAME(Index_Of_ADL_Display_WriteAndReadI2C),
	TO_PROC_NAME(Index_Of_ADL_Display_DDCBlockAccess_Get),
	TO_PROC_NAME(Index_Of_ADL_Display_DDCInfo_Get),
	TO_PROC_NAME(Index_Of_ADL_Display_EdidData_Get),
	TO_PROC_NAME(Index_Of_ADL_Workstation_Caps),
	TO_PROC_NAME(Index_Of_ADL_Workstation_Stereo_Get),
	TO_PROC_NAME(Index_Of_ADL_Workstation_Stereo_Set),
	TO_PROC_NAME(Index_Of_ADL_Workstation_AdapterNumOfGLSyncConnectors_Get),
	TO_PROC_NAME(Index_Of_ADL_Workstation_DisplayGenlockCapable_Get),
	TO_PROC_NAME(Index_Of_ADL_Workstation_GLSyncModuleDetect_Get),
	TO_PROC_NAME(Index_Of_ADL_Workstation_GLSyncModuleInfo_Get),
	TO_PROC_NAME(Index_Of_ADL_Workstation_GLSyncGenlockConfiguration_Get),
	TO_PROC_NAME(Index_Of_ADL_Workstation_GLSyncGenlockConfiguration_Set),
	TO_PROC_NAME(Index_Of_ADL_Workstation_GLSyncPortState_Get),
	TO_PROC_NAME(Index_Of_ADL_Workstation_GLSyncPortState_Set),
	TO_PROC_NAME(Index_Of_ADL_Workstation_DisplayGLSyncMode_Get),
	TO_PROC_NAME(Index_Of_ADL_Workstation_DisplayGLSyncMode_Set),
	TO_PROC_NAME(Index_Of_ADL_Workstation_GLSyncSupportedTopology_Get),
	TO_PROC_NAME(Index_Of_ADL_Workstation_LoadBalancing_Get),
	TO_PROC_NAME(Index_Of_ADL_Workstation_LoadBalancing_Set),
	TO_PROC_NAME(Index_Of_ADL_Workstation_LoadBalancing_Caps),

#ifdef __linux__
	TO_PROC_NAME(Index_Of_ADL_Adapter_MemoryInfo_Get),
	TO_PROC_NAME(Index_Of_ADL_Controller_Color_Set),
	TO_PROC_NAME(Index_Of_ADL_Controller_Color_Get),
	TO_PROC_NAME(Index_Of_ADL_DesktopConfig_Get),
	TO_PROC_NAME(Index_Of_ADL_DesktopConfig_Set),
	TO_PROC_NAME(Index_Of_ADL_NumberOfDisplayEnable_Get),
	TO_PROC_NAME(Index_Of_ADL_DisplayEnable_Set),
	TO_PROC_NAME(Index_Of_ADL_Display_IdentifyDisplay),
	TO_PROC_NAME(Index_Of_ADL_Display_LUTColor_Set),
	TO_PROC_NAME(Index_Of_ADL_Display_LUTColor_Get),
	TO_PROC_NAME(Index_Of_ADL_Adapter_XScreenInfo_Get),
	TO_PROC_NAME(Index_Of_ADL_Display_XrandrDisplayName_Get)
#endif
};

#define ASSIGN_PROC(name, type, pool) (name = (type)(pool[Index_Of_##name]))

int Init_ADL_Procs(void)
{
	void* procEntries[Proc_Count];
	void* proc;
	int i;

	gDll = LoadLibrary(_T("atiadlxx.dll"));
	if (gDll == NULL) {
		return ADL_ERR;
	}
	
	for (i = 0; i < Proc_Count; i++) {
		proc = GetProcAddress(gDll, gProcNames[i]);
		if (proc == NULL) {
			printf("%s\n", gProcNames[i]);
		}
		procEntries[i] = proc;
	}

	ASSIGN_PROC(ADL_Main_Control_Create, int(*)(ADL_MAIN_MALLOC_CALLBACK , int), procEntries);
	ASSIGN_PROC(ADL_Main_Control_Refresh, int(*)(void), procEntries);
	ASSIGN_PROC(ADL_Main_Control_Destroy, int(*)(void), procEntries);
	ASSIGN_PROC(ADL_Graphics_Platform_Get, int(*)(int *), procEntries);
	ASSIGN_PROC(ADL_Adapter_Active_Get, int(*)(int , int *), procEntries);
	ASSIGN_PROC(ADL_Adapter_NumberOfAdapters_Get, int(*)(int *), procEntries);
	ASSIGN_PROC(ADL_Adapter_AdapterInfo_Get, int(*)(LPAdapterInfo , int), procEntries);
	ASSIGN_PROC(ADL_Adapter_ASICFamilyType_Get, int(*)(int , int *, int *), procEntries);
	ASSIGN_PROC(ADL_Adapter_Speed_Caps, int(*)(int , int *, int *), procEntries);
	ASSIGN_PROC(ADL_Adapter_Speed_Get, int(*)(int , int *, int *), procEntries);
	ASSIGN_PROC(ADL_Adapter_Speed_Set, int(*)(int , int), procEntries);
	ASSIGN_PROC(ADL_Adapter_Accessibility_Get, int(*)(int , int *), procEntries);
	ASSIGN_PROC(ADL_Adapter_VideoBiosInfo_Get, int(*)(int , ADLBiosInfo *), procEntries);
	ASSIGN_PROC(ADL_Adapter_ID_Get, int(*)(int , int *), procEntries);
	ASSIGN_PROC(ADL_Adapter_CrossdisplayAdapterRole_Caps, int(*)(int , int *, int *, int *, int **, int *, int **, int *), procEntries);
	ASSIGN_PROC(ADL_Adapter_CrossdisplayInfo_Get, int(*)(int , int *, int *, int *, int **, int *, int **, int *), procEntries);
	ASSIGN_PROC(ADL_Adapter_CrossdisplayInfo_Set, int(*)(int , int , int , int , int *), procEntries);
	ASSIGN_PROC(ADL_Adapter_Crossfire_Caps, int(*)(int , int *, int *, ADLCrossfireComb **), procEntries);
	ASSIGN_PROC(ADL_Adapter_Crossfire_Get, int(*)(int , ADLCrossfireComb *, ADLCrossfireInfo *), procEntries);
	ASSIGN_PROC(ADL_Adapter_Crossfire_Set, int(*)(int , ADLCrossfireComb *), procEntries);
	ASSIGN_PROC(ADL_Display_DisplayInfo_Get, int(*)(int , int *, ADLDisplayInfo **, int), procEntries);
	ASSIGN_PROC(ADL_Display_NumberOfDisplays_Get, int(*)(int , int *), procEntries);
	ASSIGN_PROC(ADL_Display_PreservedAspectRatio_Get, int(*)(int , int , int *, int *, int *), procEntries);
	ASSIGN_PROC(ADL_Display_PreservedAspectRatio_Set, int(*)(int , int , int), procEntries);
	ASSIGN_PROC(ADL_Display_ImageExpansion_Get, int(*)(int , int , int *, int *, int *), procEntries);
	ASSIGN_PROC(ADL_Display_ImageExpansion_Set, int(*)(int , int , int), procEntries);
	ASSIGN_PROC(ADL_Display_Position_Get, int(*)(int , int , int *, int *, int *, int *, int *, int *, int *, int *, int *, int *), procEntries);
	ASSIGN_PROC(ADL_Display_Position_Set, int(*)(int , int , int , int), procEntries);
	ASSIGN_PROC(ADL_Display_Size_Get, int(*)(int , int , int *, int *, int *, int *, int *, int *, int *, int *, int *, int *), procEntries);
	ASSIGN_PROC(ADL_Display_Size_Set, int(*)(int , int , int , int), procEntries);
	ASSIGN_PROC(ADL_Display_AdjustCaps_Get, int(*)(int , int , int *), procEntries);
	ASSIGN_PROC(ADL_Display_Capabilities_Get, int(*)(int , int *, int *), procEntries);
	ASSIGN_PROC(ADL_Display_ConnectedDisplays_Get, int(*)(int , int *), procEntries);
	ASSIGN_PROC(ADL_Display_DeviceConfig_Get, int(*)(int , int , ADLDisplayConfig *), procEntries);
	ASSIGN_PROC(ADL_Display_Property_Get, int(*)(int , int , ADLDisplayProperty *), procEntries);
	ASSIGN_PROC(ADL_Display_Property_Set, int(*)(int , int , ADLDisplayProperty *), procEntries);
	ASSIGN_PROC(ADL_Display_SwitchingCapability_Get, int(*)(int , int *), procEntries);
	ASSIGN_PROC(ADL_Display_DitherState_Get, int(*)(int , int , int *), procEntries);
	ASSIGN_PROC(ADL_Display_DitherState_Set, int(*)(int , int , int), procEntries);
	ASSIGN_PROC(ADL_Display_SupportedPixelFormat_Get, int(*)(int , int , int *), procEntries);
	ASSIGN_PROC(ADL_Display_PixelFormat_Get, int(*)(int , int , int *), procEntries);
	ASSIGN_PROC(ADL_Display_PixelFormat_Set, int(*)(int , int , int), procEntries);
	ASSIGN_PROC(ADL_Display_ODClockInfo_Get, int(*)(int , ADLAdapterODClockInfo *), procEntries);
	ASSIGN_PROC(ADL_Display_ODClockConfig_Set, int(*)(int , ADLAdapterODClockConfig *), procEntries);
	ASSIGN_PROC(ADL_Display_AdjustmentCoherent_Get, int(*)(int , int , int *, int *), procEntries);
	ASSIGN_PROC(ADL_Display_AdjustmentCoherent_Set, int(*)(int , int , int), procEntries);
	ASSIGN_PROC(ADL_Display_ReducedBlanking_Get, int(*)(int , int , int *, int *), procEntries);
	ASSIGN_PROC(ADL_Display_ReducedBlanking_Set, int(*)(int , int , int), procEntries);
	ASSIGN_PROC(ADL_Display_FormatsOverride_Get, int(*)(int , int , int *, int *, int *), procEntries);
	ASSIGN_PROC(ADL_Display_FormatsOverride_Set, int(*)(int , int , int), procEntries);
	ASSIGN_PROC(ADL_Display_MVPUCaps_Get, int(*)(int , ADLMVPUCaps *), procEntries);
	ASSIGN_PROC(ADL_Display_MVPUStatus_Get, int(*)(int , ADLMVPUStatus *), procEntries);
	ASSIGN_PROC(ADL_Adapter_Active_Set, int(*)(int , int , int *), procEntries);
	ASSIGN_PROC(ADL_Adapter_Active_SetPrefer, int(*)(int , int , int , ADLDisplayTarget *, int *), procEntries);
	ASSIGN_PROC(ADL_Adapter_Primary_Get, int(*)(int *), procEntries);
	ASSIGN_PROC(ADL_Adapter_Primary_Set, int(*)(int), procEntries);
	ASSIGN_PROC(ADL_Adapter_ModeSwitch, int(*)(int), procEntries);
	ASSIGN_PROC(ADL_Display_Modes_Get, int(*)(int , int , int *, ADLMode **), procEntries);
	ASSIGN_PROC(ADL_Display_Modes_Set, int(*)(int , int , int , ADLMode *), procEntries);
	ASSIGN_PROC(ADL_Display_PossibleMode_Get, int(*)(int , int *, ADLMode **), procEntries);
	ASSIGN_PROC(ADL_Display_ForcibleDisplay_Get, int(*)(int , int , int *), procEntries);
	ASSIGN_PROC(ADL_Display_ForcibleDisplay_Set, int(*)(int , int , int), procEntries);
	ASSIGN_PROC(ADL_Adapter_NumberOfActivatableSources_Get, int(*)(int , int *, ADLActivatableSource **), procEntries);
	ASSIGN_PROC(ADL_Adapter_Display_Caps, int(*)(int , int *, ADLAdapterDisplayCap **), procEntries);
	ASSIGN_PROC(ADL_Display_DisplayMapConfig_Get, int(*)(int , int *, ADLDisplayMap **, int *, ADLDisplayTarget **, int), procEntries);
	ASSIGN_PROC(ADL_Display_DisplayMapConfig_Set, int(*)(int , int , ADLDisplayMap *, int , ADLDisplayTarget *), procEntries);
	ASSIGN_PROC(ADL_Display_PossibleMapping_Get, int(*)(int , int , ADLPossibleMapping *, int , int *, ADLPossibleMapping **), procEntries);
	ASSIGN_PROC(ADL_Display_DisplayMapConfig_Validate, int(*)(int , int , ADLPossibleMap *, int *, ADLPossibleMapResult **), procEntries);
	ASSIGN_PROC(ADL_Display_DisplayMapConfig_PossibleAddAndRemove, int(*)(int , int , ADLDisplayMap *, int , ADLDisplayTarget *, int *, ADLDisplayTarget **, int *, ADLDisplayTarget **), procEntries);
	ASSIGN_PROC(ADL_Display_SLSGrid_Caps, int(*)(int , int *, ADLSLSGrid **, int), procEntries);
	ASSIGN_PROC(ADL_Display_SLSMapIndexList_Get, int(*)(int , int *, int **, int), procEntries);
	ASSIGN_PROC(ADL_Display_SLSMapIndex_Get, int(*)(int , int , ADLDisplayTarget *, int *), procEntries);
	ASSIGN_PROC(ADL_Display_SLSMapConfig_Get, int(*)(int , int , ADLSLSMap *, int *, ADLSLSTarget **, int *, ADLSLSMode **, int *, ADLBezelTransientMode **, int *, ADLBezelTransientMode **, int *, ADLSLSOffset **, int), procEntries);
	ASSIGN_PROC(ADL_Display_SLSMapConfig_Create, int(*)(int , ADLSLSMap , int , ADLSLSTarget *, int , int *, int), procEntries);
	ASSIGN_PROC(ADL_Display_SLSMapConfig_Delete, int(*)(int , int), procEntries);
	ASSIGN_PROC(ADL_Display_SLSMapConfig_SetState, int(*)(int , int , int), procEntries);
	ASSIGN_PROC(ADL_Display_SLSMapConfig_Rearrange, int(*)(int , int , int , ADLSLSTarget *, ADLSLSMap , int), procEntries);
	ASSIGN_PROC(ADL_Display_PossibleMode_WinXP_Get, int(*)(int , int , ADLDisplayTarget *, int , int , int *, ADLMode **), procEntries);
	ASSIGN_PROC(ADL_Display_BezelOffsetSteppingSize_Get, int(*)(int , int *, ADLBezelOffsetSteppingSize **), procEntries);
	ASSIGN_PROC(ADL_Display_BezelOffset_Set, int(*)(int , int , int , LPADLSLSOffset , ADLSLSMap , int), procEntries);
	ASSIGN_PROC(ADL_Display_BezelSupported_Validate, int(*)(int , int , LPADLPossibleSLSMap , int *, LPADLPossibleMapResult *), procEntries);
	ASSIGN_PROC(ADL_Display_ColorCaps_Get, int(*)(int , int , int *, int *), procEntries);
	ASSIGN_PROC(ADL_Display_Color_Set, int(*)(int , int , int , int), procEntries);
	ASSIGN_PROC(ADL_Display_Color_Get, int(*)(int , int , int , int *, int *, int *, int *, int *), procEntries);
	ASSIGN_PROC(ADL_Display_ColorTemperatureSource_Get, int(*)(int , int , int *), procEntries);
	ASSIGN_PROC(ADL_Display_ColorTemperatureSource_Set, int(*)(int , int , int), procEntries);
	ASSIGN_PROC(ADL_Display_ModeTimingOverride_Get, int(*)(int , int , ADLDisplayMode *, ADLDisplayModeInfo *), procEntries);
	ASSIGN_PROC(ADL_Display_ModeTimingOverride_Set, int(*)(int , int , ADLDisplayModeInfo *, int), procEntries);
	ASSIGN_PROC(ADL_Display_ModeTimingOverrideList_Get, int(*)(int , int , int , ADLDisplayModeInfo *, int *), procEntries);
	ASSIGN_PROC(ADL_Display_CustomizedModeListNum_Get, int(*)(int , int , int *), procEntries);
	ASSIGN_PROC(ADL_Display_CustomizedModeList_Get, int(*)(int , int , ADLCustomMode *, int), procEntries);
	ASSIGN_PROC(ADL_Display_CustomizedMode_Add, int(*)(int , int , ADLCustomMode), procEntries);
	ASSIGN_PROC(ADL_Display_CustomizedMode_Delete, int(*)(int , int , int), procEntries);
	ASSIGN_PROC(ADL_Display_CustomizedMode_Validate, int(*)(int , int , ADLCustomMode , int *), procEntries);
	ASSIGN_PROC(ADL_Display_Underscan_Set, int(*)(int , int , int), procEntries);
	ASSIGN_PROC(ADL_Display_Underscan_Get, int(*)(int , int , int *, int *, int *, int *, int *), procEntries);
	ASSIGN_PROC(ADL_Display_Overscan_Set, int(*)(int , int , int), procEntries);
	ASSIGN_PROC(ADL_Display_Overscan_Get, int(*)(int , int , int *, int *, int *, int *, int *), procEntries);
	ASSIGN_PROC(ADL_Display_ControllerOverlayAdjustmentCaps_Get, int(*)(int , ADLControllerOverlayInput *, ADLControllerOverlayInfo *), procEntries);
	ASSIGN_PROC(ADL_Display_ControllerOverlayAdjustmentData_Get, int(*)(int , ADLControllerOverlayInput *), procEntries);
	ASSIGN_PROC(ADL_Display_ControllerOverlayAdjustmentData_Set, int(*)(int , ADLControllerOverlayInput *), procEntries);
	ASSIGN_PROC(ADL_Display_PowerXpressVersion_Get, int(*)(int , int *), procEntries);
	ASSIGN_PROC(ADL_Display_PowerXpressActiveGPU_Get, int(*)(int , int *), procEntries);
	ASSIGN_PROC(ADL_Display_PowerXpressActiveGPU_Set, int(*)(int , int , int *), procEntries);
	ASSIGN_PROC(ADL_Display_PowerXpress_AutoSwitchConfig_Get, int(*)(int , int *, int *), procEntries);
	ASSIGN_PROC(ADL_Display_PowerXpress_AutoSwitchConfig_Set, int(*)(int , int , int), procEntries);
	ASSIGN_PROC(ADL_DFP_BaseAudioSupport_Get, int(*)(int , int , int *), procEntries);
	ASSIGN_PROC(ADL_DFP_HDMISupport_Get, int(*)(int , int , int *), procEntries);
	ASSIGN_PROC(ADL_DFP_MVPUAnalogSupport_Get, int(*)(int , int , int *), procEntries);
	ASSIGN_PROC(ADL_DFP_PixelFormat_Caps, int(*)(int , int , int *, int *), procEntries);
	ASSIGN_PROC(ADL_DFP_PixelFormat_Get, int(*)(int , int , int *, int *), procEntries);
	ASSIGN_PROC(ADL_DFP_PixelFormat_Set, int(*)(int , int , int), procEntries);
	ASSIGN_PROC(ADL_DFP_GPUScalingEnable_Get, int(*)(int , int , int *, int *, int *), procEntries);
	ASSIGN_PROC(ADL_DFP_GPUScalingEnable_Set, int(*)(int , int , int), procEntries);
	ASSIGN_PROC(ADL_DFP_AllowOnlyCETimings_Get, int(*)(int , int , int *, int *, int *), procEntries);
	ASSIGN_PROC(ADL_DFP_AllowOnlyCETimings_Set, int(*)(int , int , int), procEntries);
	ASSIGN_PROC(ADL_Display_TVCaps_Get, int(*)(int , int , int *), procEntries);
	ASSIGN_PROC(ADL_TV_Standard_Set, int(*)(int , int , int), procEntries);
	ASSIGN_PROC(ADL_TV_Standard_Get, int(*)(int , int , int *, int *, int *), procEntries);
	ASSIGN_PROC(ADL_CV_DongleSettings_Get, int(*)(int , int , int *, int *, int *), procEntries);
	ASSIGN_PROC(ADL_CV_DongleSettings_Set, int(*)(int , int , int), procEntries);
	ASSIGN_PROC(ADL_CV_DongleSettings_Reset, int(*)(int , int), procEntries);
	ASSIGN_PROC(ADL_Overdrive5_CurrentActivity_Get, int(*)(int , ADLPMActivity *), procEntries);
	ASSIGN_PROC(ADL_Overdrive5_ThermalDevices_Enum, int(*)(int , int , ADLThermalControllerInfo *), procEntries);
	ASSIGN_PROC(ADL_Overdrive5_Temperature_Get, int(*)(int , int , ADLTemperature *), procEntries);
	ASSIGN_PROC(ADL_Overdrive5_FanSpeedInfo_Get, int(*)(int , int , ADLFanSpeedInfo *), procEntries);
	ASSIGN_PROC(ADL_Overdrive5_FanSpeed_Get, int(*)(int , int , ADLFanSpeedValue *), procEntries);
	ASSIGN_PROC(ADL_Overdrive5_FanSpeed_Set, int(*)(int , int , ADLFanSpeedValue *), procEntries);
	ASSIGN_PROC(ADL_Overdrive5_FanSpeedToDefault_Set, int(*)(int , int), procEntries);
	ASSIGN_PROC(ADL_Overdrive5_ODParameters_Get, int(*)(int , ADLODParameters *), procEntries);
	ASSIGN_PROC(ADL_Overdrive5_ODPerformanceLevels_Get, int(*)(int , int , ADLODPerformanceLevels *), procEntries);
	ASSIGN_PROC(ADL_Overdrive5_ODPerformanceLevels_Set, int(*)(int , ADLODPerformanceLevels *), procEntries);
	ASSIGN_PROC(ADL_Display_WriteAndReadI2CRev_Get, int(*)(int , int *, int *), procEntries);
	ASSIGN_PROC(ADL_Display_WriteAndReadI2C, int(*)(int , ADLI2C *), procEntries);
	ASSIGN_PROC(ADL_Display_DDCBlockAccess_Get, int(*)(int , int , int , int , int , char *, int *, char *), procEntries);
	ASSIGN_PROC(ADL_Display_DDCInfo_Get, int(*)(int , int , ADLDDCInfo *), procEntries);
	ASSIGN_PROC(ADL_Display_EdidData_Get, int(*)(int , int , ADLDisplayEDIDData *), procEntries);
	ASSIGN_PROC(ADL_Workstation_Caps, int(*)(int , int *, int *), procEntries);
	ASSIGN_PROC(ADL_Workstation_Stereo_Get, int(*)(int , int *, int *), procEntries);
	ASSIGN_PROC(ADL_Workstation_Stereo_Set, int(*)(int , int), procEntries);
	ASSIGN_PROC(ADL_Workstation_AdapterNumOfGLSyncConnectors_Get, int(*)(int , int *), procEntries);
	ASSIGN_PROC(ADL_Workstation_DisplayGenlockCapable_Get, int(*)(int , int , int *), procEntries);
	ASSIGN_PROC(ADL_Workstation_GLSyncModuleDetect_Get, int(*)(int , int , ADLGLSyncModuleID *), procEntries);
	ASSIGN_PROC(ADL_Workstation_GLSyncModuleInfo_Get, int(*)(int , int , int *, int *, int *, int *, ADLGLSyncPortCaps **), procEntries);
	ASSIGN_PROC(ADL_Workstation_GLSyncGenlockConfiguration_Get, int(*)(int , int , int , ADLGLSyncGenlockConfig *), procEntries);
	ASSIGN_PROC(ADL_Workstation_GLSyncGenlockConfiguration_Set, int(*)(int , int , ADLGLSyncGenlockConfig), procEntries);
	ASSIGN_PROC(ADL_Workstation_GLSyncPortState_Get, int(*)(int , int , int , int , ADLGlSyncPortInfo *, int **), procEntries);
	ASSIGN_PROC(ADL_Workstation_GLSyncPortState_Set, int(*)(int , int , ADLGlSyncPortControl), procEntries);
	ASSIGN_PROC(ADL_Workstation_DisplayGLSyncMode_Get, int(*)(int , int , ADLGlSyncMode *), procEntries);
	ASSIGN_PROC(ADL_Workstation_DisplayGLSyncMode_Set, int(*)(int , int , ADLGlSyncMode), procEntries);
	ASSIGN_PROC(ADL_Workstation_GLSyncSupportedTopology_Get, int(*)(int , int , ADLGlSyncMode2 *, int *, ADLGlSyncMode2 **), procEntries);
	ASSIGN_PROC(ADL_Workstation_LoadBalancing_Get, int(*)(int *, int *, int *), procEntries);
	ASSIGN_PROC(ADL_Workstation_LoadBalancing_Set, int(*)(int), procEntries);
	ASSIGN_PROC(ADL_Workstation_LoadBalancing_Caps, int(*)(int , int *, int *), procEntries);

#ifdef __linux__
	ASSIGN_PROC(ADL_Adapter_MemoryInfo_Get, int(*)(int , ADLMemoryInfo *), procEntries);
	ASSIGN_PROC(ADL_Controller_Color_Set, int(*)(int , int , ADLGamma), procEntries);
	ASSIGN_PROC(ADL_Controller_Color_Get, int(*)(int , int , ADLGamma *, ADLGamma *, ADLGamma *, ADLGamma *), procEntries);
	ASSIGN_PROC(ADL_DesktopConfig_Get, int(*)(int , int *), procEntries);
	ASSIGN_PROC(ADL_DesktopConfig_Set, int(*)(int , int), procEntries);
	ASSIGN_PROC(ADL_NumberOfDisplayEnable_Get, int(*)(int , int *), procEntries);
	ASSIGN_PROC(ADL_DisplayEnable_Set, int(*)(int , int *, int , int), procEntries);
	ASSIGN_PROC(ADL_Display_IdentifyDisplay, int(*)(int , int , int , int , int , int , int), procEntries);
	ASSIGN_PROC(ADL_Display_LUTColor_Set, int(*)(int , int , ADLGamma), procEntries);
	ASSIGN_PROC(ADL_Display_LUTColor_Get, int(*)(int , int , ADLGamma *, ADLGamma *, ADLGamma *, ADLGamma *), procEntries);
	ASSIGN_PROC(ADL_Adapter_XScreenInfo_Get, int(*)(LPXScreenInfo , int), procEntries);
	ASSIGN_PROC(ADL_Display_XrandrDisplayName_Get, int(*)(int , int , char *, int), procEntries);
#endif

	return ADL_OK;
}

void Deinit_ADL_Procs(void)
{
	FreeLibrary(gDll);
}

#else //#ifndef DIRECT_LINK_ADL

int Init_ADL_Proces(void)
{
	return ADL_OK;
}

void Deinit_ADL_Procs(void)
{
}

#endif //#ifndef DIRECT_LINK_ADL

void* __stdcall Main_Malloc_Callback(int n)
{
	return malloc(n);
}

