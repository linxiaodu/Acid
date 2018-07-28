#pragma once

#include "Pipeline.hpp"

namespace acid
{
	/// <summary>
	/// Class that represents a compute Vulkan pipeline.
	/// </summary>
	class ACID_EXPORT Compute :
		public Pipeline
	{
	private:
	public:
		Compute(const std::string &shader, const VertexInput &vertexInput);

		~Compute();
	};
}
