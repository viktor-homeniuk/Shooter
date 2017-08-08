// Viktor Gomeniuk : https://github.com/vgomeniuk

#include "Shoot.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../../Actors/ShooterCharacter.h"

EBTNodeResult::Type UShoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
	UObject* Target = OwnerComp.GetBlackboardComponent()->GetValueAsObject(TargetKey.SelectedKeyName);
	OwnerComp.GetAIOwner()->SetFocus(Cast<AActor>(Target), EAIFocusPriority::Gameplay);
	Cast<AShooterCharacter>(OwnerComp.GetAIOwner()->GetPawn())->ToggleAlarm(true);
	return EBTNodeResult::Succeeded;
}

//EBTNodeResult::Type UShoot::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
//	UE_LOG(LogTemp, Warning, TEXT("Abort"));
//
//	OwnerComp.GetAIOwner()->ClearFocus(EAIFocusPriority::Gameplay);
//	OwnerComp.GetBlackboardComponent()->ClearValue(TargetKey.SelectedKeyName);
//	Cast<AShooterCharacter>(OwnerComp.GetAIOwner()->GetPawn())->ToggleAlarm(false);
//	return EBTNodeResult::Aborted;
//}
