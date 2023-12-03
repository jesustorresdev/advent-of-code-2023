import std;
#include <cassert>

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
    auto [symbols, numbers] = aoc::read_input("data/test2.txt");

    std::set<int> valid_numbers;
    for (auto& symbol : symbols)
    {
        valid_numbers.insert_range(
            numbers[symbol.row]
                | std::views::filter([&symbol](auto& number)
                    { return symbol.col == (number.first - 1) || symbol.col == (number.last + 1); })
                | std::views::transform([](auto& number) { return number.id; }));
        
        // Check prev row
        if (symbol.row > 0)
        {
            valid_numbers.insert_range(
                numbers[symbol.row - 1]
                    | std::views::filter([&symbol](auto& number)
                        { return symbol.col >= (number.first - 1) && symbol.col <= (number.last + 1); })
                    | std::views::transform([](auto& number) { return number.id; }));
        }

        // Check next row
        if (symbol.row < numbers.size() - 1)
        {
            valid_numbers.insert_range(
                numbers[symbol.row + 1]
                    | std::views::filter([&symbol](auto& number)
                        { return symbol.col >= (number.first - 1) && symbol.col <= (number.last + 1); })
                    | std::views::transform([](auto& number) { return number.id; }));
        }
    }

    int sum = std::accumulate(valid_numbers.begin(), valid_numbers.end(), 0);
    std::print(std::cout, "ANSWER: {}\n", sum);
    
    return 0;
}
