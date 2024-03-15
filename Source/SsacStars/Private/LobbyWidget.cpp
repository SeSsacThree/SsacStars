// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyWidget.h"

#include "SsacGameInstance.h"
#include "Components/Button.h"
#include "Components/EditableText.h"
#include "Components/Slider.h"
#include "Components/TextBlock.h"

void ULobbyWidget::NativeConstruct()
{
	Super::NativeConstruct();

	gi = GetWorld()->GetGameInstance<USsacGameInstance>();

	btn_doCreateRoom->OnClicked.AddDynamic(this, &ULobbyWidget::OnMyClicked_doCreateRoom);

	// 마우스 커서
	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);

	Slider_maxPlayer->OnValueChanged.AddDynamic(this, &ULobbyWidget::OnMyValueChange_maxplayer);

	text_maxplayer->SetText(FText::AsNumber(Slider_maxPlayer->GetValue()));
	Slider_maxPlayer->SetMinValue(2);
	Slider_maxPlayer->SetMaxValue(10);
	Slider_maxPlayer->SetStepSize(1);
	Slider_maxPlayer->MouseUsesStep = true;

}

void ULobbyWidget::OnMyClicked_doCreateRoom()
{
	FString roomName = edit_roomName->GetText().ToString();

	if (roomName.TrimStartAndEnd().IsEmpty())
	{
		UE_LOG(LogTemp,Warning, TEXT("방 이름 썼어~~??^^"))
	}

	TArray<FString>badWords;
	badWords.Add(TEXT("최재원"));
	badWords.Add(TEXT("김민서"));
	badWords.Add(TEXT("정윤선"));
	for(int i = 0; i < badWords.Num(); i++)
	{
		if (roomName.Contains(badWords[i]))
		{
			UE_LOG(LogTemp, Warning, TEXT("방 이름 땡~~"));
			return;
		}
	}

	int32 maxPlayer = Slider_maxPlayer->GetValue();
	gi->CreateRoom( maxPlayer, roomName);
}

void ULobbyWidget::OnMyValueChange_maxplayer(float value)
{
	text_maxplayer->SetText(FText::AsNumber(value));
}
