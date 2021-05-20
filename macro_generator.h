//code generation function for #define[] and #for commands
#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include<iostream>
#include<vector>
#include <map>
#include <algorithm>

bool isnamechar(char& ch)
{
	if (isalnum(ch))return true;
	if (ch == '_')return true;
	return false;
}

auto search_str = [&](std::string l, std::string str)
{return std::search(l.begin(), l.end(), str.begin(), str.end()) != l.end(); };

bool first_line_command = true;
std::stringstream generateCodeFromMacros(std::stringstream text, bool& was_changed)
{
	std::stringstream result;

	std::vector<std::vector<std::string>> defines_values;
	std::vector<std::string>defines_names;

	for (std::string line; std::getline(text, line);)
	{

		auto search_str = [&](std::string l, std::string str)
		{return std::search(l.begin(), l.end(), str.begin(), str.end()) != l.end(); };

		if (first_line_command)
			if (search_str(line, "#GENERATE")) {
				first_line_command = false;
				line.clear();
				continue;
			}
			else
			{
				was_changed = false;
				return text;
			}


		std::string str_def = std::string("#define[]");



		if (search_str(line, str_def))
		{
			std::string start_line = line;

			size_t pos = line.find(str_def);
			line.erase(0, pos + 8);

			std::string define_list_name;
			std::string define_list_value;
			bool list_name_parsed = false;
			for (int ch = 0; ch < line.size(); ch++)
			{

				if (!list_name_parsed) {
					if (isnamechar(line[ch]))
						define_list_name += line[ch];
					else if (line[ch] == ' ' && define_list_name.size() != 0)
					{


						defines_names.push_back(define_list_name);
						defines_values.push_back(std::vector<std::string>());



						list_name_parsed = true;
					}
				}
				else
				{

					if (ch == line.size() - 1)
					{
						if (isnamechar(line[ch]))
							define_list_value += line[ch];

						defines_values[defines_values.size() - 1].push_back(define_list_value);
						break;

					}

					if (isnamechar(line[ch]))
						define_list_value += line[ch];

					else if (define_list_value.size() != 0)
					{

						defines_values[defines_values.size() - 1].push_back(define_list_value);
						define_list_value.clear();
					}

				}
			}

			line.clear();

			line += "//";
			line += defines_names.back();
			line += " ";
			for (auto& d : defines_values.back())
			{
				line += d; line += ",";
			}
			line.erase(line.size() - 1);

		}

		std::string str_for = "#for";
		if (search_str(line, str_for))
		{

			size_t pos = line.find(str_for);
			line.erase(0, pos + 4);

			std::string start_line = line;
			std::string debug_line = start_line;
			debug_line.insert(0, "//");
			debug_line += " START GENERATION";
			result << debug_line << "\n";



			std::vector<std::string> possition_in_macro;


			size_t all_combinations_int = 1;
			int num_of_new_lines = 1;

			std::map<int, std::pair<std::string, int>> macro_order;

			std::string line_debug(line);
			for (int i = 0; i < defines_names.size(); i++)
				if (search_str(line_debug, defines_names[i]))
				{

					macro_order[(int)line_debug.find(defines_names[i])] = std::make_pair(defines_names[i], i);
					all_combinations_int *= defines_values[i].size();

					line_debug.erase((int)line_debug.find(defines_names[i]), defines_names[i].size());
				}

			for (int i = 0; i < defines_names.size(); i++)
				if (search_str(line_debug, defines_names[i]))
				{

					result << "//GENERATION ERROR IN LINE:" << start_line << "\n";
					result << "//ONE OR MORE ARGS IN #for HAVE NAME: " << defines_names[i] << "\n";
					result << "//YOU KNOW HOW MACROS IS DANGEROUS SO ALL ANOTHER CODE CORRUPTED " << "\n";
					result << "//FIX THE MACRO AND TRY AGAIN " << "\n";
					result << "//ONLY ONE ENTRANCE OF ARG IN #for ALLOWED " << "\n";
					return result;
				}

			std::vector<int> possition_in_macro_int;
			for (auto& name : macro_order)
			{
				possition_in_macro_int.push_back(name.second.second);
				possition_in_macro.push_back(name.second.first);
			}


			std::cout << "all_combinations_int = " << all_combinations_int << std::endl;
			std::cout << "possition_in_macro = ";
			for (auto& p : possition_in_macro)std::cout << p << " "; std::cout << std::endl;
			std::cout << "possition_in_macro_int = ";
			for (auto& p : possition_in_macro_int)std::cout << p << " "; std::cout << std::endl;

			///////////////////	///////////////////	///////////////////

			std::vector<std::string> all_combinations; all_combinations.resize(all_combinations_int);

			size_t size = possition_in_macro.size();
			std::vector<int> V; V.resize(size);
			V[size - 1] = 1;

			for (int i = int(size - 2); i >= 0; i--)
			{
				std::cout << "i= " << i << " : " << V[i + 1] << "*" << defines_values[possition_in_macro_int[i]].size() << std::endl;

				V[i] = V[i + 1] * int(defines_values[possition_in_macro_int[i + 1]].size());
			}

			std::cout << "------------------------" << std::endl;


			for (int i = 0; i < size; i++)
			{
				int counter = 0;
				for (int j = 0; j < all_combinations_int / (V[i] * defines_values[possition_in_macro_int[i]].size()); j++)
					for (int k = 0; k < defines_values[possition_in_macro_int[i]].size(); k++)
						for (int l = 0; l < V[i]; l++)
						{
							all_combinations[counter] += defines_values[possition_in_macro_int[i]][k];
							all_combinations[counter++] += ",";
						}
			}

			std::cout << "------------------------" << std::endl;

			std::cout << "V = ";
			for (auto& v : V)std::cout << v << " "; std::cout << std::endl;

			for (int i = 0; i < all_combinations_int; i++) {
				all_combinations[i].pop_back();
				std::cout << "all_combinations[i] = " << all_combinations[i] << std::endl;
			}
			std::cout << "all_combinations.size() = " << all_combinations.size() << std::endl;
			std::cout << "predicted:all_combinations.size() = " << all_combinations_int << std::endl;


			///////////////////	///////////////////	///////////////////

			size_t replace_from = line.find('(') + 1,
				replace_to = line.find(')') - replace_from;


			for (int i = 0; i < all_combinations_int; i++)
			{
				std::string new_line = line;
				new_line.replace(replace_from, replace_to, all_combinations[i]);
				result << new_line << "\n";
				std::cout << new_line << std::endl;
			}
			line.clear();

			debug_line = start_line;
			debug_line.insert(0, "//");
			debug_line += " END GENERATION";
			result << debug_line << "\n";

		}

		result << line << "\n";
	}

	for (int i = 0; i < defines_names.size(); i++)
	{
		std::cout << "_" << defines_names[i] << "_";
		for (auto& d : defines_values[i])
			std::cout << "_" << d << "_";
		std::cout << std::endl;

	}
	first_line_command = true;
	was_changed = true;
	return result;

}