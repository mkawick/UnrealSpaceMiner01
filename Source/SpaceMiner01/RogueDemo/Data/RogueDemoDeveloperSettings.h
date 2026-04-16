// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettingsBackedByCVars.h"
#include "RogueDemoDeveloperSettings.generated.h"

class UMassEntityConfigAsset;
/**
 * 
 */
UCLASS(Config = Game, DefaultConfig, meta = (DisplayName = "Rogue Demo Settings"))
class SPACEMINER01_API URogueDemoDeveloperSettings : public UDeveloperSettingsBackedByCVars
{
	GENERATED_BODY()
	
public:
	URogueDemoDeveloperSettings();
	
	UPROPERTY(EditDefaultsOnly, Config, Category="System Settings")
	int MaxSpawnPerTick = 64;
	
	UPROPERTY(EditDefaultsOnly, Config, Category="System Settings")
	TSoftObjectPtr<UMassEntityConfigAsset> EntityConfig;
};
