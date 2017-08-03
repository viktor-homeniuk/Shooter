// Fill out your copyright notice in the Description page of Project Settings.

#include "GetNextRoutePoint.h"
#include "AIController.h"
#include "../GuardBehaviorComponent.h"
#include "BehaviorTree/BlackboardComponent.h"


EBTNodeResult::Type UGetNextRoutePoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
	// Get patrol Guard Component
	APawn* Guard = OwnerComp.GetAIOwner()->GetPawn();
	UGuardBehaviorComponent* GuardComponent = Guard->FindComponentByClass<UGuardBehaviorComponent>();
	if (!ensure(GuardComponent)) { 
		UE_LOG(LogTemp, Warning, TEXT("%s misses GuardBehaviorComponent"), *Guard->GetName());
		return EBTNodeResult::Failed;
	}

	// Get Patrol Points
	TArray<AActor*> PatrolPoints = GuardComponent->GetPatrolPoints();
	if (PatrolPoints.Num() == 0) {
		UE_LOG(LogTemp, Warning, TEXT("%s misses points to patrol"), *Guard->GetName());
		return EBTNodeResult::Aborted;
	}

	// Get Blackboard Data
	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	int32 Index = Blackboard->GetValueAsInt(TargetPointIndexKey.SelectedKeyName);

	// Set TargetPoint and increment TargetPointIndex
	Blackboard->SetValueAsObject(TargetPointKey.SelectedKeyName, PatrolPoints[Index]);
	Blackboard->SetValueAsInt(TargetPointIndexKey.SelectedKeyName, (Index + 1) % PatrolPoints.Num());

	return EBTNodeResult::Succeeded;
}


