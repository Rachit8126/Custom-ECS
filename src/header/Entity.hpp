#pragma once

#include <cstdint>

using EntityId = std::uint32_t;
using EntityIndex = std::uint32_t;
using EntityGeneration = std::uint32_t;

namespace Entity
{
	inline constexpr std::uint32_t INDEX_BITS = 20;
	inline constexpr std::uint32_t GENERATION_BITS = 12;
	inline constexpr std::uint32_t INDEX_MASK = (1u << INDEX_BITS) - 1u;
	inline constexpr std::uint32_t GENERATION_MASK = (1u << GENERATION_BITS) - 1u;


	inline EntityId Create(EntityIndex index, EntityGeneration generation)
	{
		generation &= GENERATION_MASK;

		return (generation << INDEX_BITS) | (index & INDEX_MASK);
	}

	inline EntityIndex GetIndex(EntityId entity)
	{
		return entity & INDEX_MASK;
	}

	inline EntityGeneration GetGeneration(EntityId entity)
	{
		return (entity >> INDEX_BITS) & GENERATION_MASK;
	}
}