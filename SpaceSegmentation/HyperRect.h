#pragma once

#include <vector>
#include <iostream>
#include <numeric>
#include <cstddef>
#include <cassert>
#include <array>
#include <concepts>

namespace geometry
{
	// Generalised rectangle
	template <std::floating_point TFloat = float, std::size_t Dimensions = 2>
	struct HyperRect
	{
		using coordinate = std::array<TFloat, Dimensions>;
		using value_type = typename coordinate::value_type;

		using float_type = TFloat;
		using index_type = decltype(Dimensions);

		const index_type dimension = Dimensions;

	private:
		coordinate min_corner{};
		coordinate max_corner{};

		float_type area{};

	public:
		HyperRect() = delete;

		HyperRect(std::convertible_to<coordinate> auto min, std::convertible_to<coordinate> auto max) :
			min_corner(min), max_corner(max), area(this->compute_area())
		{
			// Assert object is valid i.e. max coord >= min_coord && area is non-negative
		}

		HyperRect(const HyperRect& rhs) :
			min_corner(rhs.min_corner), max_corner(rhs.max_corner), area(rhs.area)
		{
		}

		HyperRect& operator=(HyperRect rhs)
		{
			if (this != &rhs)
			{
				using std::swap;

				swap(min_corner, rhs.min_corner);
				swap(max_corner, rhs.max_corner);
				swap(area, rhs.area);
			}

			return *this;
		}

		friend auto operator> (const HyperRect& lhs, const HyperRect& rhs)
		{
			return lhs.area > rhs.area;
		}

		const auto& get_min_coord() const
		{
			return min_corner;
		}

		const auto& get_max_coord() const
		{
			return max_corner;
		}

		const auto get_area() const
		{
			return area;
		}

		void display(std::ostream& out) const
		{
			out << "\nGeometry: HyperRect\n";

			out << "min: ";
			display_corner(out, min_corner);

			out << "max: ";
			display_corner(out, max_corner);

			out << "area: ";
			out << compute_area();

			out << "\n";
		}

	private:
		TFloat compute_area() const
		{
			return std::transform_reduce(
				max_corner.begin(), max_corner.end(),
				min_corner.begin(),
				static_cast<TFloat>(1.0),
				std::multiplies<>(),
				std::minus<>());
		}

		void display_corner(std::ostream& out, const coordinate& corner) const
		{
			for (const auto& coord : corner)
			{
				out << coord << ", ";
			}

			out << "\n";
		}
	};

	using Box = HyperRect<float, 2>;
}