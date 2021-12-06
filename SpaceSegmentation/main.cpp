#include "HyperRect.h"
#include "RegionType.h"
#include "Region.h"
#include "RegionSegmentation.h"
#include "ShapeDataIngestion.h"

#include <exception>
#include <iostream>

using namespace ingestion;
using namespace geometry::computation;

int main()
{
	try
	{
		const auto boxes = BoxIngester().ReadLines();
		const auto number_of_land_regions = 
			segmentation::RegionSegmenter(boxes.cbegin(), boxes.cend()).
				count_regions(geometry::computation::RegionType::Land);

		std::cout << number_of_land_regions << std::endl;

		return 0;
	}
	catch (std::exception& ex)
	{
		std::cerr << ex.what() << std::endl;
	}
	catch (...)
	{
		std::cerr << "Encountered unhandled exception." << std::endl;
	}

	return -1;
}