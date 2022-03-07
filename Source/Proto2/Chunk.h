// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProceduralMeshComponent.h"
/**
 * 
 */

class Block;

class PROTO2_API Chunk
{
	friend class GameMap;

public:
	const static int HEIGHT_MAX = 64;
	const static int CHUNK_SIZE = 32;
	const static int BLOCK_SIZE = 10;

	Chunk();
	~Chunk();

	void GenerateChunk();
	void BuildMesh(UProceduralMeshComponent* mesh, int chunkIdx);
	void SetPosition(FVector pos) { m_chunkPos = pos; }

private:
	Block*** m_blocks;
	FVector m_chunkPos;

	int CalculateElevation(FVector2D pos);
};

