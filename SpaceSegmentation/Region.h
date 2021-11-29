#pragma once

#include "HyperRect.h"
#include "RegionType.h"

#include <vector>

namespace geometry
{
	namespace computation
	{

		template <typename TFloat, std::size_t Dimensions = 2>
		struct Region
		{
			using HyperRect = geometry::HyperRect<TFloat, Dimensions>;

			using region_container = std::vector<Region<TFloat, Dimensions>>;
			using index_type = typename HyperRect::index_type;

			Region() = delete;

			Region(RegionType region_type, const HyperRect* shape, Region* parent) :
				regionType(region_type), shape(shape), parent(parent)
			{}

			bool is_region_contained(const HyperRect* inner_shape) const
			{
				assert(inner_shape != nullptr);

				bool is_in_range = true;
				for (index_type idx{}; idx < Dimensions; ++idx)
				{
					is_in_range = is_in_range &&
						shape->get_min_coord()[idx] <= inner_shape->get_min_coord()[idx] &&
						inner_shape->get_max_coord()[idx] <= shape->get_max_coord()[idx];
				}

				return is_in_range;
			}

			inline static RegionType get_region_type_from_parent(Region* parent)
			{
				return parent == nullptr ? RegionType::Land :
					parent->regionType == RegionType::Sea ?
					RegionType::Land :
					RegionType::Sea;
			}

			RegionType regionType = RegionType::Unknown;
			region_container sub_regions;

			Region* parent = nullptr;
			const HyperRect* shape = nullptr;
		};

	}
}