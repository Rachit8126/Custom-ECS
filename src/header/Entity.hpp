#pragma once

#include <cstdint>

using EntityId = std::uint32_t;

namespace Entity
{
	inline constexpr EntityId INDEX_BITS = 20;
	inline constexpr EntityId GENERATION_BITS = 12;
	inline constexpr EntityId INDEX_MASK = (1u << INDEX_BITS) - 1u;
	inline constexpr EntityId GENERATION_MASK = (1u << GENERATION_BITS) - 1u;


	inline EntityId Create(EntityId index, EntityId generation)
	{
		generation &= GENERATION_MASK;

		return (generation << INDEX_BITS) | (index & INDEX_MASK);
	}

	inline EntityId GetIndex(EntityId entity)
	{
		return entity & INDEX_MASK;
	}

	inline EntityId GetGeneration(EntityId entity)
	{
		return (entity >> INDEX_BITS) & GENERATION_MASK;
	}
}