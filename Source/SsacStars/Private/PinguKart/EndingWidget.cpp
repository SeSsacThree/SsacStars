// Fill out your copyright notice in the Description page of Project Settings.


#include "EndingWidget.h"
#include "KartGameState.h"
#include "Components/TextBlock.h"
#include "GameFramework/PlayerState.h"

void UEndingWidget::NativeConstruct()
{
	Super::NativeConstruct();

	auto playerList = GetWorld()->GetGameState<AKartGameState>()->PlayerArray;
	FString txt;

	playerList.Sort( []( const APlayerState& A , const APlayerState& B ) {
		return A.GetScore() > B.GetScore(); // 내림차순 정렬
} );

	// 플레이어 목록에서 상위 4명의 정보를 가져와 각각의 변수에 저장
	const APlayerState* FirstPlayer = nullptr;
	const APlayerState* SecondPlayer = nullptr;
	const APlayerState* ThirdPlayer = nullptr;
	const APlayerState* FourthPlayer = nullptr;

	if (playerList.Num() > 0)
		FirstPlayer = playerList[0];
	if (playerList.Num() > 1)
		SecondPlayer = playerList[1];
	if (playerList.Num() > 2)
		ThirdPlayer = playerList[2];
	if (playerList.Num() > 3)
		FourthPlayer = playerList[3];


	// 상위 4명의 정보를 각각의 랭킹에 출력
	if (FirstPlayer != nullptr)
		RankingFirst->SetText( FText::FromString( FString::Printf( TEXT( "%s   %d점" ) , *FirstPlayer->GetPlayerName() , FMath::RoundToInt( FirstPlayer->GetScore() ) ) ) );
	if (SecondPlayer != nullptr)
		RankingSecond->SetText( FText::FromString( FString::Printf( TEXT( "%s   %d점" ) , *SecondPlayer->GetPlayerName() , FMath::RoundToInt( SecondPlayer->GetScore() ) ) ) );
	if (ThirdPlayer != nullptr)
		RankingThird->SetText( FText::FromString( FString::Printf( TEXT( "%s   %d점" ) , *ThirdPlayer->GetPlayerName() , FMath::RoundToInt( ThirdPlayer->GetScore() ) ) ) );
	if (FourthPlayer != nullptr)
		RankingFourth->SetText( FText::FromString( FString::Printf( TEXT( "%s   %d점" ) , *FourthPlayer->GetPlayerName() , FMath::RoundToInt( FourthPlayer->GetScore() ) ) ) );
}
