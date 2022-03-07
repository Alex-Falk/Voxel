// Fill out your copyright notice in the Description page of Project Settings.


#include "Chunk.h"
#include "GameMap.h"
#include "Block.h"

Chunk::Chunk()
{
	m_blocks = new Block** [CHUNK_SIZE];
	for (int i = 0; i < CHUNK_SIZE; ++i) 
	{
		m_blocks[i] = new Block * [CHUNK_SIZE];
		for (int j = 0; j < CHUNK_SIZE; ++j)
		{
			m_blocks[i][j] = new Block[HEIGHT_MAX];
		}
	}
}

Chunk::~Chunk()
{
	for (int i = 0; i < CHUNK_SIZE; ++i)
	{
		for (int j = 0; j < CHUNK_SIZE; ++j)
		{
			delete[] m_blocks[i][j];
		}
		delete[] m_blocks[i];
	}
	delete[] m_blocks;
}

void Chunk::GenerateChunk()
{
	for (int x = 0; x < CHUNK_SIZE; ++x)
	{
		for (int y = 0; y < CHUNK_SIZE; ++y)
		{
			int height = CalculateElevation({ m_chunkPos.X + x, m_chunkPos.Y + y });

			for (int z = 0; z < HEIGHT_MAX; ++z)
			{
				if (z > height)
				{
					m_blocks[x][y][z].Type = AIR;
				}
				else if (z == height)
				{
					m_blocks[x][y][z].Type = DIRT;
				}
				else
				{
					m_blocks[x][y][z].Type = STONE;
				}
			}
		}
	}
}

void Chunk::BuildMesh(UProceduralMeshComponent* mesh, int chunkIdx)
{
	TArray<FVector> Vertices;
	TArray<int32> Indices;
	TArray<FLinearColor> Colors;
	TArray<FVector> Normals;
	TArray<FVector2D> UV0;
	TArray<FProcMeshTangent> Tangents;

	for (int x = 0; x < CHUNK_SIZE; ++x)
	{
		for (int y = 0; y < CHUNK_SIZE; ++y)
		{
			for (int z = 0; z < HEIGHT_MAX; ++z) 
			{
				Block& block = m_blocks[x][y][z];
				if (!block.ToUpdate)
					continue;

				if (block.Type == BlockType::AIR)
					continue;

				// check all directions if air block
				if (x < CHUNK_SIZE - 1 && m_blocks[x + 1][y][z].Type == BlockType::AIR)
				{
					Block::GenerateVertices(Block::RIGHT, m_chunkPos + FVector(x,y,z), BLOCK_SIZE, Vertices, Indices, Normals);
					UV0.Append(Block::GetTexCoordForType(block.Type, Block::RIGHT));
				}
				else if (x == CHUNK_SIZE - 1)
				{
					int nextHeight = CalculateElevation({ m_chunkPos.X + x + 1, m_chunkPos.Y + y });
					if (nextHeight < z)
					{
						Block::GenerateVertices(Block::RIGHT, m_chunkPos + FVector(x, y, z), BLOCK_SIZE, Vertices, Indices, Normals);
						UV0.Append(Block::GetTexCoordForType(block.Type, Block::RIGHT));
					}
				}
				
				if (x > 0 && m_blocks[x - 1][y][z].Type == BlockType::AIR)
				{
					Block::GenerateVertices(Block::LEFT, m_chunkPos + FVector(x, y, z), BLOCK_SIZE, Vertices, Indices, Normals);
					UV0.Append(Block::GetTexCoordForType(block.Type, Block::LEFT));
				}
				else if (x == 0)
				{
					int nextHeight = CalculateElevation({ m_chunkPos.X + x - 1, m_chunkPos.Y + y });
					if (nextHeight < z)
					{
						Block::GenerateVertices(Block::LEFT, m_chunkPos + FVector(x, y, z), BLOCK_SIZE, Vertices, Indices, Normals);
						UV0.Append(Block::GetTexCoordForType(block.Type, Block::LEFT));
					}
				}
				
				if (y < CHUNK_SIZE - 1 && m_blocks[x][y + 1][z].Type == BlockType::AIR)
				{
					Block::GenerateVertices(Block::FRONT, m_chunkPos + FVector(x, y, z), BLOCK_SIZE, Vertices, Indices, Normals);
					UV0.Append(Block::GetTexCoordForType(block.Type, Block::FRONT));
				}
				else if (y == CHUNK_SIZE - 1)
				{
					int nextHeight = CalculateElevation({ m_chunkPos.X + x, m_chunkPos.Y + y + 1});
					if (nextHeight < z)
					{
						Block::GenerateVertices(Block::FRONT, m_chunkPos + FVector(x, y, z), BLOCK_SIZE, Vertices, Indices, Normals);
						UV0.Append(Block::GetTexCoordForType(block.Type, Block::FRONT));
					}
				}

				if (y > 0 && m_blocks[x][y - 1][z].Type == BlockType::AIR)
				{
					Block::GenerateVertices(Block::BACK, m_chunkPos + FVector(x, y, z), BLOCK_SIZE, Vertices, Indices, Normals);
					UV0.Append(Block::GetTexCoordForType(block.Type, Block::BACK));
				}
				else if (y == 0)
				{
					int nextHeight = CalculateElevation({ m_chunkPos.X + x, m_chunkPos.Y + y - 1 });
					if (nextHeight < z)
					{
						Block::GenerateVertices(Block::BACK, m_chunkPos + FVector(x, y, z), BLOCK_SIZE, Vertices, Indices, Normals);
						UV0.Append(Block::GetTexCoordForType(block.Type, Block::BACK));
					}
				}

				if (z < HEIGHT_MAX - 1 && m_blocks[x][y][z + 1].Type == BlockType::AIR)
				{
					Block::GenerateVertices(Block::TOP, m_chunkPos + FVector(x, y, z), BLOCK_SIZE, Vertices, Indices, Normals);
					UV0.Append(Block::GetTexCoordForType(block.Type, Block::TOP));
				}

				if (z > 0 && m_blocks[x][y][z - 1].Type == BlockType::AIR)
				{
					Block::GenerateVertices(Block::BOTTOM, m_chunkPos + FVector(x, y, z), BLOCK_SIZE, Vertices, Indices, Normals);
					UV0.Append(Block::GetTexCoordForType(block.Type, Block::BOTTOM));
				}
			}
		}
	}

	for (int i = 0; i < Vertices.Num(); ++i)
	{
		Tangents.Add(FProcMeshTangent(0, 1, 0));
	}

	mesh->CreateMeshSection_LinearColor(chunkIdx, Vertices, Indices, Normals, UV0, Colors, Tangents, true);
}

int Chunk::CalculateElevation(FVector2D pos)
{
	pos /= CHUNK_SIZE * AGameMap::NUM_CHUNKS;
	auto height = (FMath::PerlinNoise2D(pos) + 0.5 * FMath::PerlinNoise2D(2 * pos) + 0.25 * FMath::PerlinNoise2D(4 * pos)) / (1.75);
	//height = FMath::Pow(height, 4.54);
	return ((height + 1.f) / 2.f) * HEIGHT_MAX;
}

