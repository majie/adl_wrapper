#include <stdio.h>

#include "adl_wrapper.h"

int main(int argc, char** argv)
{
	int err;
	int count = 0;

	err = ADL_Main_Control_Create(Main_Malloc_Callback, 1);
	if (err != ADL_OK) {
		puts("error");
		return 1;
	}

	ADL_Adapter_NumberOfAdapters_Get(&count);

	printf("count: %d\n", count);

	ADL_Main_Control_Destroy();
	return 0;
}
