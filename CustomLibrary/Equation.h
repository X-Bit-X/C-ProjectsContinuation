
//Warning: This has one crappy error check. Use only clean data for this.

#ifndef EQUATION
#define EQUATION

#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <algorithm>
#include <cmath>

#include "Error.h"

class Equation
{
public:
	double solve(const std::string &input)
	{
		//Parse
		std::vector<std::string> equation;
		for (unsigned int i = 0; i < input.size(); i++)
		{
			static std::string parBuf;

			if (input[i] == '-' || input[i] == '+')
				parBuf.push_back(input[i]);
			if (input[i] == '(' || input[i] == ')')
				equation.push_back(std::move(parBuf) + input[i]);

			for (const auto &func : checkers)
				if (func(input[i]))
				{
					parBuf.push_back(input[i]);
					if (!func(input[i + 1]))
						equation.push_back(std::move(parBuf));
				}
		}

		//Find all bracket pairs
		std::vector<std::array<unsigned int, 2>> brackets;
		for (unsigned int i = 0; i < equation.size(); i++)
			if (equation[i] == "(" || equation[i] == "+(" || equation[i] == "-(")
				brackets.push_back({ i, 0 });
			else if (equation[i] == ")")
				brackets.at([&brackets] { for (int i = brackets.size() - 1; i >= 0; i--) if (brackets[i][1] == 0) return i; throw Error("Front brackets missing."); }())[1] = i;

		//Sort order of calculation
		std::sort(brackets.begin(), brackets.end(), [](const std::array<unsigned int, 2> &x, const std::array<unsigned int, 2> &y) constexpr { return x[1] - x[0] < y[1] - y[0]; });
		if (!brackets.empty() && brackets.front()[1] == 0)
			throw Error("Back brackets missing.");

		//Calculate
		for (unsigned int i = 0; i < brackets.size(); i++)
		{
			equation[brackets[i][0]] = std::to_string((equation[brackets[i][0]] == "-(" ? -1 : 1) * evaluate(std::vector<std::string>(&equation[brackets[i][0] + 1], &equation[brackets[i][1]])));
			std::fill(equation.begin() + brackets[i][0] + 1, equation.begin() + brackets[i][1] + 1, "");
		}
		std::remove(equation.begin(), equation.end(), "");

		return evaluate(equation);
	}

private:

	static constexpr std::array<bool(*)(const char &), 3> checkers = {
		[](const char &val) constexpr { for (char i = '0'; i <= '9'; i++) if (i == val || val == '.') return true; return false; },
		[](const char &val) constexpr { for (char i = 'a'; i <= 'z'; i++) if (i == val) return true; return false; },
		[](const char &val) constexpr { return '*' == val || '/' == val; } };

	virtual void constant(std::vector<std::string> &equation)
	{
		for (unsigned int i = 0; i < equation.size(); i++)
			for (const auto &val : { std::make_pair("pi", std::acos(-1)), std::make_pair("e", std::exp(1)) })
				if (equation[i] == val.first || equation[i] == '+' + val.first || equation[i] == '-' + val.first)
					if (equation[i].front() != '-')
						equation[i] = std::to_string(val.second);
					else
						equation[i] = std::to_string(-val.second);
	}

	virtual void modifer(std::vector<std::string> &equation)
	{
		for (unsigned int i = 0; i < equation.size(); i++)
		{
			auto check = [&equation, &i](const std::pair<std::string, double(*)(double)> &val, double(*func)(const double &))
			{
				if (equation[i] == val.first || equation[i] == '-' + val.first || equation[i] == '+' + val.first)
				{
					if (equation[i].front() != '-')
						equation[i] = std::to_string(val.second(func(std::stod(equation[i + 1]))));
					else
						equation[i] = std::to_string(-val.second(func(std::stod(equation[i + 1]))));
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

			for (const std::pair<std::string, double(*)(double)> &val :
				{
					std::make_pair("sin", static_cast<double(*)(double)>(std::sin)),
					std::make_pair("cos", static_cast<double(*)(double)>(std::cos)),
					std::make_pair("tan", static_cast<double(*)(double)>(std::tan)),
					std::make_pair("asin", static_cast<double(*)(double)>(std::asin)),
					std::make_pair("acos", static_cast<double(*)(double)>(std::acos)),
					std::make_pair("atan", static_cast<double(*)(double)>(std::atan))
				})
				check(val, [](const double &num) { return num / 180 * std::acos(-1); });
			for (const std::pair<std::string, double(*)(double)> &val :
				{
					std::make_pair("!", static_cast<double(*)(double)>(fact)),
					std::make_pair("log", static_cast<double(*)(double)>(std::log)),
					std::make_pair("sqrt", static_cast<double(*)(double)>(std::sqrt))
				})
				check(val, [](const double &num) constexpr { return num; });
		}
	}

	virtual void joiner(std::vector<std::string> &equation)
	{
		for (unsigned int i = 0; i < equation.size(); i++)
			if (equation[i] == "*" || equation[i] == "/" || equation[i] == "mod" || equation[i] == "root" || equation[i] == "pow")
			{
				if (equation[i] == "*")
					equation[--i] = std::to_string(std::stod(equation[i - 1]) * std::stod(equation[i + 1]));
				else if (equation[i] == "/")
					equation[--i] = std::to_string(std::stod(equation[i - 1]) / std::stod(equation[i + 1]));
				else if (equation[i] == "mod")
					equation[--i] = std::to_string((int)std::round(std::stod(equation[i - 1])) % (int)std::round(std::stod(equation[i + 1])));
				else if (equation[i] == "root")
					equation[--i] = std::to_string(std::pow(std::stod(equation[i - 1]), 1 / std::stod(equation[i + 1])));
				else if (equation[i] == "pow")
					equation[--i] = std::to_string(std::pow(std::stod(equation[i - 1]), std::stod(equation[i + 1])));
				if (equation[i + 1] == "/" && (equation[i + 2] == "0.000000" || equation[i + 2] == "0"))
					throw Error("Equation has a divide by zero.");
				equation.erase(equation.begin() + i + 1, equation.begin() + i + 3);
			}
	}

	virtual double sum(std::vector<std::string> &equation)
	{
		double result = 0;
		for (const auto &val : equation)
			if (val != "")
				result += std::stod(val);
		return result;
	}

	double evaluate(std::vector<std::string> equation)
	{
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
#endif // !EQUATION