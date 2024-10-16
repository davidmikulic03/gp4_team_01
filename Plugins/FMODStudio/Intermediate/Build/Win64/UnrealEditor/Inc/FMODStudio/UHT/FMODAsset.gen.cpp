// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "FMODStudio/Classes/FMODAsset.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeFMODAsset() {}

// Begin Cross Module References
COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FGuid();
FMODSTUDIO_API UClass* Z_Construct_UClass_UFMODAsset();
FMODSTUDIO_API UClass* Z_Construct_UClass_UFMODAsset_NoRegister();
UPackage* Z_Construct_UPackage__Script_FMODStudio();
// End Cross Module References

// Begin Class UFMODAsset
void UFMODAsset::StaticRegisterNativesUFMODAsset()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UFMODAsset);
UClass* Z_Construct_UClass_UFMODAsset_NoRegister()
{
	return UFMODAsset::StaticClass();
}
struct Z_Construct_UClass_UFMODAsset_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * FMOD Asset.\n */" },
#endif
		{ "IncludePath", "FMODAsset.h" },
		{ "ModuleRelativePath", "Classes/FMODAsset.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "FMOD Asset." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AssetGuid_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** The unique Guid, which matches the one exported from FMOD Studio */" },
#endif
		{ "ModuleRelativePath", "Classes/FMODAsset.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "The unique Guid, which matches the one exported from FMOD Studio" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_AssetGuid;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UFMODAsset>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UFMODAsset_Statics::NewProp_AssetGuid = { "AssetGuid", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UFMODAsset, AssetGuid), Z_Construct_UScriptStruct_FGuid, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AssetGuid_MetaData), NewProp_AssetGuid_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UFMODAsset_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UFMODAsset_Statics::NewProp_AssetGuid,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UFMODAsset_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_UFMODAsset_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UObject,
	(UObject* (*)())Z_Construct_UPackage__Script_FMODStudio,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UFMODAsset_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UFMODAsset_Statics::ClassParams = {
	&UFMODAsset::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_UFMODAsset_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_UFMODAsset_Statics::PropPointers),
	0,
	0x001000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UFMODAsset_Statics::Class_MetaDataParams), Z_Construct_UClass_UFMODAsset_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UFMODAsset()
{
	if (!Z_Registration_Info_UClass_UFMODAsset.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UFMODAsset.OuterSingleton, Z_Construct_UClass_UFMODAsset_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UFMODAsset.OuterSingleton;
}
template<> FMODSTUDIO_API UClass* StaticClass<UFMODAsset>()
{
	return UFMODAsset::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(UFMODAsset);
UFMODAsset::~UFMODAsset() {}
// End Class UFMODAsset

// Begin Registration
struct Z_CompiledInDeferFile_FID_Users_david_mikulic_Perforce_gp4_team_01_FG23_MAL_GP4_Team01_Plugins_FMODStudio_Source_FMODStudio_Classes_FMODAsset_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UFMODAsset, UFMODAsset::StaticClass, TEXT("UFMODAsset"), &Z_Registration_Info_UClass_UFMODAsset, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UFMODAsset), 769181548U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_david_mikulic_Perforce_gp4_team_01_FG23_MAL_GP4_Team01_Plugins_FMODStudio_Source_FMODStudio_Classes_FMODAsset_h_3239715401(TEXT("/Script/FMODStudio"),
	Z_CompiledInDeferFile_FID_Users_david_mikulic_Perforce_gp4_team_01_FG23_MAL_GP4_Team01_Plugins_FMODStudio_Source_FMODStudio_Classes_FMODAsset_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_david_mikulic_Perforce_gp4_team_01_FG23_MAL_GP4_Team01_Plugins_FMODStudio_Source_FMODStudio_Classes_FMODAsset_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
