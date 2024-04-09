// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHUD.h"
#include "Asst2_EODriscollCharacter.h"
#include "TP_WeaponComponent.h"
#include "Components/Button.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

//UI HUD
void UPlayerHUD::NativeConstruct()
{
	if (ClickMeButton)
	{
		//ClickMeButton->OnClicked.AddDynamic(this, &UPlayerHud::ButtonClicked);
	}


}

//UI HUD
bool UPlayerHUD::Initialize()
{
	bool Success = Super::Initialize();
	if (WeaponAmmoCountText)
	{
		WeaponAmmoCountText->TextDelegate.BindUFunction(this, "SetWeaponAmmoCount");
	}

	if (HealthBar)
	{
		HealthBar->PercentDelegate.BindUFunction(this, "SetHealthProgress");
	}

	//if (GameOverText)
	//{
		//GameOverText->TextDelegate.BindUFunction(this, "GameOver");
	//}


	return true;

}

//UI HUD
FText UPlayerHUD::SetWeaponAmmoCount()
{
	APlayerController* PC = GetOwningPlayer();
	if (PC)
	{
		AAsst2_EODriscollCharacter* Char = Cast<AAsst2_EODriscollCharacter>(PC->GetPawn());
		if (Char)
		{
			UTP_WeaponComponent* Weapon = Char->CurrentWeapon;
			//WeaponAmmoCountText->SetText(FText::AsNumber(Weapon->CurrentAmmo) );
			//return FText::FromString(FString::FromInt(Weapon->CurrentAmmo));
			int AmmoCount = 0;
			int MaxAmmo = 0;
			if (Weapon)
			{
				AmmoCount = Weapon->CurrentAmmo;
				MaxAmmo = Weapon->MaximumAmmo;
			}
			return FText::FromString(FString::FromInt(AmmoCount) + "/" + FString::FromInt(MaxAmmo));
			//return FText::AsNumber(AmmoCount);
		}
	}
	return FText::FromString("NULL");
}

float UPlayerHUD::SetHealthProgress()
{

	APlayerController* PC = GetOwningPlayer();
	if (PC)
	{
		AAsst2_EODriscollCharacter* Player = Cast<AAsst2_EODriscollCharacter>(PC->GetCharacter());
		if (Player)
		{
		
				return Player->CurrentHealth / Player->MaximumHealth;
			}
		

	}
	return 1;
}

FText UPlayerHUD::GameOver()
{
	FText returnString = FText::FromString("");

	APlayerController* PC = GetOwningPlayer();
	if (PC)
	{
		AAsst2_EODriscollCharacter* Player = Cast<AAsst2_EODriscollCharacter>(PC->GetCharacter());
		if (Player->CurrentHealth == 0) {
			returnString = FText::FromString("GAME OVER");
		}
	}

	return returnString;
}


//UI HUD
void UPlayerHUD::ButtonClicked()
{
	//WeaponAmmoCountText->SetColorAndOpacity(FSlateColor(FLinearColor::Blue));

	APlayerController* PC = GetOwningPlayer();
	if (PC)
	{
		PC->ConsoleCommand("RestartLevel");
	}

}

