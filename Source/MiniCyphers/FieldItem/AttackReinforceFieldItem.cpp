// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackReinforceFieldItem.h"
#include "FieldItem.h"

AAttackReinforceFieldItem::AAttackReinforceFieldItem()
{
	ItemType = EItemType::AttackReinforce;
}

void AAttackReinforceFieldItem::OnTrigger()
{
	Super::OnTrigger();
}
