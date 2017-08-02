// Viktor Gomeniuk : https://github.com/vgomeniuk

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "SetSuspiciousPoint.generated.h"

struct FBlackboardKeySelector;


UCLASS()
class SHOOTER_API USetSuspiciousPoint : public UBTService
{
	GENERATED_BODY()
	
private:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector LastChasePointKey;

	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector SuspiciousPointKey;

};
