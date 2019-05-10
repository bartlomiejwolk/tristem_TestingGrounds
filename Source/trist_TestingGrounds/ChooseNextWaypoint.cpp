// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNextWaypoint.h"
#include "BehaviorTree/BlackboardComponent.h"

// TODO remove
#include "PatrollingGuard.h"
#include "Runtime/AIModule/Classes/AIController.h"

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();

	// get patrol points from TPP character
	AAIController* AIController = Cast<AAIController>(OwnerComp.GetOwner());
	check(AIController);
	APatrollingGuard* PatrollingGuard = Cast<APatrollingGuard>(AIController->GetPawn());
	check(PatrollingGuard);
	PatrolPoints = PatrollingGuard->PatrolPoints;

	// read Blackboard waypoint index value
	int32 Index = BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName);

	// set Blackboard Actor ref.
	BlackboardComp->SetValueAsObject(WaypointRef.SelectedKeyName, PatrolPoints[Index]);

	// cycle Blackboard waypoint index
	int32 newIndex = (Index + 1) % PatrolPoints.Num();
	BlackboardComp->SetValueAsInt(IndexKey.SelectedKeyName, newIndex);

	UE_LOG(LogTemp, Log, TEXT("Index: %i"), Index)

	return EBTNodeResult::Succeeded;
}