#include "EntityManager.hpp"

EntityId EntityManager::Create()
{
	if (m_FreeIndicesQueue.size() > 0)
	{
		EntityIndex index = m_FreeIndicesQueue.front();
		m_FreeIndicesQueue.pop();
		return Entity::Create(index, m_GenerationsVector[index]);
	}

	EntityIndex index = static_cast<EntityIndex>(m_GenerationsVector.size());
	m_GenerationsVector.push_back(0);

	return Entity::Create(index, 0);
}

bool EntityManager::IsAlive(EntityId entity) const
{
	EntityGeneration generation = Entity::GetGeneration(entity);
	EntityIndex index = Entity::GetIndex(entity);

	if (index >= m_GenerationsVector.size())
	{
		return false;
	}

	return m_GenerationsVector[index] == generation;
}

void EntityManager::Destroy(EntityId entity)
{
	EntityIndex index = Entity::GetIndex(entity);

	if (!IsAlive(entity))
	{
		return;
	}

	m_GenerationsVector[index]++;
	m_GenerationsVector[index] &= Entity::GENERATION_MASK;

	m_FreeIndicesQueue.push(index);
}
