// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemySpawner.generated.h"

UCLASS()
class ASST2_EODRISCOLL_API AEnemySpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemySpawner();

	
	UPROPERTY(EditAnywhere, Category = "Class to Spawn")
	UClass* EnemyBlueprintBlue;

	UPROPERTY(EditAnywhere, Category = "Class to Spawn")
	UClass* EnemyBlueprintRed;

	void SpawnEnemy();

	float SpawnDelayRangeLow;

	float SpawnDelayRangeHigh;

	float SpawnDelay;

	float DifficultyScalar;

	FTimerHandle SpawnTimerHandle;

	int SpawnCount;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
