// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LobbyWidget.generated.h"

/**
 * 
 */
UCLASS()
class SSACSTARS_API ULobbyWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;

	UPROPERTY()
	class USsacGameInstance* gi;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UImage* Image_bg;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UImage* Image1;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UImage* Image2;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UImage* Image3;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UImage* Image4;

	UPROPERTY( EditDefaultsOnly , meta = (BindWidget))
	class UEditableText* edit_roomName;

	UPROPERTY( EditDefaultsOnly , meta = (BindWidget))
	class USlider* Slider_maxPlayer;

	UPROPERTY( EditDefaultsOnly , meta = (BindWidget))
	class UTextBlock* text_maxplayer;

	UPROPERTY( EditDefaultsOnly , meta = (BindWidget))
	class UButton* btn_doCreateRoom;

	UPROPERTY( EditDefaultsOnly , meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* Image_bg_Animation;

	UFUNCTION()
	void OnMyClicked_doCreateRoom();

	UFUNCTION()
	void OnMyValueChange_maxplayer(float value);

	UPROPERTY( EditDefaultsOnly , meta = (BindWidget))
	class UWidgetSwitcher* WidgetSwitcherLobby;

	UPROPERTY( EditDefaultsOnly , meta = (BindWidget))
	class UButton* btn_goCreateRoom;

	UPROPERTY( EditDefaultsOnly , meta = (BindWidget))
	class UButton* btn_goFindRoom;

	UPROPERTY( EditDefaultsOnly , meta = (BindWidget))
	class UButton* btn_goMenuFromCreateRoom;

	UPROPERTY( EditDefaultsOnly , meta = (BindWidget))
	class UButton* btn_goMenuFromFindRoom;

	void SwitchPanel(int32 index);

	UFUNCTION()
	void OnMyGoMenu();

	UFUNCTION()
	void OnMyGoCreateRoom();

	UFUNCTION()
	void OnMyGoFindRoom();

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UScrollBox* scroll_RoomList;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class URoomInfoWidget> roomInfoFactory;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* btn_doFindRoomList;

	UFUNCTION()
	void OnMyDoFindRoomList();

	UFUNCTION()
	void AddRoomInfoWidget(const struct FRoomInfo& info);

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UTextBlock* txt_findingRooms;

	void SetFindActive(bool bActive);

	UPROPERTY( EditDefaultsOnly , meta = (BindWidget) )
	class UEditableText* edit_nickName;
	
};
