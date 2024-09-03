// Fill out your copyright notice in the Description page of Project Settings.

/*
 *	Author: Lee Dong Geun
 */

#include "HitTool.h"

#include "Components/BoxComponent.h"

// Sets default values
AHitTool::AHitTool()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HitCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Hit Collision"));
	SetRootComponent(HitCollision);
	HitCollision -> SetBoxExtent(FVector(50.0f, 50.0f, 50.0f));
	HitCollision -> SetCollisionEnabled(ECollisionEnabled::NoCollision);

	HitMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Hit Mesh"));
	HitMesh -> SetupAttachment(RootComponent);
	HitMesh -> SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called when the game starts or when spawned
void AHitTool::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHitTool::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHitTool::ActivationCollision(bool bIsActivated)
{
	bIsActivated ? HitCollision -> SetCollisionEnabled(ECollisionEnabled::QueryOnly) : HitCollision -> SetCollisionEnabled(ECollisionEnabled::NoCollision);
}