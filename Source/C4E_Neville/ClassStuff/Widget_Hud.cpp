#include "Widget_Hud.h"

void UWidget_Hud::NativeConstruct()
{
	Super::NativeConstruct();

	if(HealthBar) HealthBar->SetPercent(0.0f);
	if(ScoreText) ScoreText->SetText(FText::FromString("Score: ERROR! :/"));
}

void UWidget_Hud::UpdateHealth(float newHealthRatio)
{
	if (HealthBar) HealthBar->SetPercent(newHealthRatio);
}

void UWidget_Hud::UpdateScore(int newScore)
{
	if(ScoreText)
	{
		ScoreText->SetText(
			FText::FromString(
				FString::Printf(TEXT("Score: %d"), newScore)
			)
		);
	}
}
