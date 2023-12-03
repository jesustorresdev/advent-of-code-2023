#include <cassert>

import std;

using namespace std::literals;

const std::vector digit_names = {
    "zero"sv, "one"sv, "two"sv, "three"sv, "four"sv,
    "five"sv, "six"sv, "seven"sv, "eight"sv, "nine"sv
};

int find_first_digit(const std::string_view str)
{
    for (auto it = str.begin(); it != str.end(); ++it)
    {
        if (std::isdigit(*it))
        {
            return *it - '0';
        }
            
        for (auto [index, digit]: digit_names | std::views::enumerate)
        {
            if (std::ranges::starts_with(it, str.end(), digit.begin(), digit.end()))
            {
                return static_cast<int>(index);
            }
        }
    }

    assert(("No digit found", false));
    return 0;
}

int find_last_digit(const std::string_view str)
{
    for (auto it = str.rbegin(); it != str.rend(); ++it)
    {
        if (std::isdigit(*it))
        {
            return *it - '0';
        }
            
        for (auto [index, digit]: digit_names | std::views::enumerate)
        {
            if (std::ranges::starts_with(it, str.rend(), digit.rbegin(), digit.rend()))
            {
                return static_cast<int>(index);
            }
        }
    }

    assert(("No digit found", false));
    return 0;
}

int main(int argc, char* argv[])
{
    std::ifstream input_file("data/input.txt");

    int sum = 0;
    while (input_file)
    {
        std::string line;
        std::getline(input_file, line);

        if (line.empty()) continue;

        int first = find_first_digit(line);
        int last = find_last_digit(line);

        int number = first * 10 + last;
        std::print(std::cout, "{}\n", number);

        sum += number;
    }

    std::print(std::cout, "ANSWER: {}\n", sum);
    
    return 0;
}
