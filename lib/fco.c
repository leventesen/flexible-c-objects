/*
Copyright 2024 Levent Esen leventesen12@hotmail.com

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

   http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#include "fco.h"

static FCO_AllocFunc allocate;
static FCO_ExceptionFunc exception;

void FCO_Init(FCO_AllocFunc alloc_func, FCO_ExceptionFunc exception_func)
{
	allocate = alloc_func;
	exception = exception_func;
}

void *FCO_AllocMemory(unsigned int size)
{
	void *address = 0;

	if (allocate)
	{
		address = allocate(size);

		if (!address)
		{
			if (exception)
			{
				exception(FCO_MEMORY_ALLOC_EXCEPTION);
			}
		}
	}
	else
	{
		if (exception)
		{
			exception(FCO_NULL_ALLOC_FUNC_EXCEPTION);
		}
	}

	return address;
}

void FCO_RegisterObject(FCO_TypeName type, FCO_ObjectConstructor constructor)
{
}

void FCO_RegisterDependency(FCO_TypeName requested_type, FCO_TypeName resolved_type)
{
}

FCO_ObjectHandle FCO_CreateEmptyObject()
{
}

FCO_ObjectHandle FCO_CreateTypedObject(FCO_TypeName type)
{
}

void FCO_SetInterface(FCO_ObjectHandle object, FCO_TypeName type, FCO_InterfaceHandle interface)
{
}

FCO_InterfaceHandle FCO_GetInterface(FCO_ObjectHandle object, FCO_TypeName type)
{
}

void FCO_SetData(FCO_ObjectHandle object, FCO_TypeName type, FCO_DataHandle data)
{
}

FCO_DataHandle FCO_GetData(FCO_ObjectHandle object, FCO_TypeName type)
{
}

void FCO_AddDependency(FCO_ObjectHandle object, FCO_TypeName type)
{
}

FCO_ObjectHandle FCO_GetDependency(FCO_ObjectHandle object, FCO_TypeName type)
{
}