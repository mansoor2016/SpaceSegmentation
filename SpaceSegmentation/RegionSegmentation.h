#pragma once

#include "Region.h"
#include "HyperRect.h"
#include "RegionType.h"

#include <vector>
#include <algorithm>
#include <iterator>
#include <concepts>
#include <functional>
#include <utility>

namespace geometry
{
	namespace computation
	{
		namespace segmentation
		{
			template <typename TFloat = float, std::size_t Dimensions = 2>
			class RegionSegmentation
			{
				using HyperRect = geometry::HyperRect<TFloat, Dimensions>;
				using ShapePtr = const HyperRect*;

				using Region = Region<TFloat, Dimensions>;
				using RegionPtr = Region*;

				typename Region::region_container classified_regions;

			public:
				RegionSegmentation(std::forward_iterator auto const begin, std::forward_iterator auto const end)
				{
					init(begin, end);
				}

				auto count_regions(const RegionType region_type) const
				{
					std::function<typename Region::index_type(const decltype(classified_regions)&)> counter =
						[&](const auto& regions_collection) -> Region::index_type
					{
						typename Region::index_type count{};

						for (const auto& elem : regions_collection)
						{
							count += elem.regionType == region_type ? 1 : 0;

							if (not elem.sub_regions.empty())
							{
								count += counter(elem.sub_regions);
							}
						}

						return count;
					};

					return counter(classified_regions);
				}

			private:
				void init(std::forward_iterator auto const begin, std::forward_iterator auto const end)
				{
					auto ordered_shapes_desc = std::vector(begin, end);
					std::sort(ordered_shapes_desc.begin(), ordered_shapes_desc.end(),
						[](const auto& elem1, const auto& elem2)
						{
							return elem1.get_area() > elem2.get_area();
						});

					for (auto it = ordered_shapes_desc.begin();
						it != ordered_shapes_desc.end();
						++it)
					{
						insert_into_classified_regions(&*it, classified_regions, nullptr);
					}
				}

				void insert_into_classified_regions(
					ShapePtr shape,
					typename Region::region_container& current_regions, RegionPtr parent)
				{
					auto [is_contained_in_another_region, parent_region] =
						is_region_contained(
							current_regions.begin(),
							current_regions.end(),
							shape);

					if (not is_contained_in_another_region)
					{
						current_regions.emplace_back(
							Region::get_region_type_from_parent(parent),
							shape,
							parent);
					}
					else
					{
						insert_into_classified_regions(
							shape,
							parent_region->sub_regions,
							parent_region);
					}
				}

				std::pair<bool, RegionPtr> is_region_contained(
					std::forward_iterator auto begin,
					std::forward_iterator auto end,
					ShapePtr shape)
				{
					auto it = std::find_if(begin, end,
						[&](const auto& elem)
						{
							return elem.is_region_contained(shape);
						});

					auto is_in_region = it != end;

					return { is_in_region, is_in_region ? &*it : nullptr };
				}
			};
		}
	}
}
