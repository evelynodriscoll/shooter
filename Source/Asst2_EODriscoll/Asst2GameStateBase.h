// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "Asst2GameStateBase.generated.h"

/**
 * 
 */
UCLASS()
class ASST2_EODRISCOLL_API AAsst2GameStateBase : public AGameStateBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool GameStarted = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
};
