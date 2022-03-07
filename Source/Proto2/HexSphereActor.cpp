// Fill out your copyright notice in the Description page of Project Settings.


#include "HexSphereActor.h"

#include "Math/UnrealMathUtility.h"

// Sets default values for this component's properties
AHexSphereActor::AHexSphereActor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	// ...
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SetRootComponent(SceneComponent);
}

void AHexSphereActor::PostActorCreated()
{
	Super::PostActorCreated();
	CreateHexGrid(XSize, YSize);
	SetActorScale3D({ 30, 30, 30 });
}

// This is called when actor is already in level and map is opened
void AHexSphereActor::PostLoad()
{
	Super::PostLoad();
	CreateHexGrid(XSize, YSize);
}

void AHexSphereActor::BeginPlay()
{
	Super::BeginPlay();
	CreateHexGrid(XSize, YSize);
}

#if WITH_EDITOR
void AHexSphereActor::PostEditChangeProperty(FPropertyChangedEvent& event)
{

}
#endif

void AHexSphereActor::CreateHexGrid(int x, int y)
{
	for(auto hex : Hexagons)
	{
		GetWorld()->RemoveActor(hex, true);
	}

	const float cos30 = FMath::Cos(FMath::DegreesToRadians(30));

	for(int i = - x / 2; i < x / 2; ++i)
	{
		for (int j = -y / 2; j < y / 2; ++j)
		{
			const float additionalXOffset = j % 2 == 0 ? 0.f : 1.5f;

			auto test = FActorSpawnParameters();
			test.Owner = this;

			AHexTile* tile = GetWorld()->SpawnActor<AHexTile>(FVector(cos30 * j, 3 * i + additionalXOffset, 0.f), FRotator::ZeroRotator, test);
			tile->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);

			Hexagons.Add(tile);
		}
	}
}

