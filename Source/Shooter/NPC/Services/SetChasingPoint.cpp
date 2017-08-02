// Viktor Gomeniuk : https://github.com/vgomeniuk

#include "SetChasingPoint.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"


void USetChasingPoint::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) {
	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	UObject* ChasePoint = Blackboard->GetValueAsObject(ChasePointKey.SelectedKeyName);
	if (ChasePoint) { 
		OwnerComp.GetAIOwner()->SetFocus(Cast<AActor>(ChasePoint));
	}
	return;
}
