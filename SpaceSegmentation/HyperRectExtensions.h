#pragma once

#include "HyperRect.h"

namespace geometry
{
	namespace extensions
	{
		template <typename U>
		inline static auto CreateHyperRectExtensions(U const& hyperRect)
		{
			return HyperRectExtensions<std::decay_t<U>>(hyperRect);
		}

		template <typename T>
		struct HyperRectExtensions
		{
			T const hyperRect;

			HyperRectExtensions(T const& hyperRect) :
				hyperRect(hyperRect)
			{
			}

			bool contains(T const& inner_shape) const
			{
				assert(inner_shape.dimension == hyperRect.dimension);

				bool is_in_range = true;
				for (typename T::index_type idx{}; idx < inner_shape.dimension; ++idx)
				{
					is_in_range = is_in_range &&
						hyperRect.get_min_coord()[idx] <= inner_shape.get_min_coord()[idx] &&
						inner_shape.get_max_coord()[idx] <= hyperRect.get_max_coord()[idx];
				}

				return is_in_range;
			}
		};
	}
}