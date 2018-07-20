#include "stdafx.h"

#include <wchar.h>
#include <sys/prx.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/syscall.h>
#include <sys/ppu_thread.h>
#include <string.h>
#include <sys/sys_time.h>
#include <sys/time_util.h>
#include <stdarg.h>
#include <assert.h>
#include <sys/process.h>
#include <sys/memory.h>
#include <sys/timer.h>
#include <sys/return_code.h>
#include <sys/prx.h>
#include <stddef.h>
#include <math.h>
#include <stdarg.h>
#include <cellstatus.h>
#include <typeinfo>
#include <vector>
#include <pthread.h>
#include <locale.h>
#include <cell/error.h>
#include <sys/paths.h>
#include <time.h>
#include <cell/sysmodule.h>
#include <sys/ss_get_open_psid.h>

#pragma comment(lib, "sysmodule_stub")
#include <cell/pad.h>
#include <string>
#include <sys/random_number.h>
#pragma comment(lib, "c")
#include <sys/memory.h>
#include <fastmath.h>
#include <ppu_intrinsics.h>

void sleep(usecond_t time)
{
	sys_timer_usleep(time * 1000);
}

int console_write(const char * s)
{
	uint32_t len;
	system_call_4(403, 0, (uint64_t)s, 32, (uint64_t)&len);
	return_to_user_prog(int);
}

int Memcpy(void* destination, const void* source, size_t size)
{
	system_call_4(905, (uint64_t)sys_process_getpid(), (uint64_t)destination, size, (uint64_t)source);
	__dcbst(destination);
	__sync();
	__isync();
	return_to_user_prog(int);
}

void PatchInJump(int Address, int Destination, bool Linked)
{
	// use this data to copy over the address
	int FuncBytes[4];

	// Get the actual destination address
	Destination = *(int *)Destination;

	FuncBytes[0] = 0x3D600000 + ((Destination >> 16) & 0xFFFF); // lis     %r11, dest>>16
	if (Destination & 0x8000) // If bit 16 is 1
		FuncBytes[0] += 1;

	FuncBytes[1] = 0x396B0000 + (Destination & 0xFFFF); // addi    %r11, %r11, dest&0xFFFF
	FuncBytes[2] = 0x7D6903A6; // mtctr    %r11

	FuncBytes[3] = 0x4E800420; // bctr

	if (Linked)
		FuncBytes[3] += 1; // bctrl

	Memcpy((void*)Address, FuncBytes, 4 * 4);
}

sys_ppu_thread_t id;
sys_ppu_thread_t create_thread(void(*entry)(uint64_t), int priority, size_t stacksize, const char* threadname)
{
	if (sys_ppu_thread_create(&id, entry, 0, priority, stacksize, 0, threadname) != CELL_OK)
	{
		console_write("Thread creation failed\n");
	}
	else
	{
		console_write("Thread created\n");
	}
	return id;
}