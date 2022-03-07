// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
enum BlockType
{
	AIR,
	DIRT,
	STONE,
	NUMTYPES
};

class PROTO2_API Block
{
public:
	BlockType Type;

	bool ToUpdate = true;
	bool Active;

	enum BlockSide {
		BOTTOM = 0,
		LEFT,
		RIGHT,
		FRONT,
		BACK,
		TOP,
	};

	static void GenerateVertices(BlockSide side, FVector pos, int size, TArray<FVector>& vertices, TArray<int32>& indices, TArray<FVector>& normals);
	static TArray<FVector2D> GetTexCoordForType(BlockType type, BlockSide side);

private:
	static const float TEXTURE_SIZE;
	static TArray<FVector2D> GetTexCoords(int x, int y);
};