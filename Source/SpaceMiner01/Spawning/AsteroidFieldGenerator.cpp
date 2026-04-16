#include "AsteroidFieldGenerator.h"
#include "MassExecutionContext.h"
#include "MassProcessor.h"
#include "MassEntitySettings.h"
#include "AssetToolsModule.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "UObject/SavePackage.h"


void GenerateTemp(TArray<FMassEntitySpawnDataGeneratorResult>& Results, TConstArrayView<FMassSpawnedEntityType>& EntityTypes)
{
    Results.SetNum(EntityTypes.Num());

    for (int32 i = 0; i < EntityTypes.Num(); ++i)
    {
        // MASSIVE STEP: Link the result back to the config
        // If Results[i].EntityConfig = EntityTypes[i].EntityConfig; fails to compile:
        // It means your version of Mass uses the index to match them automatically.
        // In that case, ENSURE Results.SetNum matches EntityTypes.Num exactly.

        Results[i].SpawnData.InitializeAs<FMassTransformsSpawnData>();
        FMassTransformsSpawnData& TransformsData = Results[i].SpawnData.GetMutable<FMassTransformsSpawnData>();

        // Ensure you are adding exactly 100 transforms to this specific Results[i]
        for (int32 j = 0; j < 100; ++j) {
            TransformsData.Transforms.Add(FTransform(FVector(j * 100, 0, 0)));
        }
    }
}


void UAsteroidFieldGenerator::Generate(UObject& QueryOwner,
    TConstArrayView<FMassSpawnedEntityType> EntityTypes,
    int32 Count,
    FFinishedGeneratingSpawnDataSignature& FinishedGeneratingSpawnPointsDelegate) const
{
    //GenerateMassEntitySettings();

    FMessageDialog::Open(EAppMsgType::Ok, FText::FromString("GENERATOR IS ALIVE!"));
    UE_LOG(LogTemp, Warning, TEXT("Generator found %d Entity Types"), EntityTypes.Num()); 
    if (EntityTypes.Num() == 0)
    {
        UE_LOG(LogTemp, Error, TEXT("CRITICAL: No Entity Types passed to Generator! Check Mass Spawner 'Entity Types' array."));
        return;
    }
    // Get Spawner Location
    AActor* SpawnerActor = Cast<AActor>(&QueryOwner);
    FVector Center = SpawnerActor ? SpawnerActor->GetActorLocation() : FVector::ZeroVector;

    // 1. Initialize the Results array to the exact size of EntityTypes
    TArray<FMassEntitySpawnDataGeneratorResult> Results;
    Results.AddDefaulted(EntityTypes.Num());

    // Calculate count per type
    int32 NumToSpawn = Count / FMath::Max(1, EntityTypes.Num());
    GenerateTemp(Results, EntityTypes);

   /* for (int32 i = 0; i < EntityTypes.Num(); ++i)
    {
        // 2. Initialize the struct at index [i]
        // Mass knows that Results[i] maps to EntityTypes[i]
        Results[i].SpawnData.InitializeAs<FMassTransformsSpawnData>();
        FMassTransformsSpawnData& TransformsData = Results[i].SpawnData.GetMutable<FMassTransformsSpawnData>();

        for (int32 j = 0; j < NumToSpawn; ++j)
        {
            FTransform& NewTransform = TransformsData.Transforms.AddDefaulted_GetRef();

            // Randomize position
            FVector RandomPos = Center + (FMath::VRand() * FMath::RandRange(500.f, 5000.f));
            NewTransform.SetLocation(RandomPos);

            // Random Rotation
            NewTransform.SetRotation(FQuat(FMath::VRand(), FMath::RandRange(0.f, 360.f)));
            NewTransform.SetScale3D(FVector(FMath::RandRange(0.5f, 2.5f)));
        }

        UE_LOG(LogTemp, Warning, TEXT("Generated %d transforms for Entity Type Index %d"),
            TransformsData.Transforms.Num(), i);
    }*/

    // 3. Send it back
    FinishedGeneratingSpawnPointsDelegate.ExecuteIfBound(Results);
}


void UAsteroidFieldGenerator::GenerateMassEntitySettings() const
{
    UE_LOG(LogTemp, Warning, TEXT("GenerateMassEntitySettings"));
    // TEMPORARY: Force create the settings asset
    UPackage* Package = CreatePackage(TEXT("/Game/DA_MassSettings"));
    UMassEntitySettings* NewSettings = NewObject<UMassEntitySettings>(Package, UMassEntitySettings::StaticClass(), TEXT("DA_MassSettings"), RF_Public | RF_Standalone);
    if (NewSettings)
    {
        UE_LOG(LogTemp, Warning, TEXT("GenerateMassEntitySettings: NewSettings success"));
        FAssetRegistryModule::AssetCreated(NewSettings);
        // This part actually writes the file to your /Content/ folder
        FString PackageFileName = FPackageName::LongPackageNameToFilename(TEXT("/Game/DA_MassSettings"), FPackageName::GetAssetPackageExtension());
        FSavePackageArgs SaveArgs;
        SaveArgs.TopLevelFlags = RF_Public | RF_Standalone;
        SaveArgs.Error = GLog;

        UPackage::SavePackage(Package, NewSettings, *PackageFileName, SaveArgs);
        UE_LOG(LogTemp, Warning, TEXT("MASS SETTINGS ASSET CREATED IN CONTENT FOLDER!"));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("GenerateMassEntitySettings: NewSettings failure"));
    }
}