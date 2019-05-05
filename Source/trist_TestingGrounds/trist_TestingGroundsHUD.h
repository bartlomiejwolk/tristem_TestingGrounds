// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once 
#include "GameFramework/HUD.h"
#include "trist_TestingGroundsHUD.generated.h"

UCLASS()
class Atrist_TestingGroundsHUD : public AHUD
{
	GENERATED_BODY()

public:
	Atrist_TestingGroundsHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

};

