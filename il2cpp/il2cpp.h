#pragma once
#include <Windows.h>
#include <map>
#define OFFSET( type, func, offset ) [[nodiscard]] std::add_lvalue_reference_t< type > func()  { return *reinterpret_cast< std::add_pointer_t< type > >( reinterpret_cast< std::uintptr_t >( this ) + offset ); }
class Il2CppDomain;
class Il2CppAssembly;
class Il2CppImage;
class MethodInfo
{
public:
	void* pMethod;
};
class Il2CppClass;
class il2cppAPI
{
public:
	static inline HMODULE GameAssembly = GetModuleHandleA("GameAssembly.dll");
	static inline auto il2cpp_domain_get = reinterpret_cast<Il2CppDomain * (__cdecl*)()>(GetProcAddress(GameAssembly, "il2cpp_domain_get"));
	static inline auto il2cpp_domain_assembly_open = reinterpret_cast<Il2CppAssembly * (__cdecl*)(Il2CppDomain * domain, const char* name)>(GetProcAddress(GameAssembly, "il2cpp_domain_assembly_open"));
	static inline auto il2cpp_assembly_get_image = reinterpret_cast<Il2CppImage * (__cdecl*)(Il2CppAssembly * assembly)>(GetProcAddress(GameAssembly, "il2cpp_assembly_get_image"));
	static inline auto il2cpp_image_get_class_count = reinterpret_cast<int(__cdecl*)(Il2CppImage * image)>(GetProcAddress(GameAssembly, "il2cpp_image_get_class_count"));
	static inline auto il2cpp_image_get_class = reinterpret_cast<Il2CppClass * (__cdecl*)(Il2CppImage * image, int index)>(GetProcAddress(GameAssembly, "il2cpp_image_get_class"));
	static inline auto il2cpp_class_get_name = reinterpret_cast<const char* (__cdecl*)(Il2CppClass * klass)>(GetProcAddress(GameAssembly, "il2cpp_class_get_name"));
	static inline auto il2cpp_class_get_method_from_name = reinterpret_cast<MethodInfo * (__cdecl*)(Il2CppClass * klass, const char* name, int argsCount)>(GetProcAddress(GameAssembly, "il2cpp_class_get_method_from_name"));
};
class Il2CppClass
{
public:
	const char* GetName() {
		return il2cppAPI::il2cpp_class_get_name(this);
	}
	void* FindMethod(const char* name, int argsCount) {
		auto method_info = il2cppAPI::il2cpp_class_get_method_from_name(this, name, argsCount);
		return method_info ? method_info->pMethod : nullptr;
	}
#if defined(_WIN64)
	OFFSET(void*, StaticFields, 0xB8)
#elif  defined(_WIN32)
	OFFSET(void*, StaticFields, 0x5C)
#endif
};
class il2cpp
{
public:
	static inline Il2CppClass* FindClass(const char* name, const char* ModuleNameSpace = "Assembly-CSharp") {
		auto domain = il2cppAPI::il2cpp_domain_get();
		auto module_namespace = il2cppAPI::il2cpp_domain_assembly_open(domain, ModuleNameSpace);
		if (!module_namespace) return nullptr;
		auto image = il2cppAPI::il2cpp_assembly_get_image(module_namespace);
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
