// Fill out your copyright notice in the Description page of Project Settings.

#include "GuardBehaviorComponent.h"

TArray<AActor*> UGuardBehaviorComponent::GetPatrolPoints() const {
	return PatrolPoints;
}
