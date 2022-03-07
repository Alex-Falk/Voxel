// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMap.h"

#include "DrawDebugHelpers.h"
#include "Chunk.h"

// Sets default values
AGameMap::AGameMap()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	m_mesh = CreateDefaultSubobject<UProceduralMeshComponent>("Mesh");
	RootComponent = m_mesh;
	Material = UMaterial::GetDefaultMaterial(MD_Surface);

	m_chunks = new Chunk * [NUM_CHUNKS];
	for (int i = 0; i < NUM_CHUNKS; ++i)
	{
		m_chunks[i] = new Chunk[NUM_CHUNKS];
		for (int j = 0; j < NUM_CHUNKS; ++j)
		{
			m_chunks[i][j].SetPosition(FVector(i * Chunk::CHUNK_SIZE,j * Chunk::CHUNK_SIZE,0));
			m_chunks[i][j].GenerateChunk();
			m_chunks[i][j].BuildMesh(m_mesh, (i * NUM_CHUNKS) + j);
		}
		
	}
}

AGameMap::~AGameMap()
{
	delete[] m_chunks;
}

// Called when the game starts or when spawned
void AGameMap::BeginPlay()
{
	Super::BeginPlay();
}

void AGameMap::Reload()
{
	if (m_mesh)
		m_mesh->ClearAllMeshSections();

	delete[] m_chunks;
	m_chunks = new Chunk * [NUM_CHUNKS];
	for (int i = 0; i < NUM_CHUNKS; ++i)
	{
		m_chunks[i] = new Chunk[NUM_CHUNKS];
		for (int j = 0; j < NUM_CHUNKS; ++j)
		{
			m_chunks[i][j].SetPosition(FVector(i * Chunk::CHUNK_SIZE, j * Chunk::CHUNK_SIZE, 0));
			m_chunks[i][j].GenerateChunk();
			m_chunks[i][j].BuildMesh(m_mesh, (i * NUM_CHUNKS) + j);
			m_mesh->SetMaterial((i * NUM_CHUNKS) + j, Material);
		}
	}

	
}

// Called every frame
void AGameMap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

