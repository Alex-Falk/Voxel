// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProceduralMeshComponent.h"
#include "HexTile.generated.h"

UCLASS()
class PROTO2_API AHexTile : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	AHexTile();

	class FHexagonShape
	{
	public:

		static const TArray<FVector> Vertices;
		static const TArray<int32> Indeces;
	};

protected:


	void RebuildMesh();
	void SetMaterial();

	void BeginPlay() override;
	void PostLoad() override;
	void PostActorCreated() override;

#if WITH_EDITOR
	void PostEditChangeProperty(FPropertyChangedEvent& event) override;
#endif


	FLinearColor Color = FLinearColor::MakeRandomColor();
	UProceduralMeshComponent* MeshComponent;

	UPROPERTY(EditAnywhere)
		UMaterialInterface* Material;


};
