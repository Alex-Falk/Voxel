// Fill out your copyright notice in the Description page of Project Settings.


#include "HexTile.h"

#include "Materials/Material.h"

const TArray<FVector> AHexTile::FHexagonShape::Vertices = {
		FVector(0, 0, 0),
		FVector(FMath::Cos(FMath::DegreesToRadians(30)), .5, 0),
		FVector(FMath::Cos(FMath::DegreesToRadians(30)), -.5, 0),
		FVector(0, -1, 0),
		FVector(-FMath::Cos(FMath::DegreesToRadians(30)), -.5, 0),
		FVector(-FMath::Cos(FMath::DegreesToRadians(30)), .5, 0),
		FVector(0, 1, 0)
};

const TArray<int32> AHexTile::FHexagonShape::Indeces = { 0, 1, 2, 0, 2, 3, 0, 3, 4, 0, 4, 5, 0, 5, 6, 0, 6, 1 };


// Sets default values
AHexTile::AHexTile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UProceduralMeshComponent>("Mesh");
	RootComponent = MeshComponent;
	Material = UMaterial::GetDefaultMaterial(MD_Surface);
}



void AHexTile::RebuildMesh()
{
	TArray<FLinearColor> Colors;
	TArray<FVector> Normals;
	TArray<FVector2D> UV0;
	TArray<FProcMeshTangent> Tangents;
	for (int c = 0; c < 7; ++c)
	{
		Normals.Add(FVector(0, 0, 1));
		UV0.Add(FVector2D(0, 10));
		Tangents.Add(FProcMeshTangent(0, 1, 0));
		Colors.Add(Color);
	}

	MeshComponent->CreateMeshSection_LinearColor(0, FHexagonShape::Vertices, FHexagonShape::Indeces, Normals, UV0, Colors, Tangents, false);
}

void AHexTile::SetMaterial()
{
	MeshComponent->SetMaterial(0, Material);
}

void AHexTile::BeginPlay()
{
	Super::BeginPlay();
	RebuildMesh();
}

void AHexTile::PostLoad()
{
	Super::PostLoad();
	RebuildMesh();
}

void AHexTile::PostActorCreated()
{
	Super::PostActorCreated();
	RebuildMesh();
}

void AHexTile::PostEditChangeProperty(FPropertyChangedEvent& event)
{
	Super::PostEditChangeProperty(event);
	
	
	FName PropertyName = (event.Property != NULL) ? event.Property->GetFName() : NAME_None;
	if (PropertyName == GET_MEMBER_NAME_CHECKED(AHexTile, Material))
	{
		SetMaterial();
	}
	else
	{
		RebuildMesh();
	}
}
