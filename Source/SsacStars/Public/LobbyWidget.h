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
	class UImage* Image1;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UImage* Image2;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UImage* Image3;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UImage* Image4;

	UPROPERTY( EditDefaultsOnly , meta = (BindWidget) )
	class UEditableText* edit_roomName;

	UPROPERTY( EditDefaultsOnly , meta = (BindWidget) )
	class USlider* Slider_maxPlayer;

	UPROPERTY( EditDefaultsOnly , meta = (BindWidget) )
	class UTextBlock* text_maxplayer;

	UPROPERTY( EditDefaultsOnly , meta = (BindWidget) )
	class UButton* btn_doCreateRoom;

	UFUNCTION()
	void OnMyClicked_doCreateRoom();

	UFUNCTION()
	void OnMyValueChange_maxplayer(float value);
	
};
