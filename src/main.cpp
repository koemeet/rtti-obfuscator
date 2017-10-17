#include <windows.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <random>
#include <time.h>
#include <cstdlib>
#include <unordered_set>

#include <boost/regex.hpp>
#include <boost/filesystem.hpp>

using namespace std;

std::unordered_set<std::string> usedTypeNames;

std::string getRandomString(const int len) {
	static const char alpha[] =
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz";

	static const char alphanum[] =
		"0123456789"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz";

	string s;
	s.resize(len);

	for (auto i = 0; i < len; ++i) {
		// we always want to start types with an alphabetical letter
		if (0 == i)
		{
			s[i] = alpha[rand() % (sizeof(alpha) - 1)];

		}
		else
		{
			s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];	
		}
	}

	s[len] = 0;
	
	return s;
}

int main(int argc, char* argv[])
{
	cout << "===== RTTI obfuscator by koemeet =====" << endl;

	srand(time(nullptr));

	try 
	{
		if (argc < 2) 
		{
			throw std::exception("Please provide a path or drop a file into me.");
		}

		// path to input binary
		string path = argv[1];

		std::ifstream fs(path, std::fstream::binary);
		if (fs.fail())
		{
			throw std::exception("Could not open source binary");
		}

		// read file contents
		std::stringstream ss;
		ss << fs.rdbuf();
		auto contents = ss.str();

		boost::regex reg(R"(\.(\?AV|PEAV)(.+?)@@\0)");

		// replace RTTI types
		contents = boost::regex_replace(contents, reg, [](const boost::smatch& m)
		{
			auto prefix = m[1].str();
			auto typeName = m[2].str();

			// get a new random name untill we have one we never used before
			std::string newTypeName;
			do
			{
				newTypeName = getRandomString(1 + prefix.size() + typeName.size() + 2);
			} while (usedTypeNames.find(newTypeName) != usedTypeNames.end());

			usedTypeNames.emplace(newTypeName);

			return newTypeName + '\0';
		});

		// generate output path
		boost::filesystem::path p(path);
		auto outputPath = p.parent_path().string() + "\\" + p.stem().string() + p.extension().string();

		// write to file
		std::ofstream os(outputPath, std::ofstream::trunc | std::ofstream::binary);
		if (!os.write(contents.data(), contents.size()))
		{
			throw std::exception((std::string("Unable to write to file ") + outputPath).c_str());
		}
		else
		{
			cout << "Successfully obfuscated RTTI information. Output written to " << outputPath << endl;
			system("pause");
		}
	} 
	catch (std::exception &e)
	{
		cout << e.what() << endl;
		system("pause");
		return 1;
	}

    return 0;
}
