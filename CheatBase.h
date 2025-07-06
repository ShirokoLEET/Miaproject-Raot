#pragma once
#include <cstdint>

// Forward declarations for Il2Cpp structures
struct Il2CppObject;
struct Il2CppType;
struct Il2CppClass;
struct Il2CppArray;
struct Il2CppImage;
struct Il2CppAssembly;
struct Il2CppDomain;

// Function pointer types for Il2Cpp functions
typedef void* (*t_il2cpp_domain_get)();
typedef Il2CppAssembly** (*t_il2cpp_domain_get_assemblies)(Il2CppDomain*, size_t*);
typedef Il2CppClass* (*t_il2cpp_class_from_name)(Il2CppImage*, const char*, const char*);
typedef Il2CppType* (*t_il2cpp_class_get_type)(Il2CppClass*);
typedef Il2CppArray* (*t_FindObjectsOfType)(Il2CppType*);
typedef const char* (*t_get_tag)(Il2CppObject*);

// Global variables
extern uintptr_t baseAddress;
extern t_il2cpp_domain_get il2cpp_domain_get;
extern t_il2cpp_domain_get_assemblies il2cpp_domain_get_assemblies;
extern t_il2cpp_class_from_name il2cpp_class_from_name;
extern t_il2cpp_class_get_type il2cpp_class_get_type;
extern t_FindObjectsOfType FindObjectsOfType;
extern t_get_tag GetGameObjectTag;

// Function declarations
void GetGameObject();
uintptr_t GetModuleBaseAddress(const char* moduleName);
void InitializeAddresses();
void CheatInit();

class CheatBase
{
};