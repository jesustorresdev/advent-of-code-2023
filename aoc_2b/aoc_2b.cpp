#include <cassert>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <string_view>
#include <vector>
#include <ranges>

namespace aoc
{
    struct set_of_cubes
    {
        int red = 0;
        int green = 0;
        int blue = 0;

        set_of_cubes() = default;
        set_of_cubes(int r, int g, int b)
            : red(r), green(g), blue(b) {}
    };

    struct game
    {
        int id = 0;
        std::vector<set_of_cubes> sets;
    };
     
    using games = std::vector<game>;

    aoc::games read_input(const std::string& filename)
    {
        std::ifstream input_file(filename);
        std::regex input_regex(R"(\w+|;|:)");

        aoc::games games{};
        while (input_file)
        {
            std::string line;
            std::getline(input_file, line);

            if (line.empty()) continue;

            std::sregex_iterator begin{line.begin(), line.end(), input_regex};
            std::sregex_iterator end{};

            if (begin == end) continue;

            // Game
            games.emplace_back();
            auto& current_game = games.back();

            // id
            ++begin;
            current_game.id = std::stoi(begin->str());

            // :
            ++begin;
            assert(begin->str() == ":");
            current_game.sets.emplace_back();

            {
                ++begin;
                while (begin != end)
                {
                    if (begin->str() == ";")
                    {
                        current_game.sets.emplace_back();
                        current_game.sets.back() = current_game.sets.back();
                        ++begin;
                        continue;
                    }
                    
                    auto number_of_cubes = std::stoi(begin->str());
                    ++begin;

                    auto color = begin->str(); 
                    if (color == "red")
                    {
                        current_game.sets.back().red = number_of_cubes;
                    }
                    else if (color == "green")
                    {
                        current_game.sets.back().green = number_of_cubes;
                    }
                    else if (color == "blue")
                    {
                        current_game.sets.back().blue = number_of_cubes;
                    }
                    else
                    {
                        assert(("Unknown color", false));
                    }                    
                    ++begin;
                }
            }
        }
        
        return games;
    }
}

int main(int argc, char* argv[])
{
    aoc::games games = aoc::read_input("data/input.txt");

    int result = 0;
    for (auto& [id, cube_sets]: games)
    {
        auto max_red = std::ranges::max(
            cube_sets | std::views::transform([](const auto& cubes) { return cubes.red; }));
        auto max_green = std::ranges::max(
            cube_sets | std::views::transform([](const auto& cubes) { return cubes.green; }));
        auto max_blue = std::ranges::max(
            cube_sets | std::views::transform([](const auto& cubes) { return cubes.blue; }));

        int power = max_red * max_green * max_blue;
        result += power;
    }

    std::print(std::cout, "ANSWER: {}\n", result);
    
    return 0;
}
