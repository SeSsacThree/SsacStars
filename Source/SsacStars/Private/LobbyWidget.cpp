// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyWidget.h"

#include "SsacGameInstance.h"
#include "Components/Button.h"
#include "Components/EditableText.h"
#include "Components/ScrollBox.h"
#include "Components/Slider.h"
#include "Components/TextBlock.h"
#include "Components/WidgetSwitcher.h"
#include "RoomInfoWidget.h"
#include "Blueprint/UserWidget.h"

const int SWITCHER_INDEX_MENU = 0;
const int SWITCHER_INDEX_CREATEROOM = 1;
const int SWITCHER_INDEX_FINDROOM = 2;

void ULobbyWidget::NativeConstruct()
{
	Super::NativeConstruct();


	gi = GetWorld()->GetGameInstance<USsacGameInstance>();
	if (gi)
	{
		gi->onAddRoomInfoDelegate.AddDynamic(this, &ULobbyWidget::AddRoomInfoWidget);
		gi->OnFindingRoomsDelegate.AddDynamic(this, &ULobbyWidget::SetFindActive);
	}

	btn_doCreateRoom->OnClicked.AddDynamic(this, &ULobbyWidget::OnMyClicked_doCreateRoom);
	btn_doFindRoomList->OnClicked.AddDynamic(this, &ULobbyWidget::OnMyDoFindRoomList);

	btn_goCreateRoom->OnClicked.AddDynamic(this, &ULobbyWidget::OnMyGoCreateRoom);
	btn_goFindRoom->OnClicked.AddDynamic(this, &ULobbyWidget::OnMyGoFindRoom);
	btn_goMenuFromCreateRoom->OnClicked.AddDynamic(this, &ULobbyWidget::OnMyGoMenu);
	btn_goMenuFromFindRoom->OnClicked.AddDynamic(this, &ULobbyWidget::OnMyGoMenu);

	// 마우스 커서
	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);

	Slider_maxPlayer->OnValueChanged.AddDynamic(this, &ULobbyWidget::OnMyValueChange_maxplayer);

	text_maxplayer->SetText(FText::AsNumber(Slider_maxPlayer->GetValue()));
	Slider_maxPlayer->SetValue(2);
	Slider_maxPlayer->SetMinValue(2);
	Slider_maxPlayer->SetMaxValue(4);
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

void ULobbyWidget::SwitchPanel(int32 index)
{
	WidgetSwitcherLobby->SetActiveWidgetIndex(index);
}

void ULobbyWidget::OnMyGoMenu()
{
	SwitchPanel(SWITCHER_INDEX_MENU);
}

void ULobbyWidget::OnMyGoCreateRoom()
{
	if (gi)
	{
		gi->myNickName = edit_nickName->GetText().ToString();
	}else
	{
		edit_nickName->SetText(FText::FromString(gi->myNickName));
	}
	SwitchPanel(SWITCHER_INDEX_CREATEROOM);
	// OnMyDoFindRoomList();
}

void ULobbyWidget::OnMyGoFindRoom()
{
	if (gi)
	{
		if (false == edit_nickName->GetText().IsEmpty())
		{
			gi->myNickName = edit_nickName->GetText().ToString();
		}else
		{
			edit_nickName->SetText(FText::FromString(gi->myNickName));
		}
	}
	SwitchPanel(SWITCHER_INDEX_FINDROOM);
	OnMyDoFindRoomList();
}

void ULobbyWidget::OnMyDoFindRoomList()
{
	scroll_RoomList->ClearChildren();
	if(gi)
	{
		gi->FindOtherRooms();
	}
}

void ULobbyWidget::AddRoomInfoWidget(const FRoomInfo& info)
{
	if (nullptr == scroll_RoomList || nullptr == roomInfoFactory)
	return;

	auto ui = CreateWidget<URoomInfoWidget>(GetWorld(), roomInfoFactory);
	ui->SetInfo( info );
	if (scroll_RoomList)
	{
		scroll_RoomList->AddChild(ui);
	}
}

void ULobbyWidget::SetFindActive(bool bActive)
{
	if (bActive)
	{
		btn_doFindRoomList->SetIsEnabled(false);
		txt_findingRooms->SetVisibility(ESlateVisibility::Visible);
	}else
	{
		btn_doFindRoomList->SetIsEnabled(true);
		txt_findingRooms->SetVisibility(ESlateVisibility::Hidden);
	}
}
