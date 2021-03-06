// Inverted index.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <algorithm>
#include <list>


int main()
{
	std::wcout << L"Enter a word for search or a file for inclusion." << std::endl;
	std::wstring text;
	std::getline(std::wcin, text);
	std::wifstream source(text);
	if (!source)
		for (const auto &name : std::filesystem::directory_iterator(L"data"))
		{
			std::wifstream data(name.path().wstring() + L'/' + text);
			if (data)
			{
				std::wcout << name.path().wstring() << L" has \"" << text << L"\" in slot numbers: ";
				std::wstring buf;
				data >> buf;
				std::wcout << buf << std::endl;
				data.close();
			}
		}
	else
	{
		const std::wstring dir = L"data/" + text;
		std::wcout << L"Creating data set." << std::endl;
		if (!std::filesystem::exists(L"data"))
			std::filesystem::create_directory(L"data");
		if (std::filesystem::exists(dir))
			std::filesystem::remove_all(dir);
		std::filesystem::create_directory(dir);

		for (size_t i = 1; source; i++)
		{
			std::wstring buff;
			source >> buff;

			for (const auto &check : L".,\"{}[]()!:")
				buff.erase(std::remove(buff.begin(), buff.end(), check), buff.end());
			std::transform(buff.begin(), buff.end(), buff.begin(), ::tolower);

			if (!buff.empty())
			{
				std::wofstream wordFile(dir + L'/' + buff, std::ios_base::app);
				wordFile << i << L",";
				wordFile.close();
			}
		}
		source.close();
		std::wcout << L"Done." << std::endl;
	}

	getchar();
    return 0;
}