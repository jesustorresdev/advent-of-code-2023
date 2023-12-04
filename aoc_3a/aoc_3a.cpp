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
        bool already_valid = false;

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

            for (auto i = 0; i < line.size(); ++i)
            {
                char ch = line[i];
                
                if (ch == '.') continue;
                
                if (std::ispunct(ch))
                {
                    int row = static_cast<int>(numbers.size() - 1);
                    symbols.emplace_back(ch, row, i);
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

    std::vector<int> valid_numbers;
    for (auto& symbol : symbols)
    {
        assert(symbol.row != 0 && symbol.row != numbers.size() - 1);
        
        for (int row = symbol.row - 1; row <= symbol.row + 1; ++row)
        {
            for (auto& number: numbers[row])
            {
                if (!number.already_valid && (symbol.col >= (number.first - 1) && symbol.col <= (number.last + 1)))
                {
                    number.already_valid = true;
                    valid_numbers.push_back(number.id);
                }
            }
        }
    }

    int sum = std::accumulate(valid_numbers.begin(), valid_numbers.end(), 0);
    std::print(std::cout, "ANSWER: {}\n", sum);
    
    return 0;
}
