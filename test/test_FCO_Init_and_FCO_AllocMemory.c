#include "common.h"

struct FCO_AllocFunc_Impl_Vars
{
	unsigned int size;
	void *address;
	int counter;
};

struct FCO_ExceptionFunc_Impl_Vars
{
	FCO_ExceptionCode code;
	int counter;
};

struct FCO_AllocFunc_Impl_Vars FCO_AllocFunc_Vars;
struct FCO_ExceptionFunc_Impl_Vars FCO_ExceptionFunc_Vars;

void *FCO_AllocFunc_Impl(unsigned int size)
{
	FCO_AllocFunc_Vars.counter++;
	FCO_AllocFunc_Vars.size = size;
	return FCO_AllocFunc_Vars.address;
}

void FCO_ExceptionFunc_Impl(FCO_ExceptionCode code)
{
	FCO_ExceptionFunc_Vars.counter++;
	FCO_ExceptionFunc_Vars.code = code;
}

void Test_Not_Calling_FCO_Init_Does_Not_Cause_Crash()
{
	FCO_AllocMemory(10);
}

void Test_Calling_FCO_AllocMemory_Without_Calling_FCO_Init_Returns_Null()
{
	if (FCO_AllocMemory(10) != NULL)
	{
		TEST_FAIL();
	}
}

void Test_Calling_Setting_FCO_AllocFunc_Null_Throws_Exception()
{
	FCO_ExceptionFunc_Vars = (struct FCO_ExceptionFunc_Impl_Vars){.code = FCO_NO_EXCEPTION, .counter = 0};

	FCO_Init(NULL, FCO_ExceptionFunc_Impl);
	
	FCO_AllocMemory(10);

	if (FCO_ExceptionFunc_Vars.counter != 1)
	{
		TEST_FAIL();
	}

	if (FCO_ExceptionFunc_Vars.code != FCO_NULL_ALLOC_FUNC_EXCEPTION)
	{
		TEST_FAIL();
	}
}

void Test_Returning_Null_Address_Throws_Exception()
{
	FCO_AllocFunc_Vars = (struct FCO_AllocFunc_Impl_Vars){.size = 0, .address = NULL, .counter = 0};
	FCO_ExceptionFunc_Vars = (struct FCO_ExceptionFunc_Impl_Vars){.code = FCO_NO_EXCEPTION, .counter = 0};

	FCO_Init(FCO_AllocFunc_Impl, FCO_ExceptionFunc_Impl);

	void *address = FCO_AllocMemory(10);

	if (FCO_AllocFunc_Vars.counter != 1)
	{
		TEST_FAIL();
	}

	if (FCO_AllocFunc_Vars.size != 10)
	{
		TEST_FAIL();
	}

	if (address != NULL)
	{
		TEST_FAIL();
	}

	if (FCO_ExceptionFunc_Vars.counter != 1)
	{
		TEST_FAIL();
	}

	if (FCO_ExceptionFunc_Vars.code != FCO_MEMORY_ALLOC_EXCEPTION)
	{
		TEST_FAIL();
	}
}

void Test_Valid_Operation()
{
	FCO_AllocFunc_Vars = (struct FCO_AllocFunc_Impl_Vars){.size = 0, .address = (void *)1000, .counter = 0};
	FCO_ExceptionFunc_Vars = (struct FCO_ExceptionFunc_Impl_Vars){.code = FCO_NO_EXCEPTION, .counter = 0};

	FCO_Init(FCO_AllocFunc_Impl, FCO_ExceptionFunc_Impl);

	void *address = FCO_AllocMemory(10);

	if (FCO_AllocFunc_Vars.counter != 1)
	{
		TEST_FAIL();
	}

	if (FCO_AllocFunc_Vars.size != 10)
	{
		TEST_FAIL();
	}

	if (address != (void *)1000)
	{
		TEST_FAIL();
	}

	if (FCO_ExceptionFunc_Vars.counter != 0)
	{
		TEST_FAIL();
	}

	if (FCO_ExceptionFunc_Vars.code != FCO_NO_EXCEPTION)
	{
		TEST_FAIL();
	}
}

int main()
{
	Test_Not_Calling_FCO_Init_Does_Not_Cause_Crash();
	Test_Calling_FCO_AllocMemory_Without_Calling_FCO_Init_Returns_Null();
	Test_Calling_Setting_FCO_AllocFunc_Null_Throws_Exception();
	Test_Returning_Null_Address_Throws_Exception();
	Test_Valid_Operation();

	TEST_PASS();
}