/* Copyright (c) 2012 The adl_wrapper Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license
 * that can be found in the LICENSE.txt file.
 */

// main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <windows.h>
#include "adl_wrapper.h"

int _tmain(int argc, _TCHAR* argv[])
{
	int err;
	int count = 0;
	
	err = Init_ADL_Procs();
	if (err != ADL_OK) {
	puts("error");
	return 1;
	}
	
	err = ADL_Main_Control_Create(Main_Malloc_Callback, 1);
	if (err != ADL_OK) {
	puts("error");
	return 1;
	}
	
	ADL_Adapter_NumberOfAdapters_Get(&count);
	
	printf("count: %d\n", count);
	
	ADL_Main_Control_Destroy();
	Deinit_ADL_Procs();

	return 0;
}

