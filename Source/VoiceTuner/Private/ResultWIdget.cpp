// Fill out your copyright notice in the Description page of Project Settings.


#include "ResultWIdget.h"
#include "Components/TextBlock.h"



void UResultWIdget::SetScore(int32 Score)
{
	TB_Score->SetText(FText::AsNumber(Score));
}
