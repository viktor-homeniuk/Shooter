// Viktor Gomeniuk : https://github.com/vgomeniuk

#include "IsWithinRange.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

bool UIsWithinRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const {
	APawn* Pawn = OwnerComp.GetAIOwner()->GetPawn();
	AActor* Target = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TargetKey.SelectedKeyName));
	FVector Distance = Target->GetActorLocation() - Pawn->GetActorLocation();
	return Distance.Size() <= Range;
}

