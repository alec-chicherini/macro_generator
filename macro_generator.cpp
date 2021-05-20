
#include <filesystem>
#include "macro_generator.h"

namespace fs = std::filesystem;
bool  was_changed = false;
int main(int argc, char* argv[])
{
	if (argc == 1) return 0;

	std::string projectDir(argv[1]);

	try {
		for (auto& f : fs::directory_iterator(projectDir))
		{
			auto current = f.path().filename().string();

			if (search_str(current, ".cpp") ||
				search_str(current, ".h"))
			{

				std::cout << projectDir + current << " GENERATION STARTED" << std::endl;
				std::ifstream input;
				std::stringstream text;
				std::stringstream ssoutput;
				input.open(projectDir + current);
				text << input.rdbuf();
				ssoutput << generateCodeFromMacros(std::move(text), was_changed).rdbuf();
				input.close();

				if (was_changed)
				{
					std::ofstream output;
					output.open(projectDir + current);
					output << ssoutput.rdbuf();

					output.close();
					std::cout << projectDir + current << " GENERATE COMPLETE" << std::endl;
				}
				else
					std::cout << projectDir + current << " GENERATE ZERO CHANGES" << std::endl;


			}
		}
	}
	catch (fs::filesystem_error const& e)
	{
		std::cout << e.what() << '\n';
	}
	return 0;
}


