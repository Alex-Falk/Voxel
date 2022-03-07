// Fill out your copyright notice in the Description page of Project Settings.


#include "Block.h"

const float Block::TEXTURE_SIZE = 16.f;

void Block::GenerateVertices(BlockSide side, FVector pos, int size, TArray<FVector>& vertices, TArray<int32>& indices, TArray<FVector>& normals)
{
	int32 count = vertices.Num();
	TArray<FVector> toAppend;
	switch (side)
	{
	case Block::BOTTOM:	// Z = -.5
		toAppend = { FVector(-.5, -.5, -.5), FVector(.5, -.5, -.5), FVector(.5, .5, -.5), FVector(-.5, .5, -.5) };
		normals.Append({ FVector(0, 0, -1), FVector(0, 0, -1), FVector(0, 0, -1), FVector(0, 0, -1) });
		break;
	case Block::LEFT:	// x = -.5
		toAppend = {FVector(-.5, .5, -.5), FVector(-.5, -.5, -.5), FVector(-.5, -.5, .5), FVector(-.5, .5, .5)};
		normals.Append({ FVector(-1, 0, 0), FVector(-1, 0, 0), FVector(-1, 0, 0), FVector(-1, 0, 0) });
		break;
	case Block::RIGHT:	// x = .5
		toAppend = { FVector(.5, -.5, -.5) , FVector(.5, .5, -.5) , FVector(.5, .5, .5) , FVector(.5, -.5, .5) };
		normals.Append({ FVector(1, 0, 0), FVector(1, 0, 0), FVector(1, 0, 0), FVector(1, 0, 0) });
		break;
	case Block::FRONT:	// y = .5
		toAppend = { FVector(.5, .5, -.5), FVector(-.5, .5, -.5), FVector(-.5, .5, .5) , FVector(.5, .5, .5) };
		normals.Append({ FVector(0, 1, 0), FVector(0, 1, 0), FVector(0, 1, 0), FVector(0, 1, 0) });
		break;
	case Block::BACK:	// y = -.5
		toAppend = { FVector(-.5, -.5, -.5), FVector(.5, -.5, -.5) , FVector(.5, -.5, .5) , FVector(-.5, -.5, .5) };
		normals.Append({ FVector(0, -1, 0), FVector(0, -1, 0), FVector(0, -1, 0), FVector(0, -1, 0) });
		break;
	case Block::TOP:	// z = .5
		toAppend = { FVector(-.5, -.5, .5) , FVector(.5, -.5, .5) , FVector(.5, .5, .5) , FVector(-.5, .5, .5) };
		normals.Append({ FVector(0, 0, 1), FVector(0, 0, 1), FVector(0, 0, 1), FVector(0, 0, 1) });
		break;
	}

	for (FVector& vert : toAppend)
	{
		vert = size * (vert + pos);
	}

	vertices.Append(toAppend);

	indices.Append({ count, count + 2, count + 1, count, count + 3, count + 2 });
}

TArray<FVector2D> Block::GetTexCoordForType(BlockType type, BlockSide side)
{
	static const float w = 16.f;

	switch (type)
	{
	case AIR:
		break;
	case DIRT:
		if (side == TOP) 
		{
			return GetTexCoords(7, 13);
		}
		else
		{
			return GetTexCoords(12, 15);
		}
	case STONE:
		return GetTexCoords(14, 15);
	case NUMTYPES:
		break;
	default:
		break;
	}

	return { {},{},{},{} };
}

TArray<FVector2D> Block::GetTexCoords(int x, int y)
{
	return { { x / TEXTURE_SIZE, y / TEXTURE_SIZE}, { (x + 1) / TEXTURE_SIZE, y / TEXTURE_SIZE}, {(x + 1) / TEXTURE_SIZE, (y + 1) / TEXTURE_SIZE}, {x / TEXTURE_SIZE, (y + 1) / TEXTURE_SIZE}};
}
