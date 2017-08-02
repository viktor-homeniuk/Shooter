// Viktor Gomeniuk : https://github.com/vgomeniuk

#include "SetSuspiciousPoint.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"


void USetSuspiciousPoint::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) {
	// Set Suspect point for NPC to check
	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	UObject* LastChasePoint = Blackboard->GetValueAsObject(LastChasePointKey.SelectedKeyName);
	if (LastChasePoint) { 
		Blackboard->SetValueAsVector(SuspiciousPointKey.SelectedKeyName, Cast<AActor>(LastChasePoint)->GetActorLocation());
	}
	return;
}
