#pragma once

#include <iostream>
#include <string>
#include <cstdint>

// ����ǰ������
struct Il2CppObject;
struct Il2CppType;
struct Il2CppClass;
struct Il2CppArray;
struct Il2CppImage;
struct Il2CppAssembly;
struct Il2CppDomain;

// �������� typedef
typedef int32_t TypeDefinitionIndex;
typedef int32_t CustomAttributeIndex;
typedef int32_t FieldIndex;
typedef int32_t MethodIndex;
typedef int32_t ParameterIndex;
typedef int32_t EventIndex;
typedef int32_t PropertyIndex;
typedef int32_t GenericContainerIndex;
typedef int32_t StringLiteralIndex;
typedef int32_t DefaultValueIndex;

// ���� typedef
typedef void Il2CppNameToTypeDefinitionIndexHashTable;
typedef void Il2CppCodeGenModule;
typedef Il2CppClass Il2CppVTable;
typedef void MonitorData;
typedef uintptr_t il2cpp_array_size_t;
typedef int32_t il2cpp_array_lower_bound_t;

typedef enum Il2CppTypeEnum {
    IL2CPP_TYPE_END = 0x00,
    IL2CPP_TYPE_VOID = 0x01,
    IL2CPP_TYPE_BOOLEAN = 0x02,
    IL2CPP_TYPE_CHAR = 0x03,
    IL2CPP_TYPE_I1 = 0x04,
    IL2CPP_TYPE_U1 = 0x05,
    IL2CPP_TYPE_I2 = 0x06,
    IL2CPP_TYPE_U2 = 0x07,
    IL2CPP_TYPE_I4 = 0x08,
    IL2CPP_TYPE_U4 = 0x09,
    IL2CPP_TYPE_I8 = 0x0a,
    IL2CPP_TYPE_U8 = 0x0b,
    IL2CPP_TYPE_R4 = 0x0c,
    IL2CPP_TYPE_R8 = 0x0d,
    IL2CPP_TYPE_STRING = 0x0e,
    IL2CPP_TYPE_PTR = 0x0f,
    IL2CPP_TYPE_BYREF = 0x10,
    IL2CPP_TYPE_VALUETYPE = 0x11,
    IL2CPP_TYPE_CLASS = 0x12,
    IL2CPP_TYPE_VAR = 0x13,
    IL2CPP_TYPE_ARRAY = 0x14,
    IL2CPP_TYPE_GENERICINST = 0x15,
    IL2CPP_TYPE_TYPEDBYREF = 0x16,
    IL2CPP_TYPE_I = 0x18,
    IL2CPP_TYPE_U = 0x19,
    IL2CPP_TYPE_FNPTR = 0x1b,
    IL2CPP_TYPE_OBJECT = 0x1c,
    IL2CPP_TYPE_SZARRAY = 0x1d,
    IL2CPP_TYPE_MVAR = 0x1e,
    IL2CPP_TYPE_CMOD_REQD = 0x1f,
    IL2CPP_TYPE_CMOD_OPT = 0x20,
    IL2CPP_TYPE_INTERNAL = 0x21,
    IL2CPP_TYPE_MODIFIER = 0x40,
    IL2CPP_TYPE_SENTINEL = 0x41,
    IL2CPP_TYPE_PINNED = 0x45,
} Il2CppTypeEnum;

typedef struct Il2CppType {
    union {
        void* dummy; // padding, ���ù�
        uint64_t data; // �������ٷ�����������
    };
    Il2CppTypeEnum type : 8;
    uint8_t attrs : 8;
    uint16_t num_mods : 6;
    uint16_t byref : 1;
    uint16_t pinned : 1;
    uint16_t unused : 4;
} Il2CppType;

typedef struct Il2CppDomain {
    void* placeholder; // �㲻��Ҫ�õ����ڲ�ϸ�ڣ����ռλ����
} Il2CppDomain;

// Il2CppObject ���壨���нṹ���ࣩ
struct Il2CppObject {
    union {
        Il2CppClass* klass;
        Il2CppVTable* vtable;
    };
    MonitorData* monitor;
};

// ����߽�ṹ
struct Il2CppArrayBounds {
    il2cpp_array_size_t length;
    il2cpp_array_lower_bound_t lower_bound;
};

// Il2CppArray ���壨����������ࣩ
struct Il2CppArray : Il2CppObject {
    Il2CppArrayBounds* bounds;
    il2cpp_array_size_t max_length;
};

// ģ������ṹ�����ڷ��� vector[]��
template<typename T>
struct Il2CppArrayT : Il2CppArray {
    T vector[0];
};

// Il2CppImage������������������
struct Il2CppImage {
    const char* name;
    const char* nameNoExt;
    Il2CppAssembly* assembly;

    TypeDefinitionIndex typeStart;
    uint32_t typeCount;

    TypeDefinitionIndex exportedTypeStart;
    uint32_t exportedTypeCount;

    CustomAttributeIndex customAttributeStart;
    uint32_t customAttributeCount;

    MethodIndex entryPointIndex;
    mutable

    Il2CppNameToTypeDefinitionIndexHashTable* nameToClassHashTable;

    const Il2CppCodeGenModule* codeGenModule;

    uint32_t token;
    uint8_t dynamic;
};

// Il2CppAssemblyName������Ԫ��Ϣ��
struct Il2CppAssemblyName {
    const char* name;
    const char* culture;
    const char* hash_value;
    const char* public_key;
    uint32_t hash_alg;
    int32_t hash_len;
    uint32_t flags;
    int32_t major;
    int32_t minor;
    int32_t build;
    int32_t revision;
    uint8_t public_key_token[8];
};


typedef struct Il2CppClass {
    const Il2CppImage* image;  // 0x00
    void* gc_desc;             // 0x08
    const char* name;          // 0x10
    const char* namespaze;     // 0x18
    // ����԰����������ֶΣ���������ռλ�����
} Il2CppClass;





struct Il2CppAssembly {
    Il2CppImage* image;
    uint32_t token;
    int32_t referencedAssemblyStart;
    int32_t referencedAssemblyCount;
    Il2CppAssemblyName aname;
};
