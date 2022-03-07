// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Chunk.h"
#include "GameMap.generated.h"

class World;

UCLASS()
class PROTO2_API AGameMap : public AActor
{
	GENERATED_BODY()

	friend class Chunk;
	
public:	
	// Sets default values for this actor's properties
	AGameMap();
	~AGameMap();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(CallInEditor, Category = "Test")
	void Reload();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	Chunk** m_chunks;
	UProceduralMeshComponent* m_mesh;

	UPROPERTY(EditAnywhere)
	UMaterialInterface* Material;

	const static int NUM_CHUNKS = 4;
};
