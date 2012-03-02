/* Copyright (c) 2012 The adl_wrapper Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license
 * that can be found in the LICENSE.txt file.
 */

#include <stdio.h>

#include "adl_wrapper.h"

int main(int argc, char** argv)
{
	int err;
	int count = 0;

	if (Init_ADL_Procs() != ADL_OK) {
		puts("error Init_ADL_Procs()");
		return 1;
	}

	err = ADL_Main_Control_Create(Main_Malloc_Callback, 1);
	if (err != ADL_OK) {
		puts("error ADL_Main_Control_Create()");
		return 1;
	}

	ADL_Adapter_NumberOfAdapters_Get(&count);

	printf("count: %d\n", count);

	ADL_Main_Control_Destroy();
	Deinit_ADL_Procs();
	return 0;
}

