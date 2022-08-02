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
	void* methodaddr;
};
class Il2CppClass;
namespace il2cppAPI
{
	auto GameAssembly = GetModuleHandleA("GameAssembly.dll");
	auto il2cpp_domain_get = reinterpret_cast<Il2CppDomain * (__cdecl*)()>(GetProcAddress(GameAssembly, "il2cpp_domain_get"));
	auto il2cpp_domain_assembly_open = reinterpret_cast<Il2CppAssembly * (__cdecl*)(Il2CppDomain * domain, const char* name)>(GetProcAddress(GameAssembly, "il2cpp_domain_assembly_open"));
	auto il2cpp_assembly_get_image = reinterpret_cast<Il2CppImage * (__cdecl*)(Il2CppAssembly * assembly)>(GetProcAddress(GameAssembly, "il2cpp_assembly_get_image"));
	auto il2cpp_image_get_class_count = reinterpret_cast<int(__cdecl*)(Il2CppImage * image)>(GetProcAddress(GameAssembly, "il2cpp_image_get_class_count"));
	auto il2cpp_image_get_class = reinterpret_cast<Il2CppClass * (__cdecl*)(Il2CppImage * image, int index)>(GetProcAddress(GameAssembly, "il2cpp_image_get_class"));
	auto il2cpp_class_get_name = reinterpret_cast<const char* (__cdecl*)(Il2CppClass * klass)>(GetProcAddress(GameAssembly, "il2cpp_class_get_name"));
	auto il2cpp_class_get_method_from_name = reinterpret_cast<MethodInfo * (__cdecl*)(Il2CppClass * klass, const char* name, int argsCount)>(GetProcAddress(GameAssembly, "il2cpp_class_get_method_from_name"));
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
#if defined(_WIN64)
	OFFSET(void*, StaticFields, 0xB8)
#elif  defined(_WIN32)
	OFFSET(void*, StaticFields, 0x5C)
#endif
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