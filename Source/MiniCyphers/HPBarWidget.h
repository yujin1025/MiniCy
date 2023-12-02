// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MiniCyphersWidget.h"
#include "HPBarWidget.generated.h"

class UProgressBar;

/**
 * 
 */
UCLASS()
class MINICYPHERS_API UHPBarWidget : public UMiniCyphersWidget
{
	GENERATED_BODY()
	
private:
	UPROPERTY()
	UProgressBar* ProgressBar;

protected:
	virtual void NativeConstruct() override;

};
