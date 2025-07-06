#include "CheatBase.h"
#include <Windows.h>
#include <iostream>
#include <vector>
#include <string>
#include "il2cpp_struct.h"


typedef void* (*t_il2cpp_domain_get)();
typedef Il2CppAssembly** (*t_il2cpp_domain_get_assemblies)(Il2CppDomain*, size_t*);
typedef Il2CppClass* (*t_il2cpp_class_from_name)(Il2CppImage*, const char*, const char*);
typedef Il2CppType* (*t_il2cpp_class_get_type)(Il2CppClass*);
typedef Il2CppArray* (*t_FindObjectsOfType)(Il2CppType*);
typedef const char* (*t_get_tag)(Il2CppObject*);

uintptr_t baseAddress = GetModuleBaseAddress("GameAssembly.dll");
t_il2cpp_domain_get il2cpp_domain_get = (t_il2cpp_domain_get)(baseAddress + 0x20CAE0);
t_il2cpp_domain_get_assemblies il2cpp_domain_get_assemblies = (t_il2cpp_domain_get_assemblies)(baseAddress + 0x20CB20);
t_il2cpp_class_from_name il2cpp_class_from_name = (t_il2cpp_class_from_name)(baseAddress + 0x20BFC0);
t_il2cpp_class_get_type il2cpp_class_get_type = (t_il2cpp_class_get_type)(baseAddress + 0x16BB50);
t_FindObjectsOfType FindObjectsOfType = (t_FindObjectsOfType)(baseAddress + 0x10E1560);
t_get_tag GetGameObjectTag = (t_get_tag)(baseAddress + 0x126DF30);



void GetGameObject() {
    std::vector<std::string> foundObjects;
    Il2CppDomain* domain = (Il2CppDomain*)il2cpp_domain_get();
    size_t count = 0;
    Il2CppAssembly** assemblies = il2cpp_domain_get_assemblies(domain, &count);
	std::cout << "[*] 获取程序集数量: " << count << std::endl;
    Il2CppImage* unityEngineImage = nullptr;
    for (size_t i = 0; i < count; i++) {
        Il2CppAssembly* assembly = assemblies[i];
        if (!assembly) {
            std::cout << "[!] Assembly #" << i << " is null" << std::endl;
            continue;
        }

        Il2CppImage* image = assembly->image;
        if (!image || !image->name) {
            std::cout << "[!] Assembly #" << i << " has null image or image name" << std::endl;
            continue;
        }

        if (strcmp(image->name, "UnityEngine.CoreModule.dll") == 0) {
            unityEngineImage = image;
            std::cout << "[+] 找到 UnityEngine.CoreModule.dll" << std::endl;
            break;
        }
    }

    std::cout << "[*] 尝试获取 UnityEngine.GameObject 类" << std::endl;
    Il2CppClass* goClass = il2cpp_class_from_name(unityEngineImage, "UnityEngine", "GameObject");
    if (goClass == nullptr) {
        std::cout << "[!] 没有找到 UnityEngine.GameObject 类" << std::endl;
        return;
    }
    std::cout << "[+] 成功获取 UnityEngine.GameObject 类: " << goClass->name << std::endl;

    Il2CppType* goType = il2cpp_class_get_type(goClass);

    // 调用 FindObjectsOfType
    Il2CppArray* rawArray = FindObjectsOfType(goType);
    if (!rawArray) {
        std::cout << "[!] FindObjectsOfType 返回空指针" << std::endl;
        return;
    }

    // 转换为可访问 vector[] 的结构体
    Il2CppArrayT<Il2CppObject*>* goArray = (Il2CppArrayT<Il2CppObject*>*)rawArray;

    int countObj = rawArray->max_length;
    std::cout << "[+] 找到 GameObject 数量: " << countObj << std::endl;

    for (int i = 0; i < countObj; i++) {
        Il2CppObject* go = goArray->vector[i];
        if (!go) continue;

        const char* tag = GetGameObjectTag(go); // 你自己的函数
        if (tag)
            std::cout << "[" << i << "] Tag: " << tag << std::endl;
        else
            std::cout << "[" << i << "] (null tag)" << std::endl;
    }
}

uintptr_t GetModuleBaseAddress(const char* moduleName) {
    HMODULE hModule = GetModuleHandleA(moduleName);
    if (hModule == nullptr) {
        std::cout << "[!] Failed to get handle for module: " << moduleName << std::endl;
        return 0;
    }
    return reinterpret_cast<uintptr_t>(hModule);
}


void InitializeAddresses() {

    std::cout << "[+] GameAssembly: 0x" << std::hex << baseAddress << std::endl;
}

void CheatInit() {
    InitializeAddresses();
	GetGameObject();
}