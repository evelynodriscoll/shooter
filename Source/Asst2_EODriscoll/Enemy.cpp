#include "Enemy.h"
#include "NavigationSystem.h"
#include "AIModule/Classes/Blueprint/AIBlueprintHelperLibrary.h"
#include "Perception/PawnSensingComponent.h"
#include "Kismet/KismetMathLibrary.h"

AEnemy::AEnemy() : Super()
{
	//SET PrimaryActorTick.bCanEverTick to true	
	PrimaryActorTick.bCanEverTick = true;

	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));

	PawnSensingComp->OnSeePawn.AddDynamic(this, &AEnemy::OnPawnSeen);

	GuardState = EAIState::Idle;
}

void AEnemy::BeginPlay()
{
	Super::BeginPlay();

}

void AEnemy::OnPawnSeen(APawn* SeenPawn)
{
	if (SeenPawn == nullptr)
	{

		return;
	}

	TargetActor = SeenPawn;

	SetGuardState(EAIState::Alerted);

	AController* AIController = GetController();

	if (AIController)
	{
		GetWorldTimerManager().ClearTimer(TimerHandle_ResetState);
	
	}

}


void AEnemy::ResetState()
{
	if (GuardState == EAIState::Alerted)
	{
		return;
	}


	SetGuardState(EAIState::Idle);

}



void AEnemy::SetGuardState(EAIState NewState)
{
	if (GuardState == NewState)
	{
		return;
	}

	GuardState = NewState;
}


void AEnemy::Tick(float DeltaTime)
{

	Super::Tick(DeltaTime);

	if (TargetActor)
	{
		FVector MyLoc = GetActorLocation();
		FVector TargetLoc = TargetActor->GetActorLocation();
		FVector Dir = (TargetLoc - MyLoc);
		Dir.Normalize();
		SetActorRotation(FMath::Lerp(GetActorRotation(), Dir.Rotation(), 0.05f));

		if (GuardState == EAIState::Alerted)
		{
			UAIBlueprintHelperLibrary::SimpleMoveToActor(GetController(), TargetActor);
		}

	}
}



