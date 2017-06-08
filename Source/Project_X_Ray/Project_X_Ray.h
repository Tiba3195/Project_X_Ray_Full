// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "DonAINavigation/Public/IDonAINavigation.h"
#include "Components/WidgetComponent.h"
#include "PaperSpriteComponent.h"

#define COLLISION_PROJECTILE	ECC_GameTraceChannel1
/* Stencil index mapping to PP_OutlineColored */
#define STENCIL_FRIENDLY_OUTLINE 252;
#define STENCIL_NEUTRAL_OUTLINE 253;
#define STENCIL_ENEMY_OUTLINE 254;
#define STENCIL_ITEMHIGHLIGHT 255;