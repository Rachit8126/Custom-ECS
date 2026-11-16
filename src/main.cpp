#include <cassert>
#include <iostream>
#include <memory>

#include "EntityManager.hpp"

int main()
{
	std::cout << "Test Started" << "\n";

	std::unique_ptr<EntityManager> entityManager = std::make_unique<EntityManager>();

	EntityId entity = entityManager->Create();

	// Check if the handle created starts from 0
	assert(entity == Entity::Create(0, 0));

	// Check if the handle is destroyed correctly
	assert(entityManager->IsAlive(entity));
	entityManager->Destroy(entity);
	assert(!entityManager->IsAlive(entity));

	// Check if the old slot is used for new handles with incremented generation
	EntityId entity2 = entityManager->Create();

	assert(entity2 == Entity::Create(0, 1));
	assert(!entityManager->IsAlive(entity));
	assert(entityManager->IsAlive(entity2));

	entityManager->Destroy(entity2);

	// Check if the generation mask correctly wraps up the generation to 0 when it goes over 4095
	for (size_t i = 0; i < 5000; i++)
	{
		EntityId tempEntity = entityManager->Create();

		assert(entityManager->IsAlive(tempEntity));

		entityManager->Destroy(tempEntity);

		assert(!entityManager->IsAlive(tempEntity));
	}

	// Check double destroy handle
	EntityId staleEntity = entityManager->Create();

	assert(entityManager->IsAlive(staleEntity));

	entityManager->Destroy(staleEntity);
	entityManager->Destroy(staleEntity);

	assert(!entityManager->IsAlive(staleEntity));

	EntityId testEntity1 = entityManager->Create();
	EntityId testEntity2 = entityManager->Create();

	assert(testEntity1 != testEntity2);

	// Check edge case
	assert(!entityManager->IsAlive(Entity::Create(entityManager->GetGenerationnVectorSize(), 0)));

	// Checking free indices FIFO order
	EntityId entity_1 = entityManager->Create();
	EntityId entity_2 = entityManager->Create();
	EntityId entity_3 = entityManager->Create();

	entityManager->Destroy(entity_3);
	entityManager->Destroy(entity_2);

	EntityId entity_4 = entityManager->Create();
	EntityId entity_5 = entityManager->Create();

	assert(Entity::GetIndex(entity_4) == Entity::GetIndex(entity_3));
	assert(Entity::GetIndex(entity_5) == Entity::GetIndex(entity_2));

	std::cout << "All Test Passed" << "\n";

	return 0;
}