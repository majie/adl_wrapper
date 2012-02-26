This is a wrapper for AMD Display Library 3.0.
(http://developer.amd.com/sdks/ADLSDK/Pages/default.aspx)

The wrapper supports Windows and Linux. It may work with older versions of ADL.

APIs provided by adl_wrapper.h:

Preprocessor Macro DIRECT_LINK_ADL
int Init_ADL_Procs(void);
void Deinit_ADL_Procs(void);
void* __stdcall Main_Malloc_Callback(int);

If compiled on Windows, disable "use precompiled header" for adl_wrapper.c or
you will get "error C1853".
