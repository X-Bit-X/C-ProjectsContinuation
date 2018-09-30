#pragma once

//Warning: This has one crappy error check. Use only clean data for this.
#include <string>
#include <vector>
#include <array>
#include <type_traits>
#include <variant>

#include "Error.h"

enum Functions
{
	SIN, COS, TAN, ASIN, ACOS, ATAN, FACT, LOG, SQRT, MOD, ROOT, POW, PI, E
};

class Math
{
public:
	bool m_negative;

	template<typename T, typename = typename std::enable_if<std::is_same<double, T>::value || std::is_same<char, T>::value || std::is_same<Functions, T>::value>::type>
	Math(const T &x, bool &&neg)
		: m_negative(neg), m_data{ x } {}
	template<typename T, typename = typename std::enable_if<std::is_same<double, T>::value || std::is_same<char, T>::value || std::is_same<Functions, T>::value>::type>
	Math(T &&x, bool &&neg)
		: m_negative(neg), m_data{ x } {}

	Math() 
		: m_isDone(true) {}
	bool isdone() const
	{
		return m_isDone;
	}

	template<typename T, typename = typename std::enable_if<std::is_same<double, T>::value || std::is_same<char, T>::value || std::is_same<Functions, T>::value>::type>
	void operator=(const T &x)
	{
		m_data.emplace<T>(x);
	}
	template<typename T, typename = typename std::enable_if<std::is_same<double, T>::value || std::is_same<char, T>::value || std::is_same<Functions, T>::value>::type>
	void operator=(T &&x)
	{
		m_data.emplace<T>(x);
	}

	template<typename T, typename = typename std::enable_if<std::is_same<double, T>::value || std::is_same<char, T>::value || std::is_same<Functions, T>::value>::type>
	bool operator==(const T &x)
	{
		if (std::is_same<T, double>::value)
			return m_data.index() == 0 && std::get<double>(m_data) == x;
		else if (std::is_same<T, char>::value)
			return m_data.index() == 1 && std::get<char>(m_data) == x;
		else if (std::is_same<T, Functions>::value)
			return m_data.index() == 2 && std::get<Functions>(m_data) == x;
	}
	bool operator==(const Math &x)
	{
		if (x.isdone())
			return m_isDone == x.m_isDone;
		else
			return m_data.index() == x.m_data.index();
	}

	template<typename T, typename = typename std::enable_if<std::is_same<double, T>::value || std::is_same<char, T>::value || std::is_same<Functions, T>::value>::type>
	constexpr T get() const
	{
		return std::get<T>(m_data);
	}

private:
	std::variant<double, char, Functions> m_data;
	bool m_isDone = false;
};

class Equation
{
public:
	double solve(const std::string &input)
	{
		//Parse
		std::vector<Math> equation;
		for (unsigned int i = 0; i < input.size(); i++)
		{
			static std::string parBuf;
			if (input[i] == '-' || input[i] == '+')
				parBuf.push_back(input[i]);
			if (input[i] == '(' || input[i] == ')')
			{
				std::string temp(std::move(parBuf) + input[i]);
				equation.push_back(temp.size() > 1 ? Math{ temp[1], temp[0] == '-' } : Math{ temp[0], false });
			}
			for (auto iter = checkers.begin(); iter != checkers.end(); iter++)
				if ((*iter)(input[i]))
				{
					parBuf.push_back(input[i]);
					if (!(*iter)(input[i + 1]))
						switch (iter - checkers.begin())
						{
						case 0:
							equation.push_back({ std::stod(parBuf), false });
							parBuf.clear();
							break;
						case 1:
							for (const auto &val : std::initializer_list<std::pair<std::string, Functions>>
								{
									{ "sin", Functions::SIN },{ "cos", Functions::COS },{ "tan", Functions::TAN },
									{ "asin", Functions::ASIN },{ "acos", Functions::ACOS },{ "atan", Functions::ATAN },
									{ "!", Functions::FACT },{ "log", Functions::LOG },{ "sqrt", Functions::SQRT },
									{ "mod", Functions::MOD },{ "root", Functions::ROOT },{ "pow", Functions::POW },
									{ "pi", Functions::PI },{ "e", Functions::E }
								})
								if (val.first == parBuf || '+' + val.first == parBuf)
									equation.push_back({ val.second, false });
								else if ('-' + val.first == parBuf)
									equation.push_back({ val.second, true });
							parBuf.clear();
							break;
						case 2:
							equation.push_back({ parBuf[0], false });
							parBuf.clear();
							break;
						}
				}
		}

		//Find all bracket pairs
		std::vector<std::array<unsigned int, 2>> brackets;
		for (unsigned int i = 0; i < equation.size(); i++)
			if (equation[i] == '(')
				brackets.push_back({ i, 0 });
			else if (equation[i] == ')')
				brackets.at([&brackets] { for (int i = brackets.size() - 1; i >= 0; i--) if (brackets[i][1] == 0) return i; throw Error("Front brackets missing."); }())[1] = i;

		//Sort order of calculation
		std::sort(brackets.begin(), brackets.end(), [](const std::array<unsigned int, 2> &x, const std::array<unsigned int, 2> &y) constexpr { return x[1] - x[0] < y[1] - y[0]; });
		if (!brackets.empty() && brackets.front()[1] == 0)
			throw Error("Back brackets missing.");

		//Calculate
		for (unsigned int i = 0; i < brackets.size(); i++)
		{
			equation[brackets[i][0]] = (equation[brackets[i][0]].m_negative ? -1 : 1) * evaluate({ &equation[brackets[i][0] + 1], &equation[brackets[i][1]] });
			std::fill(equation.begin() + brackets[i][0] + 1, equation.begin() + brackets[i][1] + 1, Math());
		}
		return evaluate(equation);
	}

private:

