// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNextWaypoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "PatrolRoute.h"

// TODO remove
#include "PatrollingGuard.h"

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();

	// get patrol points from `PatrolRoute` component
	TArray<AActor*> PatrolPoints;
	{
		AAIController* AIController = OwnerComp.GetAIOwner();
		APawn* Pawn = AIController->GetPawn();
		UPatrolRoute* PatrolRoute = Pawn->FindComponentByClass<UPatrolRoute>();
		if (!ensure(PatrolRoute))
		{
			return EBTNodeResult::Failed;
		}
		PatrolPoints = PatrolRoute->GetPatrolPoints();
		if (PatrolPoints.Num() == 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("Patrol points not defined in `UPatrolRoute` component!"))
				return EBTNodeResult::Failed;
		}
	}

	// read Blackboard waypoint index value
	int32 Index = BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName);

	// set Blackboard Actor ref.
	BlackboardComp->SetValueAsObject(WaypointRef.SelectedKeyName, (PatrolPoints)[Index]);

	// cycle Blackboard waypoint index
	int32 newIndex = (Index + 1) % PatrolPoints.Num();
	BlackboardComp->SetValueAsInt(IndexKey.SelectedKeyName, newIndex);

	return EBTNodeResult::Succeeded;
}