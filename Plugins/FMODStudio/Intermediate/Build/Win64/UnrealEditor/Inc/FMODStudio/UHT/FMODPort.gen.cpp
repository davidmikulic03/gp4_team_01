// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "FMODStudio/Classes/FMODPort.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeFMODPort() {}

// Begin Cross Module References
FMODSTUDIO_API UClass* Z_Construct_UClass_UFMODAsset();
FMODSTUDIO_API UClass* Z_Construct_UClass_UFMODPort();
FMODSTUDIO_API UClass* Z_Construct_UClass_UFMODPort_NoRegister();
UPackage* Z_Construct_UPackage__Script_FMODStudio();
// End Cross Module References

// Begin Class UFMODPort
void UFMODPort::StaticRegisterNativesUFMODPort()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UFMODPort);
UClass* Z_Construct_UClass_UFMODPort_NoRegister()
{
	return UFMODPort::StaticClass();
}
struct Z_Construct_UClass_UFMODPort_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * FMOD Port Asset.\n */" },
#endif
		{ "IncludePath", "FMODPort.h" },
		{ "ModuleRelativePath", "Classes/FMODPort.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "FMOD Port Asset." },
#endif
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UFMODPort>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_UFMODPort_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UFMODAsset,
	(UObject* (*)())Z_Construct_UPackage__Script_FMODStudio,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UFMODPort_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UFMODPort_Statics::ClassParams = {
	&UFMODPort::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	0,
	0,
	0x001000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UFMODPort_Statics::Class_MetaDataParams), Z_Construct_UClass_UFMODPort_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UFMODPort()
{
	if (!Z_Registration_Info_UClass_UFMODPort.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UFMODPort.OuterSingleton, Z_Construct_UClass_UFMODPort_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UFMODPort.OuterSingleton;
}
template<> FMODSTUDIO_API UClass* StaticClass<UFMODPort>()
{
	return UFMODPort::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(UFMODPort);
UFMODPort::~UFMODPort() {}
// End Class UFMODPort

// Begin Registration
struct Z_CompiledInDeferFile_FID_Users_david_mikulic_Perforce_gp4_team_01_FG23_MAL_GP4_Team01_Plugins_FMODStudio_Source_FMODStudio_Classes_FMODPort_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UFMODPort, UFMODPort::StaticClass, TEXT("UFMODPort"), &Z_Registration_Info_UClass_UFMODPort, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UFMODPort), 3091690480U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_david_mikulic_Perforce_gp4_team_01_FG23_MAL_GP4_Team01_Plugins_FMODStudio_Source_FMODStudio_Classes_FMODPort_h_3559520299(TEXT("/Script/FMODStudio"),
	Z_CompiledInDeferFile_FID_Users_david_mikulic_Perforce_gp4_team_01_FG23_MAL_GP4_Team01_Plugins_FMODStudio_Source_FMODStudio_Classes_FMODPort_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_david_mikulic_Perforce_gp4_team_01_FG23_MAL_GP4_Team01_Plugins_FMODStudio_Source_FMODStudio_Classes_FMODPort_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
