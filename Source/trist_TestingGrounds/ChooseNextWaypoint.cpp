// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNextWaypoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

// TODO remove
#include "PatrollingGuard.h"

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();

	// get patrol points from TPP character
	AAIController* AIController = OwnerComp.GetAIOwner();
	check(AIController);
	APatrollingGuard* PatrollingGuard = Cast<APatrollingGuard>(AIController->GetPawn());
	check(PatrollingGuard);
	// TODO make sure there's at least one element
	auto PatrolPoints = PatrollingGuard->GetPatrolPoints();

	// read Blackboard waypoint index value
	int32 Index = BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName);

	// set Blackboard Actor ref.
	BlackboardComp->SetValueAsObject(WaypointRef.SelectedKeyName, (*PatrolPoints)[Index]);

	// cycle Blackboard waypoint index
	int32 newIndex = (Index + 1) % PatrolPoints->Num();
	BlackboardComp->SetValueAsInt(IndexKey.SelectedKeyName, newIndex);

	UE_LOG(LogTemp, Log, TEXT("Index: %i"), Index)

	return EBTNodeResult::Succeeded;
}