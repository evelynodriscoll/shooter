#include "Enemy.h"
#include "NavigationSystem.h"
#include "AIModule/Classes/Blueprint/AIBlueprintHelperLibrary.h"
#include "Perception/PawnSensingComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include <Components/CapsuleComponent.h>
#include "Asst2_EODriscollProjectile.h"

AEnemy::AEnemy() : Super()
{
	//SET PrimaryActorTick.bCanEverTick to true	
	PrimaryActorTick.bCanEverTick = true;

	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));
	PawnSensingComp->OnSeePawn.AddDynamic(this, &AEnemy::OnPawnSeen);

	EnemyCollision = GetCapsuleComponent();
	EnemyCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	EnemyCollision->OnComponentHit.AddDynamic(this, &AEnemy::DealDamage);

	GuardState = EAIState::Idle;
}

void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = MaximumHealth;

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

void AEnemy::DealDamage(UPrimitiveComponent* HitComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	FVector NormalImpulse,
	const FHitResult& Hit)
{
	if (OtherActor)
	{
		if (AAsst2_EODriscollCharacter* Character = Cast<AAsst2_EODriscollCharacter>(OtherActor))
		{
			Character->DecreaseHealth();
		
		}
		if (AAsst2_EODriscollProjectile* Projectile = Cast<AAsst2_EODriscollProjectile>(OtherActor)) {

			if ((this->ActorHasTag("Red") && OtherActor->ActorHasTag("Red")) || (this->ActorHasTag("Blue") && OtherActor->ActorHasTag("Blue"))) {

				CurrentHealth -= 1;

				if (CurrentHealth == 0) {
					Destroy();
				}
			}
		}
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



