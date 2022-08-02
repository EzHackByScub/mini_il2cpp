#pragma once
#include <Windows.h>
class Il2CppDomain;
class Il2CppAssembly;
class Il2CppImage;
class MethodInfo
{
public:
	void* methodaddr;
};
class Il2CppClass;
namespace il2cppAPI
{
	static inline auto GameAssembly = GetModuleHandleA("GameAssembly.dll");
	static inline  auto il2cpp_domain_get = reinterpret_cast<Il2CppDomain * (__cdecl*)()>(GetProcAddress(GameAssembly, "il2cpp_domain_get"));
	static inline  auto il2cpp_domain_assembly_open = reinterpret_cast<Il2CppAssembly * (__cdecl*)(Il2CppDomain * domain, const char* name)>(GetProcAddress(GameAssembly, "il2cpp_domain_assembly_open"));
	static inline  auto il2cpp_assembly_get_image = reinterpret_cast<Il2CppImage * (__cdecl*)(Il2CppAssembly * assembly)>(GetProcAddress(GameAssembly, "il2cpp_assembly_get_image"));
	static inline  auto il2cpp_image_get_class_count = reinterpret_cast<int(__cdecl*)(Il2CppImage * image)>(GetProcAddress(GameAssembly, "il2cpp_image_get_class_count"));
	static inline  auto il2cpp_image_get_class = reinterpret_cast<Il2CppClass * (__cdecl*)(Il2CppImage * image, int index)>(GetProcAddress(GameAssembly, "il2cpp_image_get_class"));
	static inline  auto il2cpp_class_get_name = reinterpret_cast<const char* (__cdecl*)(Il2CppClass * klass)>(GetProcAddress(GameAssembly, "il2cpp_class_get_name"));
	static inline  auto il2cpp_class_get_method_from_name = reinterpret_cast<MethodInfo * (__cdecl*)(Il2CppClass * klass, const char* name, int argsCount)>(GetProcAddress(GameAssembly, "il2cpp_class_get_method_from_name"));
}
class Il2CppClass
{
public:
	const char* GetName() {
		return il2cppAPI::il2cpp_class_get_name(this);
	}
	void* FindMethod(const char* name, int argsCount) {
		auto method = il2cppAPI::il2cpp_class_get_method_from_name(this, name, argsCount);
		return method ? method->methodaddr : nullptr;
	}
	void* StaticFields() {
		return (void*)(*(int*)((int)this + 0x5C)); // 0x5c - for 32 bit in 64 bit its 0xb8
	}
};
class il2cpp
{
public:
	

	static inline Il2CppClass* FindClass(const char* name, const char* Assemblyname = "Assembly-CSharp") {
		auto domain = il2cppAPI::il2cpp_domain_get();
		auto assembly_namespace = il2cppAPI::il2cpp_domain_assembly_open(domain, Assemblyname);
		auto image = il2cppAPI::il2cpp_assembly_get_image(assembly_namespace);
		auto class_count = il2cppAPI::il2cpp_image_get_class_count(image);
		for (int i = 0; i < class_count; i++)
		{
			auto il2cppclass = il2cppAPI::il2cpp_image_get_class(image, i);
			auto class_name = il2cppclass->GetName();
			if (!strcmp(class_name, name))
			{
				return il2cppclass;
			}
		}
	}

};