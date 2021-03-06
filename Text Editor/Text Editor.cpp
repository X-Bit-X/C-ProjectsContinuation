// Text Editor.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <queue>

#include <Input.h>


const std::array<std::wstring, 5> options = { L"/help", L"/save", L"/open", L"/edit", L"/exit" };
size_t textLoop(std::queue<std::wstring> &text)
{
	while (true)
	{
		std::wstring buf;
		std::wcin >> buf;
		for (size_t i = 0; i < options.size(); i++)
			if (options[i] == buf)
			{
				std::wcin.clear();
				std::wcin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				return i;
			}
		text.push(std::move(buf));
	}
}

int main()
{
	std::cout << "Welcome to the simple text editor. Enter \"/help\" for help." << std::endl;
	std::queue<std::wstring> text;
	while (true)
	{
		switch (textLoop(text))
		{
		case 0:
			for (const auto &val : options)
				std::wcout << val << std::endl;
			break;
		case 1:
		{
			std::cout << "Enter save file." << std::endl;
			std::wstring file;
			std::getline(std::wcin, file);
			std::wofstream saveFile(file);
			for (; !text.empty(); text.pop())
				saveFile << text.front() << L' ';
			saveFile.close();
			break;
		}
		case 2:
		{
			std::cout << "Enter file name." << std::endl;
			std::wstring fileName;
			std::getline(std::wcin, fileName);
			std::wifstream file(fileName);
			if (!file)
			{
				std::cerr << "Couldn't open file." << std::endl;
				break;
			}
			while (file >> fileName)
				text.push(std::move(fileName));
			file.close();
			break;
		}
		case 3:
		{
			std::cout << "Enter file name." << std::endl;
			std::wstring fileName;
			std::getline(std::wcin, fileName);
			std::cout << "Enter at which word number you want to edit." << std::endl;
			const size_t num = getConsoleInput<size_t>();
			std::wifstream file(fileName);
			if (!file)
			{
				std::cerr << "Couldn't open file." << std::endl;
				break;
			}
			for (size_t i = 0; file >> fileName && i < num; i++)
				text.push(std::move(fileName));
			file.close();
			break;
		}
		default:
			return 0;
		}
	}
}