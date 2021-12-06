#pragma once

#include "HyperRect.h"

#include <string>
#include <vector>
#include <ostream>
#include <iostream>

namespace ingestion
{
	/// <summary>
	/// This class assumes the format of the read in data:
	/// <count>
	/// <min point> <max point>
	/// ....
	/// </summary>

	template <std::floating_point TFloat = float, std::size_t Dimensions = 2>
	class ShapeDataIngestion
	{
		using shape = typename geometry::HyperRect<TFloat, Dimensions>;
		using index_type = decltype(Dimensions);

		std::istream& input_data;
		std::ostream& logging_stream;

	public:
		ShapeDataIngestion(std::istream& input = std::cin, std::ostream& logging_stream = std::cout) :
			input_data(input), logging_stream(logging_stream)
		{
			std::cin.exceptions(std::ios::failbit | std::ios::badbit);
		}

		auto ReadLines() const
		{
			//logging_stream << "Reading input data\n";

			const auto number_of_lines = ReadCount();
			//logging_stream << "Lines to read: " << number_of_lines << "\n";

			typename std::vector<geometry::HyperRect<TFloat, Dimensions>> ret_val;
			ret_val.reserve(number_of_lines);

			for (index_type idx{}; idx < number_of_lines; ++idx)
			{
				ret_val.push_back(this->ReadLine());
			}

			return ret_val;
		}

	private:

		auto ReadCount() const
		{
			index_type count{};
			input_data >> count;
			return count;
		}

		auto ReadLine() const
		{
			typename shape::coordinate min_coord{};
			typename shape::coordinate max_coord{};
			typename shape::coordinate::value_type temp{};

			for (auto& elem : min_coord)
			{
				input_data >> temp;
				elem = temp;
			}

			for (auto& elem : max_coord)
			{
				input_data >> temp;
				elem = temp;
			}

			shape ret_val(min_coord, max_coord);
			// ret_val.display(logging_stream);

			return ret_val;
		}
	};

	using BoxIngester = ShapeDataIngestion<geometry::Box::float_type, 2>;
}
