#ifndef UNITCONVERSION
#define UNITCONVERSION

#include <vector>
#include <algorithm>
#include <string>
#include <array>

#include "Error.h"

using Prefix = std::pair<std::string, double>;
const std::array<Prefix, 20> prefixes = { { { "Y", 1e24 },{ "Z", 1e21 },{ "E", 1e18 },{ "P", 1e15 },{ "T", 1e12 },{ "G", 1e9 },
	{ "M", 1e6 },{ "k", 1e3 },{ "h", 1e2 },{ "da", 1e1 },{ "d", 1e-1 },
	{ "c", 1e-2 },{ "m", 1e-3 },{ "u", 1e-6 },{ "n", 1e-9 },{ "p", 1e-12 },
	{ "f", 1e-15 },{ "a", 1e-18 },{ "z", 1e-21 },{ "y", 1e-24 } } };
class Type
{
public:
	Type() {}

	Type(std::string unit)
			: m_unit{ std::move(unit) } {}

	Type(const Type &ty)
		: m_unit{ ty.m_unit } {}

	Type(Type &&ty)
		: m_unit{ std::move(ty.m_unit) }  {}

	double convert(const std::string &from, const std::string &to) const
	{
		auto find = [&](const std::string &t) constexpr
		{
			for (const auto &prefix : prefixes)
				if (t.compare(0, prefix.first.size(), prefix.first) == 0)
					return prefix.second;
			Error("false prefix");
		};

		return find(from) / find(to);
	}
	
	const std::string& unit() const { return m_unit; }

	Type& operator=(const Type &ty)
	{
		m_unit = ty.m_unit;
		return *this;
	}
	Type& operator=(Type &&ty)
	{
		m_unit = std::move(ty.m_unit);
		return *this;
	}
	
private:
	std::string m_unit;
};

//namespace DefaultType
//{
//	extern const Type distance({ 1, 1.61, 1609.34, 63360, 5280, 160934 }, { "Mile", "Kilometre", "Metre", "Inch", "Foot", "Centimetre" });
//}

#endif // !UNITCONVERSION
