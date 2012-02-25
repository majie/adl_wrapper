#ifndef ADL_WRAPPER_H
#define ADL_WRAPPER_H

/*
 * About DIRECT_LINK_ADL
 *
 * It is recommended to #undef DIRECT_LINK_ADL On Windows and
 * to #define DIRECT_LINK_ADL On Linux.
 *
 * On Windows, to link to a .dll you need a .lib file, which
 * is not provided in the adl sdk.
 *
 * But you can generate one by following the instructions here.
 * http://wiki.videolan.org/GenerateLibFromDll
 *
 * While On Linux, you can link to a .so file directly.
 */

#ifdef __linux__
#define LINUX // used in adl_sdk.h and adl_structures.h
#define DIRECT_LINK_ADL
#endif

#if (defined (_WIN32) || defined (_WIN64)) && defined (DIRECT_LINK_ADL)
#warning DIRECT_LINK_ADL on Windows
#endif

#include <adl_sdk.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef DIRECT_LINK_ADL
int Init_ADL_Procs(void);
void Deinit_ADL_Procs(void);
#endif

void* __stdcall Main_Malloc_Callback(int);

#if defined (INCLUDE_IN_ADL_WRAPPER_C)
#define EXTERN_ADL
#else
#define EXTERN_ADL extern
#endif

#ifdef DIRECT_LINK_ADL
#define DECLARE_ADL_PROC(return_type, name, param) \
	return_type name param
#else
#define DECLARE_ADL_PROC(return_type, name, param) \
	return_type (*name) param
#endif

EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Main_Control_Create, (ADL_MAIN_MALLOC_CALLBACK callback, int iEnumConnectedAdapters));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Main_Control_Refresh, (void));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Main_Control_Destroy, (void));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Graphics_Platform_Get, (int *lpPlatForm));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Adapter_Active_Get, (int iAdapterIndex, int *lpStatus));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Adapter_NumberOfAdapters_Get, (int *lpNumAdapters));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Adapter_AdapterInfo_Get, (LPAdapterInfo lpInfo, int iInputSize));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Adapter_ASICFamilyType_Get, (int iAdapterIndex, int *lpAsicTypes, int *lpValids));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Adapter_Speed_Caps, (int iAdapterIndex, int *lpCaps, int *lpValid));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Adapter_Speed_Get, (int iAdapterIndex, int *lpCurrent, int *lpDefault));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Adapter_Speed_Set, (int iAdapterIndex, int iSpeed));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Adapter_Accessibility_Get, (int iAdapterIndex, int *lpAccessibility));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Adapter_VideoBiosInfo_Get, (int iAdapterIndex, ADLBiosInfo *lpBiosInfo));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Adapter_ID_Get, (int iAdapterIndex, int *lpAdapterID));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Adapter_CrossdisplayAdapterRole_Caps, (int iAdapterIndex, int *lpCrossDisplaySupport, int *lpAdapterRole, int *lpNumPossDisplayAdapters, int **lppPossDisplayAdapters, int *lpNnumPosRenderingAdapters, int **lppPosRenderingAdapters, int *lpErrorStatus));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Adapter_CrossdisplayInfo_Get, (int iAdapterIndex, int *lpAdapterRole, int *lpCrossdisplayMode, int *lpNumDisplayAdapters, int **lppDisplayAdapters, int *lpNumRenderingAdapters, int **lppRenderingAdapters, int *lpErrorCodeStatus));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Adapter_CrossdisplayInfo_Set, (int iAdapterIndex, int iDisplayAdapterIndex, int iRenderingAdapterIndex, int crossdisplayMode, int *lpErrorCode));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Adapter_Crossfire_Caps, (int iAdapterIndex, int *lpPreferred, int *lpNumComb, ADLCrossfireComb **ppCrossfireComb));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Adapter_Crossfire_Get, (int iAdapterIndex, ADLCrossfireComb *lpCrossfireComb, ADLCrossfireInfo *lpCrossfireInfo));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Adapter_Crossfire_Set, (int iAdapterIndex, ADLCrossfireComb *lpCrossfireComb));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Display_DisplayInfo_Get, (int iAdapterIndex, int *lpNumDisplays, ADLDisplayInfo **lppInfo, int iForceDetect));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Display_NumberOfDisplays_Get, (int iAdapterIndex, int *lpNumDisplays));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Display_PreservedAspectRatio_Get, (int iAdapterIndex, int iDisplayIndex, int *lpSupport, int *lpCurrent, int *lpDefault));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Display_PreservedAspectRatio_Set, (int iAdapterIndex, int iDisplayIndex, int iCurrent));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Display_ImageExpansion_Get, (int iAdapterIndex, int iDisplayIndex, int *lpSupport, int *lpCurrent, int *lpDefault));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Display_ImageExpansion_Set, (int iAdapterIndex, int iDisplayIndex, int iCurrent));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Display_Position_Get, (int iAdapterIndex, int iDisplayIndex, int *lpX, int *lpY, int *lpXDefault, int *lpYDefault, int *lpMinX, int *lpMinY, int *lpMaxX, int *lpMaxY, int *lpStepX, int *lpStepY));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Display_Position_Set, (int iAdapterIndex, int iDisplayIndex, int iX, int iY));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Display_Size_Get, (int iAdapterIndex, int iDisplayIndex, int *lpWidth, int *lpHeight, int *lpDefaultWidth, int *lpDefaultHeight, int *lpMinWidth, int *lpMinHeight, int *lpMaxWidth, int *lpMaxHeight, int *lpStepWidth, int *lpStepHeight));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Display_Size_Set, (int iAdapterIndex, int iDisplayIndex, int iWidth, int iHeight));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Display_AdjustCaps_Get, (int iAdapterIndex, int iDisplayIndex, int *lpInfo));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Display_Capabilities_Get, (int iAdapterIndex, int *lpNumberOfControlers, int *lpNumberOfDisplays));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Display_ConnectedDisplays_Get, (int iAdapterIndex, int *lpConnections));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Display_DeviceConfig_Get, (int iAdapterIndex, int iDisplayIndex, ADLDisplayConfig *lpDisplayConfig));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Display_Property_Get, (int iAdapterIndex, int iDisplayIndex, ADLDisplayProperty *lpDisplayProperty));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Display_Property_Set, (int iAdapterIndex, int iDisplayIndex, ADLDisplayProperty *lpDisplayProperty));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Display_SwitchingCapability_Get, (int iAdapterIndex, int *lpResult));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Display_DitherState_Get, (int iAdapterIndex, int iDisplayIndex, int *lpDitherState));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Display_DitherState_Set, (int iAdapterIndex, int iDisplayIndex, int iDitherState));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Display_SupportedPixelFormat_Get, (int iAdapterIndex, int iDisplayIndex, int *lpPixelFormat));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Display_PixelFormat_Get, (int iAdapterIndex, int iDisplayIndex, int *lpPixelFormat));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Display_PixelFormat_Set, (int iAdapterIndex, int iDisplayIndex, int iPixelFormat));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Display_ODClockInfo_Get, (int iAdapterIndex, ADLAdapterODClockInfo *lpOdClockInfo));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Display_ODClockConfig_Set, (int iAdapterIndex, ADLAdapterODClockConfig *lpOdClockConfig));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Display_AdjustmentCoherent_Get, (int iAdapterIndex, int iDisplayIndex, int *lpAdjustmentCoherentCurrent, int *lpAdjustmentCoherentDefault));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Display_AdjustmentCoherent_Set, (int iAdapterIndex, int iDisplayIndex, int iAdjustmentCoherent));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Display_ReducedBlanking_Get, (int iAdapterIndex, int iDisplayIndex, int *lpReducedBlankingCurrent, int *lpReducedBlankingDefault));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Display_ReducedBlanking_Set, (int iAdapterIndex, int iDisplayIndex, int iReducedBlanking));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Display_FormatsOverride_Get, (int iAdapterIndex, int iDisplayIndex, int *lpSettingsSupported, int *lpSettingsSupportedEx, int *lpCurSettings));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Display_FormatsOverride_Set, (int iAdapterIndex, int iDisplayIndex, int iOverrideSettings));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Display_MVPUCaps_Get, (int iAdapterIndex, ADLMVPUCaps *lpMvpuCaps));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Display_MVPUStatus_Get, (int iAdapterIndex, ADLMVPUStatus *lpMvpuStatus));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Adapter_Active_Set, (int iAdapterIndex, int iStatus, int *lpNewlyActivate));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Adapter_Active_SetPrefer, (int iAdapterIndex, int iStatus, int iNumPreferTarget, ADLDisplayTarget *lpPreferTarget, int *lpNewlyActivate));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Adapter_Primary_Get, (int *lpPrimaryAdapterIndex));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Adapter_Primary_Set, (int iAdapterIndex));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Adapter_ModeSwitch, (int iAdapterIndex));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Display_Modes_Get, (int iAdapterIndex, int iDisplayIndex, int *lpNumModes, ADLMode **lppModes));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Display_Modes_Set, (int iAdapterIndex, int iDisplayIndex, int iNumModes, ADLMode *lpModes));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Display_PossibleMode_Get, (int iAdapterIndex, int *lpNumModes, ADLMode **lppModes));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Display_ForcibleDisplay_Get, (int iAdapterIndex, int iDisplayIndex, int *lpStatus));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Display_ForcibleDisplay_Set, (int iAdapterIndex, int iDisplayIndex, int iStatus));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Adapter_NumberOfActivatableSources_Get, (int iAdapterIndex, int *lpNumSources, ADLActivatableSource **lppSources));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Adapter_Display_Caps, (int iAdapterIndex, int *lpNumDisplayCaps, ADLAdapterDisplayCap **lppAdapterDisplayCaps));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Display_DisplayMapConfig_Get, (int iAdapterIndex, int *lpNumDisplayMap, ADLDisplayMap **lppDisplayMap, int *lpNumDisplayTarget, ADLDisplayTarget **lppDisplayTarget, int iOptions));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Display_DisplayMapConfig_Set, (int iAdapterIndex, int iNumDisplayMap, ADLDisplayMap *lpDisplayMap, int iNumDisplayTarget, ADLDisplayTarget *lpDisplayTarget));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Display_PossibleMapping_Get, (int iAdapterIndex, int iNumberOfPresetMapping, ADLPossibleMapping *lpPresetMappings, int iEnquiryControllerIndex, int *lpNumberOfEnquiryPossibleMappings, ADLPossibleMapping **lppEnquiryPossibleMappings));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Display_DisplayMapConfig_Validate, (int iAdapterIndex, int iNumPossibleMap, ADLPossibleMap *lpPossibleMaps, int *lpNumPossibleMapResult, ADLPossibleMapResult **lppPossibleMapResult));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Display_DisplayMapConfig_PossibleAddAndRemove, (int iAdapterIndex, int iNumDisplayMap, ADLDisplayMap *lpDisplayMap, int iNumDisplayTarget, ADLDisplayTarget *lpDisplayTarget, int *lpNumPossibleAddTarget, ADLDisplayTarget **lppPossibleAddTarget, int *lpNumPossibleRemoveTarget, ADLDisplayTarget **lppPossibleRemoveTarget));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Display_SLSGrid_Caps, (int iAdapterIndex, int *lpNumSLSGrid, ADLSLSGrid **lppSLSGrid, int iOption));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Display_SLSMapIndexList_Get, (int iAdapterIndex, int *lpNumSLSMapIndexList, int **lppSLSMapIndexList, int iOptions));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Display_SLSMapIndex_Get, (int iAdapterIndex, int iADLNumDisplayTarget, ADLDisplayTarget *lpDisplayTarget, int *lpSLSMapIndex));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Display_SLSMapConfig_Get, (int iAdapterIndex, int iSLSMapIndex, ADLSLSMap *lpSLSMap, int *lpNumSLSTarget, ADLSLSTarget **lppSLSTarget, int *lpNumNativeMode, ADLSLSMode **lppNativeMode, int *lpNumBezelMode, ADLBezelTransientMode **lppBezelMode, int *lpNumTransientMode, ADLBezelTransientMode **lppTransientMode, int *lpNumSLSOffset, ADLSLSOffset **lppSLSOffset, int iOption));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Display_SLSMapConfig_Create, (int iAdapterIndex, ADLSLSMap SLSMap, int iNumTargetTarget, ADLSLSTarget *lpSLSTarget, int iBezelModePercent, int *lpSLSMapIndex, int iOption));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Display_SLSMapConfig_Delete, (int iAdapterIndex, int iSLSMapIndex));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Display_SLSMapConfig_SetState, (int iAdapterIndex, int iSLSMapIndex, int iState));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Display_SLSMapConfig_Rearrange, (int iAdapterIndex, int iSLSMapIndex, int iNumDisplayTarget, ADLSLSTarget *lpSLSTarget, ADLSLSMap slsMap, int iOption));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Display_PossibleMode_WinXP_Get, (int iAdapterIndex, int iNumDisplayTargets, ADLDisplayTarget *lpDisplayTargets, int iLargeDesktopSupportedType, int iDevicePanningControl, int *lpNumModes, ADLMode **lppModes));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Display_BezelOffsetSteppingSize_Get, (int iAdapterIndex, int *lpNumBezelOffsetSteppingSize, ADLBezelOffsetSteppingSize **lppBezelOffsetSteppingSize));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Display_BezelOffset_Set, (int iAdapterIndex, int iSLSMapIndex, int iNumBezelOffset, LPADLSLSOffset lpBezelOffset, ADLSLSMap SLSMap, int iOption));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Display_BezelSupported_Validate, (int iAdapterIndex, int iNumPossibleSLSMap, LPADLPossibleSLSMap lpPossibleSLSMaps, int *lpNumPossibleSLSMapResult, LPADLPossibleMapResult *lppPossibleMapResult));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Display_ColorCaps_Get, (int iAdapterIndex, int iDisplayIndex, int *lpCaps, int *lpValids));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Display_Color_Set, (int iAdapterIndex, int iDisplayIndex, int iColorType, int iCurrent));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Display_Color_Get, (int iAdapterIndex, int iDisplayIndex, int iColorType, int *lpCurrent, int *lpDefault, int *lpMin, int *lpMax, int *lpStep));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Display_ColorTemperatureSource_Get, (int iAdapterIndex, int iDisplayIndex, int *lpTempSource));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Display_ColorTemperatureSource_Set, (int iAdapterIndex, int iDisplayIndex, int iTempSource));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Display_ModeTimingOverride_Get, (int iAdapterIndex, int iDisplayIndex, ADLDisplayMode *lpModeIn, ADLDisplayModeInfo *lpModeInfoOut));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Display_ModeTimingOverride_Set, (int iAdapterIndex, int iDisplayIndex, ADLDisplayModeInfo *lpMode, int iForceUpdate));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Display_ModeTimingOverrideList_Get, (int iAdapterIndex, int iDisplayIndex, int iMaxNumOfOverrides, ADLDisplayModeInfo *lpModeInfoList, int *lpNumOfOverrides));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Display_CustomizedModeListNum_Get, (int iAdapterIndex, int iDisplayIndex, int *lpListNum));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Display_CustomizedModeList_Get, (int iAdapterIndex, int iDisplayIndex, ADLCustomMode *lpCustomModeList, int iBuffSize));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Display_CustomizedMode_Add, (int iAdapterIndex, int iDisplayIndex, ADLCustomMode customMode));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Display_CustomizedMode_Delete, (int iAdapterIndex, int iDisplayIndex, int iIndex));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Display_CustomizedMode_Validate, (int iAdapterIndex, int iDisplayIndex, ADLCustomMode customMode, int *lpValid));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Display_Underscan_Set, (int iAdapterIndex, int iDisplayIndex, int iCurrent));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Display_Underscan_Get, (int iAdapterIndex, int iDisplayIndex, int *lpCurrent, int *lpDefault, int *lpMin, int *lpMax, int *lpStep));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Display_Overscan_Set, (int iAdapterIndex, int iDisplayIndex, int iCurrent));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Display_Overscan_Get, (int iAdapterIndex, int iDisplayIndex, int *lpCurrent, int *lpDefualt, int *lpMin, int *lpMax, int *lpStep));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Display_ControllerOverlayAdjustmentCaps_Get, (int iAdapterIndex, ADLControllerOverlayInput *lpOverlayInput, ADLControllerOverlayInfo *lpCapsInfo));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Display_ControllerOverlayAdjustmentData_Get, (int iAdapterIndex, ADLControllerOverlayInput *lpOverlay));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Display_ControllerOverlayAdjustmentData_Set, (int iAdapterIndex, ADLControllerOverlayInput *lpOverlay));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Display_PowerXpressVersion_Get, (int iAdapterIndex, int *lpVersion));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Display_PowerXpressActiveGPU_Get, (int iAdapterIndex, int *lpActiveGPU));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Display_PowerXpressActiveGPU_Set, (int iAdapterIndex, int iActiveGPU, int *lpOperationResult));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Display_PowerXpress_AutoSwitchConfig_Get, (int iAdapterIndex, int *lpAutoSwitchOnACDCEvent, int *lpAutoSwitchOnDCACEvent));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Display_PowerXpress_AutoSwitchConfig_Set, (int iAdapterIndex, int iAutoSwitchOnACDCEvent, int iAutoSwitchOnDCACEvent));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_DFP_BaseAudioSupport_Get, (int iAdapterIndex, int iDisplayIndex, int *lpSupport));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_DFP_HDMISupport_Get, (int iAdapterIndex, int iDisplayIndex, int *lpSupport));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_DFP_MVPUAnalogSupport_Get, (int iAdapterIndex, int iDisplayIndex, int *lpSupport));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_DFP_PixelFormat_Caps, (int iAdapterIndex, int iDisplayIndex, int *lpValidBits, int *lpValidCaps));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_DFP_PixelFormat_Get, (int iAdapterIndex, int iDisplayIndex, int *lpCurState, int *lpDefault));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_DFP_PixelFormat_Set, (int iAdapterIndex, int iDisplayIndex, int iState));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_DFP_GPUScalingEnable_Get, (int iAdapterIndex, int iDisplayIndex, int *lpSupport, int *lpCurrent, int *lpDefault));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_DFP_GPUScalingEnable_Set, (int iAdapterIndex, int iDisplayIndex, int iCurrent));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_DFP_AllowOnlyCETimings_Get, (int iAdapterIndex, int iDisplayIndex, int *lpSupport, int *lpCurrent, int *lpDefault));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_DFP_AllowOnlyCETimings_Set, (int iAdapterIndex, int iDisplayIndex, int iCurrent));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Display_TVCaps_Get, (int iAdapterIndex, int iDisplayIndex, int *lpcaps));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_TV_Standard_Set, (int iAdapterIndex, int iDisplayIndex, int iCurrent));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_TV_Standard_Get, (int iAdapterIndex, int iDisplayIndex, int *lpCurrent, int *lpDefault, int *lpSupportedStandards));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_CV_DongleSettings_Get, (int iAdapterIndex, int iDisplayIndex, int *lpDongleSetting, int *lpOverrideSettingsSupported, int *lpCurOverrideSettings));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_CV_DongleSettings_Set, (int iAdapterIndex, int iDisplayIndex, int iOverrideSettings));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_CV_DongleSettings_Reset, (int iAdapterIndex, int iDisplayIndex));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Overdrive5_CurrentActivity_Get, (int iAdapterIndex, ADLPMActivity *lpActivity));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Overdrive5_ThermalDevices_Enum, (int iAdapterIndex, int iThermalControllerIndex, ADLThermalControllerInfo *lpThermalControllerInfo));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Overdrive5_Temperature_Get, (int iAdapterIndex, int iThermalControllerIndex, ADLTemperature *lpTemperature));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Overdrive5_FanSpeedInfo_Get, (int iAdapterIndex, int iThermalControllerIndex, ADLFanSpeedInfo *lpFanSpeedInfo));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Overdrive5_FanSpeed_Get, (int iAdapterIndex, int iThermalControllerIndex, ADLFanSpeedValue *lpFanSpeedValue));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Overdrive5_FanSpeed_Set, (int iAdapterIndex, int iThermalControllerIndex, ADLFanSpeedValue *lpFanSpeedValue));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Overdrive5_FanSpeedToDefault_Set, (int iAdapterIndex, int iThermalControllerIndex));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Overdrive5_ODParameters_Get, (int iAdapterIndex, ADLODParameters *lpOdParameters));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Overdrive5_ODPerformanceLevels_Get, (int iAdapterIndex, int iDefault, ADLODPerformanceLevels *lpOdPerformanceLevels));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Overdrive5_ODPerformanceLevels_Set, (int iAdapterIndex, ADLODPerformanceLevels *lpOdPerformanceLevels));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Display_WriteAndReadI2CRev_Get, (int iAdapterIndex, int *lpMajor, int *lpMinor));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Display_WriteAndReadI2C, (int iAdapterIndex, ADLI2C *plI2C));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Display_DDCBlockAccess_Get, (int iAdapterIndex, int iDisplayIndex, int iOption, int iCommandIndex, int iSendMsgLen, char *lpucSendMsgBuf, int *lpulRecvMsgLen, char *lpucRecvMsgBuf));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Display_DDCInfo_Get, (int iAdapterIndex, int iDisplayIndex, ADLDDCInfo *lpInfo));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Display_EdidData_Get, (int iAdapterIndex, int iDisplayIndex, ADLDisplayEDIDData *lpEDIDData));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Workstation_Caps, (int iAdapterIndex, int *lpValidBits, int *lpCaps));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Workstation_Stereo_Get, (int iAdapterIndex, int *lpDefState, int *lpCurState));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Workstation_Stereo_Set, (int iAdapterIndex, int iCurState));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Workstation_AdapterNumOfGLSyncConnectors_Get, (int iAdapterIndex, int *lpNumOfGLSyncConnectors));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Workstation_DisplayGenlockCapable_Get, (int iAdapterIndex, int iDisplayIndex, int *lpCanGenlock));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Workstation_GLSyncModuleDetect_Get, (int iAdapterIndex, int iGlSyncConnector, ADLGLSyncModuleID *lpGlSyncModuleID));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Workstation_GLSyncModuleInfo_Get, (int iAdapterIndex, int iGlSyncConnector, int *lpNumGLSyncGPUPorts, int *lpNumGlSyncPorts, int *lpMaxSyncDelay, int *lpMaxSampleRate, ADLGLSyncPortCaps **ppGlSyncPorts));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Workstation_GLSyncGenlockConfiguration_Get, (int iAdapterIndex, int iGlSyncConnector, int iGlValidMask, ADLGLSyncGenlockConfig *lpGlSyncGenlockConfig));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Workstation_GLSyncGenlockConfiguration_Set, (int iAdapterIndex, int iGlSyncConnector, ADLGLSyncGenlockConfig glSyncGenlockConfig));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Workstation_GLSyncPortState_Get, (int iAdapterIndex, int iGlSyncConnector, int iGlSyncPortType, int iNumLEDs, ADLGlSyncPortInfo *lpGlSyncPortInfo, int **ppGlSyncLEDs));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Workstation_GLSyncPortState_Set, (int iAdapterIndex, int iGlSyncConnector, ADLGlSyncPortControl glSyncPortControl));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Workstation_DisplayGLSyncMode_Get, (int iAdapterIndex, int iDisplayIndex, ADLGlSyncMode *lpGlSyncMode));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Workstation_DisplayGLSyncMode_Set, (int iAdapterIndex, int iDisplayIndex, ADLGlSyncMode glSyncMode));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Workstation_GLSyncSupportedTopology_Get, (int iAdapterIndex, int iNumSyncModes, ADLGlSyncMode2 *glSyncModes, int *iNumSugSyncModes, ADLGlSyncMode2 **glSugSyncModes));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Workstation_LoadBalancing_Get, (int *lpResultMask, int *lpCurResultValue, int *lpDefResultValue));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Workstation_LoadBalancing_Set, (int iCurState));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Workstation_LoadBalancing_Caps, (int iAdapterIndex, int *lpResultMask, int *lpResultValue));

