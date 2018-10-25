#include <sys/ppu_thread.h>
#include <sys/timer.h>
#include <sys/process.h>
#include <sys/syscall.h>
#include <ppu_intrinsics.h>

int destroy_thread(sys_ppu_thread_t id, bool* exit)
{
	std::uint64_t res;
	*exit = true;

	return sys_ppu_thread_join(id, &res);
}

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

int strlen(char* buff)
{
	int i = 0;
	while (buff[i] != 0)
		i++;
	return i;
}