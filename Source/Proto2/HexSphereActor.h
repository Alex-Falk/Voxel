// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HexTile.h"
#include "HexSphereActor.generated.h"


UCLASS()
class PROTO2_API AHexSphereActor : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	AHexSphereActor();

	void PostActorCreated() override;
	void PostLoad() override;

	void BeginPlay() override;

#if WITH_EDITOR
	void PostEditChangeProperty(FPropertyChangedEvent& event) override;
#endif


protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* SceneComponent;

	UPROPERTY(EditAnywhere)
	int XSize = 2;

	UPROPERTY(EditAnywhere)
	int YSize = 2;
	

	void CreateHexGrid(int x, int y);

	TArray<AHexTile*> Hexagons;
};
