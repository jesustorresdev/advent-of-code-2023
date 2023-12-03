#include <cassert>

import std;

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
    aoc::set_of_cubes bag{12, 13, 14};

    int result = 0;
    for (auto& [id, cube_sets]: games)
    {
        auto valid_sets = cube_sets | std::views::filter([&bag](const auto& cubes)
        {
            return cubes.red <= bag.red && cubes.green <= bag.green && cubes.blue <= bag.blue;
        });

        if (std::ranges::distance(valid_sets) == cube_sets.size())
        {
            std::print(std::cout, "Game {} is valid\n", id);
            result += id;
        }
    }

    std::print(std::cout, "ANSWER: {}\n", result);
    
    return 0;
}
