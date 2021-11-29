#include "HyperRect.h"
#include "RegionType.h"
#include "Region.h"
#include "RegionSegmentation.h"
#include "ShapeDataIngestion.h"

#include <exception>
#include <iostream>

int main()
{
	try
	{
		using Box = geometry::HyperRect<float, 2>;
		using BoxIngester = ingestion::ShapeDataIngestion<Box::float_type, Box::dimension>;
		using RegionSegmentation = geometry::computation::segmentation::RegionSegmentation<Box::float_type, Box::dimension>;

		const auto boxes = BoxIngester().ReadLines();
		const auto number_of_land_regions = RegionSegmentation(boxes.cbegin(), boxes.cend()).
			count_regions(geometry::computation::RegionType::Land);

		std::cout << number_of_land_regions << std::endl;
		return 0;
	}
	catch (std::exception ex)
	{
		std::cerr << ex.what() << std::endl;
	}
	catch (...)
	{
		std::cerr << "Encountered unhandled exception." << std::endl;
	}

	return -1;
}