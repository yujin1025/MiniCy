// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MiniCyphersWidget.h"
#include "CrossHairWidget.generated.h"

class UImage;

/**
 * 
 */
UCLASS()
class MINICYPHERS_API UCrossHairWidget : public UMiniCyphersWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
	FVector2D GetScreenMousePosition();
	FVector2D GetAimScreenPosition(UImage* AimImage);

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> AimPoint;


	
};
