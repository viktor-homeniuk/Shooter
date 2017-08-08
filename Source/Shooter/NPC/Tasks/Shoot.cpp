// Viktor Gomeniuk : https://github.com/vgomeniuk

#include "Shoot.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../../Actors/ShooterCharacter.h"

EBTNodeResult::Type UShoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
	UObject* Target = OwnerComp.GetBlackboardComponent()->GetValueAsObject(TargetKey.SelectedKeyName);
	OwnerComp.GetAIOwner()->SetFocus(Cast<AActor>(Target), EAIFocusPriority::Gameplay);
	AShooterCharacter* Character = Cast<AShooterCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	Character->ToggleAlarm(true);
	Character->Fire();
	return EBTNodeResult::Succeeded;
}
