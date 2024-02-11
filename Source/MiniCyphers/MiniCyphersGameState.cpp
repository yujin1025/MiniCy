// Fill out your copyright notice in the Description page of Project Settings.


#include "MiniCyphersGameState.h"

void AMiniCyphersGameState::OnChangedHealth(int ObjectID, float Amount)
{

}

TArray<FQuestPhaseData*> AMiniCyphersGameState::GetQuestPhaseDatas(int PhaseNumber)
{
	TArray<FQuestPhaseData*> PhaseDatas;
	TArray<FQuestPhaseData*> ResultPhaseDatas;

	QuestPhaseTable->GetAllRows(TEXT(""), OUT PhaseDatas);

	for (auto& Data : PhaseDatas)
	{
		if (Data->PhaseNumber != PhaseNumber)
			continue;

		ResultPhaseDatas.Add(Data);
	}

	return ResultPhaseDatas;
}

FQuestData* AMiniCyphersGameState::GetQuestData(int QuestId)
{
	TArray<FQuestData*> QuestDatas;

	QuestTable->GetAllRows(TEXT(""), OUT QuestDatas);

	for (auto& QuestData : QuestDatas)
	{
		if (QuestData->QuestId != QuestId)
			continue;

		return QuestData;
	}

	return nullptr;
}

TArray<FQuestData*> AMiniCyphersGameState::GetQuestDatas(int PhaseNumber)
{
	TArray<FQuestPhaseData*> PhaseDatas = GetQuestPhaseDatas(PhaseNumber);
	TArray<FQuestData*> QuestDatas;

	for (auto& PhaseData : PhaseDatas)
	{
		FQuestData* QuestData = GetQuestData(PhaseData->QuestId);
		if (QuestData == nullptr)
			continue;

		QuestDatas.Add(QuestData);
	}

	return QuestDatas;
}

bool AMiniCyphersGameState::TryChangePhase(int NextPhaseNumber)
{
	if (CurrentPhaseNumber >= 0)
	{
		TArray<FQuestData*> QuestDatas = GetQuestDatas(CurrentPhaseNumber);

		for (auto& QuestData : QuestDatas)
		{
			int32* QuestProgress = QuestProgressDatas.Find(QuestData->QuestId);
			if (QuestProgress == nullptr)
				continue;

			int Progress = *(QuestProgress);
			if (Progress >= QuestData->MaxProgress)
				continue;

			return false;
		}
	}

	CurrentPhaseNumber = NextPhaseNumber;
	OnChangedPhase(NextPhaseNumber);
	return true;
}

void AMiniCyphersGameState::OnChangedPhase(int PhaseNumber)
{
	TArray<FQuestData*> QuestDatas = GetQuestDatas(PhaseNumber);

	QuestProgressDatas.Reset();
	for (auto& QuestData : QuestDatas)
	{
		QuestProgressDatas.Add(QuestData->QuestId, 0);
	}

	OnChangedQuestDelegate.Broadcast(QuestDatas, QuestProgressDatas);
}

bool AMiniCyphersGameState::TryCompleteQuest(int QuestId)
{
	FQuestData* QuestData = GetQuestData(QuestId);
	if (QuestData == nullptr)
		return false;

	int32* QuestProgress = QuestProgressDatas.Find(QuestId);
	if (QuestProgress == nullptr)
		return false;

	int Progress = *(QuestProgress);
	if (Progress >= QuestData->MaxProgress)
		return false;

	QuestProgressDatas[QuestId]++;
	OnChangedQuest(QuestId);
	return true;
}

void AMiniCyphersGameState::OnChangedQuest(int QuestId)
{
	TArray<FQuestData*> QuestDatas = GetQuestDatas(CurrentPhaseNumber);
	OnChangedQuestDelegate.Broadcast(QuestDatas, QuestProgressDatas);
}