	static constexpr std::array<bool(*)(const char &), 3> checkers = {
		[](const char &val) constexpr
	{ 
		for (const char &i : "1234567890.")
			if (i == val && i != 0)
				return true; 
		return false; 
	},
		[](const char &val) constexpr 
	{ 
		for (const char &i : "qwertzuiopasdfghjklyxcvbnmQWERTZUIOPASDFGHJKLYXCVBNM!") 
			if (i == val && i != 0) 
				return true;
		return false; 
	},
		[](const char &val) constexpr 
	{ 
		return '*' == val || '/' == val; 
	} };

	virtual void constant(std::vector<Math> &equation)
	{
		for (unsigned int i = 0; i < equation.size(); i++)
			for (const auto &val : std::initializer_list<std::pair<Functions, double>>{ { Functions::PI, std::acos(-1) }, { Functions::E, std::exp(1) } })
				if (equation[i] == val.first)
					equation[i] = equation[i].m_negative ? -val.second : val.second;
	}

	virtual void modifer(std::vector<Math> &equation)
	{
		for (unsigned int i = 0; i < equation.size(); i++)
		{
			auto check = [&](std::initializer_list<std::pair<Functions, double(*)(double)>> &&list, double(*func)(const double &))
			{
				for (const auto &val : list)
					if (equation[i] == val.first)
					{
						equation[i] = val.second(func(equation[i + 1].get<double>())) * (equation[i].m_negative ? -1.0 : 1.0);
						equation.erase(equation.begin() + i + 1, equation.begin() + i + 2);
					}
			};
			auto fact = [](double x)
			{
				if (std::round(x) != x || x < 0)
					throw Error("Number has a point or it's negative.");
				double y = x;
				for (short i = 1; i < x; i++)
					y *= i;
				return x > 0 ? y : 1;
			};

			check(
				{
					{ Functions::SIN, std::sin },{ Functions::COS, std::cos },{ Functions::TAN, std::tan },
					{ Functions::ASIN, std::asin },{ Functions::ACOS, std::acos },{ Functions::ATAN, std::atan }
				}, [](const double &num) { return num / 180 * std::acos(-1); });
			check(
				{
					{ Functions::FACT, fact },{ Functions::LOG, std::log },{ Functions::SQRT, std::sqrt }
				}, [](const double &num) constexpr { return num; });
		}
	}

	virtual void joiner(std::vector<Math> &equation)
	{
		for (unsigned int i = 0; i < equation.size(); i++)
		{
			if (equation[i] == '*')
				equation[--i] = equation[i - 1].get<double>() * equation[i + 1].get<double>();

			else if (equation[i] == '/')
				if (equation[i + 1] == 0.0)
					throw Error("Equation has a divide by zero.");
				else
					equation[--i] = equation[i - 1].get<double>() / equation[i + 1].get<double>();

			else if (equation[i] == Functions::MOD)
				equation[--i] = static_cast<double>((int)std::round(equation[i - 1].get<double>()) % (int)std::round(equation[i + 1].get<double>()));

			else if (equation[i] == Functions::ROOT)
				equation[--i] = std::pow(equation[i - 1].get<double>(), 1.0 / static_cast<double>(equation[i + 1].get<double>()));

			else if (equation[i] == Functions::POW)
				equation[--i] = std::pow(equation[i - 1].get<double>(), equation[i + 1].get<double>());

			else
				continue;

			equation.erase(equation.begin() + i + 1, equation.begin() + i + 3);
		}
	}

	virtual double sum(std::vector<Math> &equation)
	{
		double result = 0;
		for (const auto &val : equation)
			if (!val.isdone())
				result += val.get<double>();
		return result;
	}

	double evaluate(std::vector<Math> equation)
	{
		equation.erase(std::remove(equation.begin(), equation.end(), Math()), equation.end());

		//Step 1: Constant
		constant(equation);

		//Step 2: Modifier
		modifer(equation);

		//Step 3: Joiner
		joiner(equation);

		//Step 4: Sum
		return sum(equation);
	}
};