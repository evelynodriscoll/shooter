// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Asst2_EODriscollCharacter.h"
#include "Enemy.generated.h"


class UPawnSensingComponent;

UENUM(BlueprintType)
enum class EAIState : uint8
{
	Idle,
	Suspicious,
	Alerted,
	Attack
};


UCLASS()
class ASST2_EODRISCOLL_API AEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	AEnemy();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UPawnSensingComponent* PawnSensingComp;

	UFUNCTION()
	void OnPawnSeen(APawn* SeenPawn);

	UFUNCTION()
	void DealDamage(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
	void ResetState();

	FTimerHandle TimerHandle_ResetState;

	EAIState GuardState;

	void SetGuardState(EAIState NewState);

	UFUNCTION(BlueprintImplementableEvent, Category = "AI")
	void OnStateChanged(EAIState NewState);

	UPROPERTY(EditDefaultsOnly)
	float MaximumHealth;

	UPROPERTY(BlueprintReadOnly)
	float CurrentHealth;


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	AActor* TargetActor;

};
