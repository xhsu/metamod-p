// MdlAnimTime.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <cassert>
#include <cstdio>

#include <fmt/color.h>

import <filesystem>;
import <string>;

import studio;

using std::string;

namespace fs = std::filesystem;

int main(int argc, const char *argv[]) noexcept
{
#ifdef _DEBUG
	assert(argc == 2);
	assert(fs::exists(argv[1]));
#else
	if (argc != 2)
	{
		fmt::print(fg(fmt::color::red), "No model file selected.\n");
		return 0;
	}

	if (!fs::exists(argv[1]))
	{
		fmt::print(fg(fmt::color::red), "Model file: \"{}\" no found.\n", argv[1]);
		return 0;
	}
#endif

	[[likely]]
	if (auto f = fopen(argv[1], "rb"); f)
	{
		fseek(f, 0, SEEK_END);
		auto const iSize = ftell(f);

		fseek(f, 0, SEEK_SET);
		auto pBuffer = calloc(1, iSize);
		fread(pBuffer, iSize, 1, f);

		auto const phdr = (studiohdr_t *)pBuffer;
		auto const pseq = (mstudioseqdesc_t *)((byte *)pBuffer + phdr->seqindex);

		string szModelName = phdr->name;
		if (auto const pos = szModelName.find_last_of('.'); pos != string::npos)
			szModelName.erase(pos);

		for (auto i = 0; i < phdr->numseq; ++i)
			fmt::print("{:<16}: {}/{} == {}\n", pseq[i].label, pseq[i].numframes, pseq[i].fps, (double)pseq[i].numframes / (double)pseq[i].fps);

		if (auto fout = fopen(fmt::format("{}.hpp", szModelName).c_str(), "wt"); fout)
		{
			fmt::print(fout, "namespace {}\n{{\n", szModelName);
			fmt::print(fout,
				"\tenum struct seq\n"
				"\t{{\n"
			);

			for (auto i = 0; i < phdr->numseq; ++i)
				fmt::print(fout, "\t\t{},\n", pseq[i].label);

			fmt::print(fout, "\t}};\n");
			fmt::print(fout, "\n");

			fmt::print(fout, 
				"\tnamespace time\n"
				"\t{{\n"
			);

			for (auto i = 0; i < phdr->numseq; ++i)
				fmt::print(fout, "\t\tinline constexpr float {}\t= (float)((double){} / (double){});\n", pseq[i].label, pseq[i].numframes, pseq[i].fps);

			fmt::print(fout, "\t}};\n");
			fmt::print(fout, "}};\n");
			fclose(fout);
		}

		free(pBuffer);
		fclose(f);
	}

	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
