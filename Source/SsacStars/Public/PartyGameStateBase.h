// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "PartyGameStateBase.generated.h"

/**
 *
 */
UCLASS()
class SSACSTARS_API APartyGameStateBase : public AGameStateBase
{
	GENERATED_BODY()
public:

	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere)
	class APartyGameModeBase* GM;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Replicated)
	TArray<class APartyPlayer*> PlayerList;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Replicated)
	class APartyPlayer* CurrentPlayer;
	UPROPERTY(EditAnywhere, Replicated)
	class APartyScore* Star;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Replicated)
	TArray<class ABlueBoardSpace*> FoundSpaces;

public:

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UMainUI> SelectUiFactory;
	UPROPERTY()
	class UMainUI* SelectUi;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UStatusUi> StatusUiFactory;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UItemUI> ItemUiFactory;
	UPROPERTY()
	class UItemUI* ItemUi;
	UPROPERTY()
	class UStatusUi* StatusUi;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UTrapWidget> TrapUiFactory;
	UPROPERTY()
	class UTrapWidget* TrapUi;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UGetCoins> GetCoinsUiFactory;
	UPROPERTY()
	class UGetCoins* GetCoinsUi;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UGetCoins_Pingu> UGetCoins_PinguUiFactory;
	UPROPERTY()
	class UGetCoins_Pingu* UGetCoins_PinguUi;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class URandomItemWidget> GetItemUiFactory;
	UPROPERTY()
	class URandomItemWidget* GetItemUi;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UPlayerUiCard> PlayerUiCardFactory;
	UPROPERTY(Replicated)
	class UTenCoinsforaStar* TenCoinsforaStarUi;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UTenCoinsforaStar> TenCoinsforaStarUiFactory;


public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USkeletalMesh* Mesh1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMesh* Mesh2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMesh* Mesh3;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMesh* Mesh4;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Replicated)
	int CurrentPlayerIndex;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Replicated)
	int PlayerCount = 0;
public:
	UFUNCTION(Server, Reliable)
	void ServerMoveCameraToPlayer(APartyPlayer* InPlayer);
	UFUNCTION(NetMulticast, Reliable)
	void MultiMoveCameraToPlayer(APartyPlayer* InPlayer);

	UFUNCTION(Server, Reliable)
	void ServerMoveCameraToStar();
	UFUNCTION(NetMulticast, Reliable)
	void MultiMoveCameraToStar();

	UFUNCTION(Server, Reliable)
	void ServerUpdateAppeareance(APartyPlayer* Player, int Index);
	UFUNCTION(NetMulticast, Reliable)
	void MultiUpdateAppeareance(APartyPlayer* Player, int Index);

public:
	UFUNCTION(Server, Reliable)
	void ServerViewStatusUi();
	UFUNCTION(NetMulticast, Reliable)
	void MultiViewStatusUi();
	UFUNCTION(Server, Reliable)
	void ServerViewItemUi();
	UFUNCTION(NetMulticast, Reliable)
	void MultiViewItemUi();
	UFUNCTION(Server, Reliable)
	void ServerViewSelectUi();
	UFUNCTION(NetMulticast, Reliable)
	void MultiViewSelectUi();
	UFUNCTION(Server, Reliable)
	void ServerViewTrapUi();
	UFUNCTION(NetMulticast, Reliable)
	void MultiViewTrapUi();
	UFUNCTION(Server, Reliable)
	void ServerViewTenCoinsforaStarUi();
	UFUNCTION(NetMulticast, Reliable)
	void MultiViewTenCoinsforaStarUi();
	UFUNCTION(Server, Reliable)
	void ServerGetCoinsUi();
	UFUNCTION(NetMulticast, Reliable)
	void MultiGetCoinsUi();
	UFUNCTION(Server, Reliable)
	void ServerGetCoins_PinguUi();
	UFUNCTION(NetMulticast, Reliable)
	void MultiGetCoins_PinguUi();

public:
	UFUNCTION(Server, Reliable)
	void ServerRemoveSelectUi();
	UFUNCTION(NetMulticast, Reliable)
	void MultiRemoveSelectUi();
	UFUNCTION(Server, Reliable)
	void ServerRemoveItemUi();
	UFUNCTION(NetMulticast, Reliable)
	void MultiRemoveItemUi();
	UFUNCTION(Server, Reliable)
	void ServerCloseView();
	UFUNCTION(NetMulticast, Reliable)
	void MultiCloseView();

public:
	UFUNCTION(Server, Reliable)
	void ServerChangeStarSpace();
	UFUNCTION(NetMulticast, Reliable)
	void MultiChangeStarSpace(ABlueBoardSpace* Space);
	UFUNCTION(Server, Reliable)
	void ServerUpdateGameInfo(int Index);
	UFUNCTION(NetMulticast, Reliable)
	void MultiUpdateGameInfo(int Index);
	UFUNCTION(Server, Reliable)
	void ServerUpdateRankInfo();
	UFUNCTION(NetMulticast, Reliable)
	void MultiUpdateRankInfo();

public:
	UFUNCTION(Server, Reliable)
	void ServerRollDice();
	UFUNCTION(NetMulticast, Reliable)
	void MultiRollDice();
	UFUNCTION(Server, Reliable)
	void ServerChooseItem();
	UFUNCTION(Server, Reliable)
	void ServerClickedGetStarButton();
	UFUNCTION(NetMulticast, Reliable)
	void MultiClickedGetStarButton();
	UFUNCTION(Server, Reliable)
	void ServerPressPassButton();
	UFUNCTION(NetMulticast, Reliable)
	void MultiServerPressPassButton();

	UFUNCTION(Server, Reliable)
	void ServerClickedItem1Button();
	UFUNCTION(NetMulticast, Reliable)
	void MultiClickedItem1Button();
	UFUNCTION(Server, Reliable)
	void ServerClickedItem2Button();
	UFUNCTION(NetMulticast, Reliable)
	void MultiClickedItem2Button();


	void DelayTime(float WantSeconds, TFunction<void()> InFunction);
public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

};



