#include <cassert>

import std;

namespace aoc
{
    struct symbol
    {
        char ch = '\0';
        int row = 0;
        int col = 0;

        symbol() = default;
        symbol(char ch, int row, int col)
            : ch(ch), row(row), col(col) {}
    };

    struct part_number
    {
        int id = 0;
        int first = 0;
        int last = 0;

        part_number() = default;
        part_number(int id, int first, int last)
            : id(id), first(first), last(last) {}
    };
    
    using symbol_list = std::vector<aoc::symbol>;
    using number_list = std::vector<std::vector<aoc::part_number>>;
    
    std::tuple<symbol_list, number_list> read_input(const std::string& filename)
    {
        aoc::symbol_list symbols;
        aoc::number_list numbers;

        std::ifstream input_file(filename);
        while (input_file)
        {
            std::string line;
            std::getline(input_file, line);

            if (line.empty()) continue;
            
            numbers.emplace_back();

            for (int i = 0; i < line.size(); ++i)
            {
                char ch = line[i];
                
                if (ch == '.') continue;
                
                if (std::ispunct(ch))
                {
                    symbols.emplace_back(ch, numbers.size() - 1, i);
                }
                else if (std::isdigit(ch))
                {
                    std::size_t number_size = 0;
                    int number = std::stoi(line.substr(i), &number_size);
                    
                    int first = i;
                    i += static_cast<int>(number_size) - 1;
                    
                    numbers.back().emplace_back(number, first, i);
                }
                else
                {
                    assert(("Character not recognized", false));
                }
            }
        }

        return {symbols, numbers};
    }
}

int main(int argc, char* argv[])
{
    auto [symbols, numbers] = aoc::read_input("data/input.txt");

    int sum = 0;
    for (auto& symbol : symbols)
    {
        if (symbol.ch != '*') continue;

        std::vector<int> gears;
        for (int row = symbol.row - 1; row <= symbol.row + 1; ++row)
        {
            for (auto& number: numbers[row])
            {
                if (symbol.col >= (number.first - 1) && symbol.col <= (number.last + 1))
                {
                    gears.push_back(number.id);
                }
            }
        }

        if (gears.size() == 2)
        {
            sum += gears[0] * gears[1];
        }
    }

    std::print(std::cout, "ANSWER: {}\n", sum);
    
    return 0;
}
