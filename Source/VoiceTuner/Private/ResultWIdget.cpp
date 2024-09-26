// Fill out your copyright notice in the Description page of Project Settings.


#include "ResultWIdget.h"
#include "Components/TextBlock.h"
#include "Components/MultiLineEditableTextBox.h"
#include "Components/Button.h"
#include "Kismet/KismetSystemLibrary.h"



void UResultWIdget::NativeConstruct()
{
	Button_ReqAIFeedBack->OnClicked.AddDynamic(this,&UResultWIdget::OnClickFeedBackButton);
}

void UResultWIdget::NativeTick(const FGeometry& MyGeoMetry , float InDeltaTime)
{
	FString FilePath = FPaths::ProjectContentDir() + TEXT("Sinhodeong_CUTsolution.txt");
	FString LoadText;

	if ( FFileHelper::LoadFileToString(LoadText , *FilePath) ) {
		if ( TB_FeedBack ) {
			TB_FeedBack->SetText(FText::FromString(LoadText));
		}
	}
}

void UResultWIdget::SetScore(int32 Score)
{
	TB_Score->SetText(FText::AsNumber(Score));
}

void UResultWIdget::OnClickFeedBackButton()
{
	UKismetSystemLibrary::LaunchURL("http://192.168.0.44:8989/");
}
