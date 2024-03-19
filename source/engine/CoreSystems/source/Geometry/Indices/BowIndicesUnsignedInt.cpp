#pragma once
#include "CoreSystems/Geometry/Indices/BowIndicesUnsignedInt.h"

namespace bow {
	
	IndicesUnsignedInt::IndicesUnsignedInt() : IIndicesBase(IndicesType::UnsignedInt), Values(std::vector<size_t>())
	{
	}

	IndicesUnsignedInt::IndicesUnsignedInt(int capacity) : IIndicesBase(IndicesType::UnsignedInt), Values(std::vector<size_t>(capacity))
	{
	}

	size_t IndicesUnsignedInt::Size()
	{
		return (size_t)Values.size();
	}

	IndicesUnsignedInt::~IndicesUnsignedInt()
	{
		Values.clear();
	}

}