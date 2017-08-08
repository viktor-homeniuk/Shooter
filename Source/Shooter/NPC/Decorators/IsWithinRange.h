// Viktor Gomeniuk : https://github.com/vgomeniuk

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "IsWithinRange.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTER_API UIsWithinRange : public UBTDecorator
{
	GENERATED_BODY()
	
private:
	bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const;

private:
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	struct FBlackboardKeySelector TargetKey;

	UPROPERTY(EditAnywhere, Category = "Blackboard")
	float Range = 0.0f;

};
