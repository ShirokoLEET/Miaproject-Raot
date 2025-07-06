#pragma once

#include <iostream>
#include <string>
#include <cstdint>

// 基础前向声明
struct Il2CppObject;
struct Il2CppType;
struct Il2CppClass;
struct Il2CppArray;
struct Il2CppImage;
struct Il2CppAssembly;
struct Il2CppDomain;

// 类型索引 typedef
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

// 其它 typedef
typedef void Il2CppNameToTypeDefinitionIndexHashTable;
typedef void Il2CppCodeGenModule;
typedef Il2CppClass Il2CppVTable;
typedef void MonitorData;
typedef uintptr_t il2cpp_array_size_t;
typedef int32_t il2cpp_array_lower_bound_t;


typedef int32_t GenericParameterIndex;



typedef struct Il2CppArrayType
{
    const Il2CppType* etype;
    uint8_t rank;
    uint8_t numsizes;
    uint8_t numlobounds;
    int* sizes;
    int* lobounds;
} Il2CppArrayType;

typedef struct Il2CppGenericInst
{
    uint32_t type_argc;
    const Il2CppType** type_argv;
} Il2CppGenericInst;

typedef struct Il2CppGenericContext
{
    /* The instantiation corresponding to the class generic parameters */
    const Il2CppGenericInst* class_inst;
    /* The instantiation corresponding to the method generic parameters */
    const Il2CppGenericInst* method_inst;
} Il2CppGenericContext;




typedef struct Il2CppGenericClass
{
    TypeDefinitionIndex typeDefinitionIndex;    /* the generic type definition */
    Il2CppGenericContext context;   /* a context that contains the type instantiation doesn't contain any method instantiation */
    Il2CppClass* cached_class;  /* if present, the Il2CppClass corresponding to the instantiation.  */
} Il2CppGenericClass;

typedef enum Il2CppTypeEnum
{
    IL2CPP_TYPE_END = 0x00,       /* End of List */
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
    IL2CPP_TYPE_PTR = 0x0f,       /* arg: <type> token */
    IL2CPP_TYPE_BYREF = 0x10,       /* arg: <type> token */
    IL2CPP_TYPE_VALUETYPE = 0x11,       /* arg: <type> token */
    IL2CPP_TYPE_CLASS = 0x12,       /* arg: <type> token */
    IL2CPP_TYPE_VAR = 0x13,       /* Generic parameter in a generic type definition, represented as number (compressed unsigned integer) number */
    IL2CPP_TYPE_ARRAY = 0x14,       /* type, rank, boundsCount, bound1, loCount, lo1 */
    IL2CPP_TYPE_GENERICINST = 0x15,     /* <type> <type-arg-count> <type-1> \x{2026} <type-n> */
    IL2CPP_TYPE_TYPEDBYREF = 0x16,
    IL2CPP_TYPE_I = 0x18,
    IL2CPP_TYPE_U = 0x19,
    IL2CPP_TYPE_FNPTR = 0x1b,        /* arg: full method signature */
    IL2CPP_TYPE_OBJECT = 0x1c,
    IL2CPP_TYPE_SZARRAY = 0x1d,       /* 0-based one-dim-array */
    IL2CPP_TYPE_MVAR = 0x1e,       /* Generic parameter in a generic method definition, represented as number (compressed unsigned integer)  */
    IL2CPP_TYPE_CMOD_REQD = 0x1f,       /* arg: typedef or typeref token */
    IL2CPP_TYPE_CMOD_OPT = 0x20,       /* optional arg: typedef or typref token */
    IL2CPP_TYPE_INTERNAL = 0x21,       /* CLR internal type */

    IL2CPP_TYPE_MODIFIER = 0x40,       /* Or with the following types */
    IL2CPP_TYPE_SENTINEL = 0x41,       /* Sentinel for varargs method signature */
    IL2CPP_TYPE_PINNED = 0x45,       /* Local var that points to pinned object */

    IL2CPP_TYPE_ENUM = 0x55        /* an enumeration */
} Il2CppTypeEnum;

typedef struct Il2CppType
{
    union
    {
        // We have this dummy field first because pre C99 compilers (MSVC) can only initializer the first value in a union.
        void* dummy;
        TypeDefinitionIndex klassIndex; /* for VALUETYPE and CLASS */
        const Il2CppType* type;   /* for PTR and SZARRAY */
        Il2CppArrayType* array; /* for ARRAY */
        //MonoMethodSignature *method;
        GenericParameterIndex genericParameterIndex; /* for VAR and MVAR */
        Il2CppGenericClass* generic_class; /* for GENERICINST */
    } data;
    unsigned int attrs : 16; /* param attributes or field flags */
    Il2CppTypeEnum type : 8;
    unsigned int num_mods : 6;  /* max 64 modifiers follow at the end */
    unsigned int byref : 1;
    unsigned int pinned : 1;  /* valid when included in a local var signature */
    //MonoCustomMod modifiers [MONO_ZERO_LEN_ARRAY]; /* this may grow */
} Il2CppType;

typedef struct Il2CppDomain {
    void* placeholder; // 你不需要用到它内部细节，随便占位即可
} Il2CppDomain;

// Il2CppObject 定义（所有结构基类）
struct Il2CppObject {
    union {
        Il2CppClass* klass;
        Il2CppVTable* vtable;
    };
    MonitorData* monitor;
};

// 数组边界结构
struct Il2CppArrayBounds {
    il2cpp_array_size_t length;
    il2cpp_array_lower_bound_t lower_bound;
};

// Il2CppArray 本体（用于数组基类）
struct Il2CppArray : Il2CppObject {
    Il2CppArrayBounds* bounds;
    il2cpp_array_size_t max_length;
};

// 模板数组结构（用于访问 vector[]）
template<typename T>
struct Il2CppArrayT : Il2CppArray {
    T vector[0];
};

// Il2CppImage（程序集内类型容器）
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

// Il2CppAssemblyName（程序集元信息）
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
    // 你可以按需继续添加字段，或者留空占位符填充
} Il2CppClass;





struct Il2CppAssembly {
    Il2CppImage* image;
    uint32_t token;
    int32_t referencedAssemblyStart;
    int32_t referencedAssemblyCount;
    Il2CppAssemblyName aname;
};
