// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemUI.h"
#include "PartyPlayer.h"
#include "PartyGameModeBase.h"

#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void UItemUI::NativeConstruct()
{
	Super::NativeConstruct();
	GM = Cast<APartyGameModeBase>(GetWorld()->GetAuthGameMode());
	CurrentPlayer = GM->TurnOrder[0];
	PlayerInventory=CurrentPlayer->Inventory;
	Index1Button->OnClicked.AddDynamic(this, &UItemUI::Select1Button);
	Index2Button->OnClicked.AddDynamic(this, &UItemUI::Select2Button);
	
	//A3D1 = NewObject<UImage>(this,Add3DiceImageFactory);


	switch (PlayerInventory[0])
	{
		case EItem::Add3Dice:
			{
				Add3DiceItem();
				Item1->SetText(FText::FromString(TEXT("Dice+3")));
				break;
			}
		case EItem::WarpToStar:
		{
			WarpToStarItem();
			Item1->SetText(FText::FromString(TEXT("WarpToStar")));
			break;
		}

		case EItem::SwitchCharacter:
		{
			Item1->SetText(FText::FromString(TEXT("SwitchSpace")));
			break;
		}
			case EItem::Nothing:
		{
			break;
		}

	}

	switch (PlayerInventory[1])
	{
		case EItem::Add3Dice:
		{
			Add3DiceItem();
			Item1->SetText(FText::FromString(TEXT("Dice+3")));
			break;
		}
		case EItem::WarpToStar:
		{
			Item1->SetText(FText::FromString(TEXT("WarpToStar")));
			WarpToStarItem();
			break;
		}

		case EItem::SwitchCharacter:
		{
			SwitchSpaceItem();
			Item1->SetText(FText::FromString(TEXT("SwitchSpace")));
			break;
		}
		case EItem::Nothing:
		{
			break;
		}

	}


}

void UItemUI::Add3DiceItem()//아이템을 먹었을때 ui띄우기
{
	
	//auto AddUi = CreateWidget(this, Add3DiceUIFactory);
	// grid에 자식으로 붙인다.
	//ItemGrid->AddChildToUniformGrid(AddUi, 0, ItemGrid->GetChildrenCount());
	//ButtonStaus[PlayerItemIndex] = EItem::Add3Dice;

}

void UItemUI::WarpToStarItem()
{
	
	//auto AddUi = CreateWidget(this, WarpToStarUIFactory);
	//ItemGrid->AddChildToUniformGrid(AddUi, 0, ItemGrid->GetChildrenCount());
	//ButtonStaus[PlayerItemIndex] = EItem::WarpToStar;
}

void UItemUI::SwitchSpaceItem()
{
	
	//auto AddUi = CreateWidget(this, SwitchSpaceUIFactory);
	//ItemGrid->AddChildToUniformGrid(AddUi, 0, ItemGrid->GetChildrenCount());
	//ButtonStaus[PlayerItemIndex] = EItem::SwitchCharacter;
}

void UItemUI::RemoveItemUi(int32 index)
{
	//ItemGrid->RemoveChildAt(index);
}

void UItemUI::Select1Button()//각 버튼에 대한 상호작용 
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Select1"));
	SwitchItem(PlayerInventory[0]);
	//RemoveItemUi(0);
	CurrentPlayer->Inventory[0] = EItem::Nothing;
	
}

void UItemUI::Select2Button()
{
	SwitchItem(PlayerInventory[1]);
	//RemoveItemUi(1);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Select2"));
	CurrentPlayer->Inventory[1] = EItem::Nothing;
}

void UItemUI::SwitchItem(EItem SelectedItem)//아이템사용효과를 넣으면 된다
{
	switch (SelectedItem)
	{
		case EItem::Add3Dice:
			{
				
				break;
			}
		case EItem::WarpToStar:
		{

			break;
		}
		case EItem::SwitchCharacter:
		{

			break;
		}
	}
}
