// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHUD.generated.h"

/**
 * 
 */
UCLASS()
class ASST2_EODRISCOLL_API UPlayerHUD : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* WeaponAmmoCountText = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UProgressBar* HealthBar = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* GameOverText = nullptr;

	virtual bool Initialize() override;

	UFUNCTION()
	FText SetWeaponAmmoCount();

	UFUNCTION()
	FText SetGameOverText();

	void RestartLevel();

	UFUNCTION()
	float SetHealthProgress();
	
};



