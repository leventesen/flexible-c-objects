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

#ifndef __FCO_H__
#define __FCO_H__

// FCO Types are distinguished by const char pointer addresses.
// It's important to note that the string content is not evaluated.
typedef const char *FCO_TypeName;

// All handles are pointers.
// Pointed types are hidden from client code.
// See the fco.c file for definitions of the pointed types.
typedef void *FCO_ObjectHandle;
typedef void *FCO_InterfaceHandle;
typedef void *FCO_DataHandle;

// Object constructor functions take a type name and return the necessary object handle.
typedef FCO_ObjectHandle (*FCO_ObjectConstructor)(FCO_TypeName type);

// Memory allocation callback function type
typedef void *(*FCO_AllocFunc)(unsigned int size);

// Exception codes
typedef enum {
	FCO_UNKNOWN_EXCEPTION,
	FCO_MEMORY_ALLOC_EXCEPTION,
} FCO_ExceptionCode;

// Exception callback function type
typedef void (*FCO_ExceptionFunc)(FCO_ExceptionCode code);

// Client code must call this function before using FCO
// alloc_func is mandatory
// exception_func is optional
void FCO_Init(FCO_AllocFunc alloc_func, FCO_ExceptionFunc exception_func);

// FCO_AllocMemory is used both by FCO and client code
void *FCO_AllocMemory(unsigned int size);

// Before creating an object, it's type and constructor must be registered
void FCO_RegisterObject(FCO_TypeName type, FCO_ObjectConstructor constructor);

// Dependency injection mechanism requires the registration of requested and resolved types
void FCO_RegisterDependency(FCO_TypeName requested_type, FCO_TypeName resolved_type);

// Create an object with no type, data, interfaces or dependencies
FCO_ObjectHandle FCO_CreateEmptyObject();

// Create an object with the registered type. It uses constructor to create the object
FCO_ObjectHandle FCO_CreateTypedObject(FCO_TypeName type);

// Created objects can have multiple interfaces
// Types are unique per object, this means that the same type can not be set multiple times per object
// Interface handle is pointer to a data structure that is specific to the interface type
// Interfaces are used for function calls so usually it's a pointer to struct with function pointers
// FCO_SetInterface is usually called during object creation
void FCO_SetInterface(FCO_ObjectHandle object, FCO_TypeName type, FCO_InterfaceHandle interface);
FCO_InterfaceHandle FCO_GetInterface(FCO_ObjectHandle object, FCO_TypeName type);

// Similar to FCO_SetInterface, but for data
// Data is a pointer to any data structure
void FCO_SetData(FCO_ObjectHandle object, FCO_TypeName type, FCO_DataHandle data);
FCO_DataHandle FCO_GetData(FCO_ObjectHandle object, FCO_TypeName type);

// This section is tricky
// When FCO_AddDependency is called, the dependency object is created with the registered type
// Cascaded dependencies are resolved during object creation
// Dependency type is unique per object
// FCO_AddDependency is usually called during object creation
void FCO_AddDependency(FCO_ObjectHandle object, FCO_TypeName type);
FCO_ObjectHandle FCO_GetDependency(FCO_ObjectHandle object, FCO_TypeName type);

#endif