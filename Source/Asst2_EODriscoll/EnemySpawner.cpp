// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawner.h"
#include "Enemy.h"

// Sets default values
AEnemySpawner::AEnemySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    SpawnDelayRangeLow = 1;

    SpawnDelayRangeHigh = 30;

    SpawnDelay = 0;

    DifficultyScalar = 1.2;

}

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
    //SpawnEnemy();
   
    GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &AEnemySpawner::SpawnEnemy, 10, true);
	
}

// Called every frame
void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemySpawner::SpawnEnemy()
{


    FActorSpawnParameters SpawnParams;
        
    SpawnParams.Owner = this;
        
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

    if (SpawnCount % 2 == 0) {    
        GetWorld()->SpawnActor<AEnemy>(EnemyBlueprintBlue, GetActorLocation(), GetActorRotation(), SpawnParams); 
    }
    else {
        GetWorld()->SpawnActor<AEnemy>(EnemyBlueprintRed, GetActorLocation(), GetActorRotation(), SpawnParams);
    }

    SpawnCount++;


    SpawnDelayRangeLow = SpawnDelayRangeLow / DifficultyScalar;
    SpawnDelayRangeHigh = SpawnDelayRangeHigh / DifficultyScalar;
 
    if (SpawnDelay > 1) {
        SpawnDelay = FMath::FRandRange(SpawnDelayRangeLow, SpawnDelayRangeHigh);
    }
    else {
        SpawnDelay = 1;
    }

    GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &AEnemySpawner::SpawnEnemy, SpawnDelay, true);
}


