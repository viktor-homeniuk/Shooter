// Viktor Gomeniuk : https://github.com/vgomeniuk

#include "OnSuspiciousPointChecked.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UOnSuspiciousPointChecked::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	Blackboard->ClearValue(SuspiciousPointKey.SelectedKeyName);
	return EBTNodeResult::Succeeded;
}