#ifdef __linux__
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Adapter_MemoryInfo_Get, (int iAdapterIndex, ADLMemoryInfo *lpMemoryInfo));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Controller_Color_Set, (int iAdapterIndex, int iControllerIndex, ADLGamma adlGamma));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Controller_Color_Get, (int iAdapterIndex, int iControllerIndex, ADLGamma *lpGammaCurrent, ADLGamma *lpGammaDefault, ADLGamma *lpGammaMin, ADLGamma *lpGammaMax));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_DesktopConfig_Get, (int iAdapterIndex, int *lpDesktopConfig));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_DesktopConfig_Set, (int iAdapterIndex, int iDesktopConfig));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_NumberOfDisplayEnable_Get, (int iAdapterIndex, int *lpNumberOfDisplays));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_DisplayEnable_Set, (int iAdapterIndex, int *lpDisplayIndexList, int iDisplayListSize, int bPersistOnly));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Display_IdentifyDisplay, (int iAdapterIndex, int iDisplayIndex, int iDisplayControllerIndex, int iShow, int iDisplayNum, int iPosX, int iPosY));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Display_LUTColor_Set, (int iAdapterIndex, int iDisplayIndex, ADLGamma adlGamma));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Display_LUTColor_Get, (int iAdapterIndex, int iDisplayIndex, ADLGamma *lpGammaCurrent, ADLGamma *lpGammaDefault, ADLGamma *lpGammaMin, ADLGamma *lpGammaMax));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Adapter_XScreenInfo_Get, (LPXScreenInfo lpXScreenInfo, int iInputSize));
EXTERN_ADL DECLARE_ADL_PROC(int, ADL_Display_XrandrDisplayName_Get, (int iAdapterIndex, int iDisplayIndex, char *lpXrandrDisplayName, int iBuffSize));
#endif

#undef DECLARE_ADL_PROC
#undef EXTERN_ADL

#ifdef __cplusplus
}
#endif

#endif // ifndef ADL_WRAPPER_H

