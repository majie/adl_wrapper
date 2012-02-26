This is a wrapper for AMD Display Library 3.0.
(http://developer.amd.com/sdks/ADLSDK/Pages/default.aspx)

The wrapper supports Windows and Linux. It may work with older versions of ADL.

APIs provided by adl_wrapper.h:

Preprocessor Macro DIRECT_LINK_ADL
  On Linux, you can link to a .so file directly. But On Windows, to link to
  a .dll you need a .lib file, which is not provided in the ADL SDK.
  So it's recommend to define DIRECT_LINK_ADL on Linux and
  undef DIRECT_LINK_ADL on Windows.
  See adl_wrapper.h for more information.
  
int Init_ADL_Procs(void);
void Deinit_ADL_Procs(void);
  Wrapper initializer/destructor.
  
void* __stdcall Main_Malloc_Callback(int);
  Use this for the first argument of ADL_Main_Control_Create().
  
Other functions begin with "ADL_" are documented in the ADL SDK.

Note:
If compiled on Windows, disable "use precompiled header" for adl_wrapper.c or
you will get "error C1853".
