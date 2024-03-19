#pragma once
#include "CoreSystems/Geometry/Indices/BowIndicesUnsignedShort.h"

namespace bow {
	
	IndicesUnsignedShort::IndicesUnsignedShort() :IIndicesBase(IndicesType::UnsignedShort), Values(std::vector<unsigned short>())
	{
	}

	IndicesUnsignedShort::IndicesUnsignedShort(int capacity) : IIndicesBase(IndicesType::UnsignedShort), Values(std::vector<unsigned short>(capacity))
	{
	}

	size_t IndicesUnsignedShort::Size()
	{
		return Values.size();
	}

	IndicesUnsignedShort::~IndicesUnsignedShort()
	{
		Values.clear();
	}

}
