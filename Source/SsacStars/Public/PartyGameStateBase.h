// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "PartyGameStateBase.generated.h"

class ALevelSequenceActor;
/**
 *
 */
UCLASS()
class SSACSTARS_API APartyGameStateBase : public AGameStateBase
{
	GENERATED_BODY()
	APartyGameStateBase();
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

	UPROPERTY( EditDefaultsOnly )
	class UPartyGameEnd* EndGameUi;
	UPROPERTY( EditDefaultsOnly )
	TSubclassOf<class UPartyGameEnd> EndGameUiFactory;

	UPROPERTY( EditDefaultsOnly )
	TSubclassOf<class UThrowDiceCharacterUi> ThrowDiceUiFactory;
	UPROPERTY(Replicated)
	class UThrowDiceCharacterUi* ThrowDiceUi;


	UPROPERTY( EditDefaultsOnly )
	class ADice* Dice;
	UPROPERTY(EditDefaultsOnly)
	class APlayerController* Controller;
	/*
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	class ALevelSequenceActor* LevelSequenceActor;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class ULevelSequence* LevelSequence;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class ULevelSequencePlayer* LevelSequencePlayer;
	*/
	UPROPERTY(VisibleAnywhere, Replicated)
	class ULevelSequencePlayer* SequencePlayer;
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
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<int>PlayerScores;
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Replicated)
	int CurrentPlayerIndex;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Replicated)
	int PlayerCount = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Replicated)
	int Round = 1;
public:
	UPROPERTY( EditAnywhere )
	class USoundBase* TrapSound;
	UPROPERTY( EditAnywhere )
	class USoundBase* GetStarSound;
	UPROPERTY( EditAnywhere )
	class USoundBase* ResultSound;
	UPROPERTY( EditAnywhere )
	class USoundBase* WarpSound;

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
	UFUNCTION( Server , Reliable )
	void ServerThrowDiceUi();
	UFUNCTION( NetMulticast , Reliable )
	void MultiThrowDiceUi();
	UFUNCTION(Server, Reliable)
	void ServerViewStatusUi();
	UFUNCTION(NetMulticast, Reliable)
	void MultiViewStatusUi();
	UFUNCTION( Server , Reliable )
	void ServerViewEndGameUi();
	UFUNCTION( NetMulticast , Reliable )
	void MultiViewEndGameUi();
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
	UFUNCTION( Server , Reliable )
	void ServerRemoveThrowDiceUi();
	UFUNCTION( NetMulticast , Reliable )
	void MultiRemoveThrowDiceUi();
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
	UFUNCTION( Server , Reliable )
	void ServerOverlap();

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
	UFUNCTION(Server, Reliable)
	void ServerUpdateEndInfo(int Index);
	UFUNCTION(NetMulticast, Reliable)
	void MultiUpdateEndInfo(int Index);
public:
	UFUNCTION(Server, Reliable)
	void ServerRollDice();
	UFUNCTION(NetMulticast, Reliable)
	void MultiRollDice();
	UFUNCTION( Server , Reliable )
	void ServerDiceOverlap();
	UFUNCTION( NetMulticast , Reliable )
	void MultiDiceOverlap();
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
public:
	UFUNCTION(Server, Reliable)
	void ServerOpenMinigame();
	UFUNCTION(NetMulticast, Reliable)
	void MultiOpenMinigame();
	UFUNCTION(Client, Reliable)
	void ClientTriggerSequence();
	UFUNCTION(Server, Reliable)
	void ServerTriggerSequence();
	UFUNCTION(NetMulticast, Reliable)
	void MultiTriggerSequence();
	UFUNCTION(Server, Reliable)
	void ServerSequenceEnded();
	UFUNCTION(NetMulticast, Reliable)
	void MultiSequenceEnded();
public:
	UFUNCTION( Server , Reliable )
	void ServerTurnStartUi();
	UFUNCTION( NetMulticast , Reliable )
	void MultiTurnStartUi();
	UFUNCTION( Server , Reliable )
	void ServerSoundVoice( USoundBase* MySound );
	UFUNCTION( NetMulticast , Reliable )
	void MultiSoundVoice( USoundBase* MySound );

	void PlaySound( USoundBase* MySound );
	void DelayTime(float WantSeconds, TFunction<void()> InFunction);
public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

};



