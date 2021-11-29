#pragma once

#include "HyperRect.h"
#include "HyperRectExtensions.h"
#include "RegionType.h"

#include <vector>
#include <type_traits>

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

			RegionType regionType = RegionType::Unknown;
			region_container sub_regions;

			const Region* parent = nullptr;
			const HyperRect* shape = nullptr;

			Region() = delete;

			Region(RegionType region_type, const HyperRect* shape, const Region* parent) :
				regionType(region_type), shape(shape), parent(parent)
			{
				assert(shape);
			}

			bool is_region_contained(const HyperRect* inner_shape) const
			{
				assert(inner_shape != nullptr);
				const auto hyperRectHelper = 
					geometry::extensions::CreateHyperRectExtensions(*shape);

				return hyperRectHelper.contains(*inner_shape);
			}

			inline static RegionType get_region_type_from_parent(Region* parent)
			{
				return parent == nullptr ? RegionType::Land :
					parent->regionType == RegionType::Sea ?
					RegionType::Land :
					RegionType::Sea;
			}
		};
	}
}