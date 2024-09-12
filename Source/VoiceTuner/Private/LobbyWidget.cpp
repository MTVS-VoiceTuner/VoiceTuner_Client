// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyWidget.h"
#include "Components/Button.h"
#include "Components/Slider.h"
#include "HSW_NetGameInstance.h"
#include "Components/EditableText.h"
#include "Components/TextBlock.h"

void ULobbyWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	CR_Button_CreateRoom->OnClicked.AddDynamic(this, &ULobbyWidget::CR_OnClickCreatRoom);
	CR_Slider_PlayerCount->OnValueChanged.AddDynamic(this, &ULobbyWidget::CR_OnChangeSliderPlayerCount);

	CR_Slider_PlayerCount->SetValue(2);
}

void ULobbyWidget::CR_OnClickCreatRoom()
{
	auto* gi = Cast<UHSW_NetGameInstance>(GetWorld()->GetGameInstance());
	FString roomName = CR_EditText_RoomName->GetText().ToString();
	int32 count = ( int32)CR_Slider_PlayerCount->GetValue();

	roomName = roomName.TrimStartAndEnd();
	if ( roomName.IsEmpty() )
	{
		return;
	}
	
	gi->CreateMySession(roomName, count);
	
}

void ULobbyWidget::CR_OnChangeSliderPlayerCount(float value)
{
	CR_Text_PlayerCount->SetText(FText::AsNumber((int)value));
}
