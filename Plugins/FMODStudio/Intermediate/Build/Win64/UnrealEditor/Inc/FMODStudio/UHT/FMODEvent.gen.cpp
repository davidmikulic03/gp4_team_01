// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "FMODStudio/Classes/FMODEvent.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeFMODEvent() {}

// Begin Cross Module References
FMODSTUDIO_API UClass* Z_Construct_UClass_UFMODAsset();
FMODSTUDIO_API UClass* Z_Construct_UClass_UFMODEvent();
FMODSTUDIO_API UClass* Z_Construct_UClass_UFMODEvent_NoRegister();
UPackage* Z_Construct_UPackage__Script_FMODStudio();
// End Cross Module References

// Begin Class UFMODEvent
void UFMODEvent::StaticRegisterNativesUFMODEvent()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UFMODEvent);
UClass* Z_Construct_UClass_UFMODEvent_NoRegister()
{
	return UFMODEvent::StaticClass();
}
struct Z_Construct_UClass_UFMODEvent_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * FMOD Event Asset.\n */" },
#endif
		{ "IncludePath", "FMODEvent.h" },
		{ "ModuleRelativePath", "Classes/FMODEvent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "FMOD Event Asset." },
#endif
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UFMODEvent>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_UFMODEvent_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UFMODAsset,
	(UObject* (*)())Z_Construct_UPackage__Script_FMODStudio,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UFMODEvent_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UFMODEvent_Statics::ClassParams = {
	&UFMODEvent::StaticClass,
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
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UFMODEvent_Statics::Class_MetaDataParams), Z_Construct_UClass_UFMODEvent_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UFMODEvent()
{
	if (!Z_Registration_Info_UClass_UFMODEvent.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UFMODEvent.OuterSingleton, Z_Construct_UClass_UFMODEvent_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UFMODEvent.OuterSingleton;
}
template<> FMODSTUDIO_API UClass* StaticClass<UFMODEvent>()
{
	return UFMODEvent::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(UFMODEvent);
UFMODEvent::~UFMODEvent() {}
// End Class UFMODEvent

// Begin Registration
struct Z_CompiledInDeferFile_FID_Users_david_mikulic_Perforce_gp4_team_01_FG23_MAL_GP4_Team01_Plugins_FMODStudio_Source_FMODStudio_Classes_FMODEvent_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UFMODEvent, UFMODEvent::StaticClass, TEXT("UFMODEvent"), &Z_Registration_Info_UClass_UFMODEvent, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UFMODEvent), 1319635412U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_david_mikulic_Perforce_gp4_team_01_FG23_MAL_GP4_Team01_Plugins_FMODStudio_Source_FMODStudio_Classes_FMODEvent_h_138099340(TEXT("/Script/FMODStudio"),
	Z_CompiledInDeferFile_FID_Users_david_mikulic_Perforce_gp4_team_01_FG23_MAL_GP4_Team01_Plugins_FMODStudio_Source_FMODStudio_Classes_FMODEvent_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_david_mikulic_Perforce_gp4_team_01_FG23_MAL_GP4_Team01_Plugins_FMODStudio_Source_FMODStudio_Classes_FMODEvent_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
