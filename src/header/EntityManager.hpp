#pragma once

#include "Entity.hpp"
#include <queue>
#include <vector>

class EntityManager
{
public:
	[[nodiscard]]
	EntityId Create();

	[[nodiscard]]
	bool IsAlive(EntityId entity) const;

	void Destroy(EntityId entity);

	size_t GetGenerationVectorSize() const
	{
		return m_GenerationsVector.size();
	}

private:
	std::vector<EntityGeneration> m_GenerationsVector;
	std::queue<EntityIndex> m_FreeIndicesQueue;
};