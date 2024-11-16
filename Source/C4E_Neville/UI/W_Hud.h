#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_Hud.generated.h"

class UProgressBar;
class UTextBlock;

UENUM(BlueprintType)
enum class DynamicWidgetID : uint8 {
	CANDY_COUNTER = 0 UMETA(DisplayName = "CANDY_COUNTER"),
	PUMPKIN_COUNTER = 1  UMETA(DisplayName = "PUMPKIN_COUNTER"),
	TIMER_DISPLAY = 2     UMETA(DisplayName = "TIMER_DISPLAY"),
};

UCLASS()
class C4E_NEVILLE_API UW_Hud : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	
	void Setup(TArray<DynamicWidgetID> hide);
	
	TMap<DynamicWidgetID, TObjectPtr<UWidget>> _DynamicWidgets;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> HealthBar;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> CandyCounter;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> PumpkinCounter;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TimerDisplay;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> PlayerLivesDisplay;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> LevelNameDisplay;
};
