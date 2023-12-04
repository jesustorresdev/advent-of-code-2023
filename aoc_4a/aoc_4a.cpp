import std;

using namespace std::literals;

int to_int(const std::string_view str) {
    int value = 0;
    std::from_chars(str.data(), str.data() + str.size(), value);
    return value;
};

int main(int argc, char* argv[])
{
    std::ifstream input_file("data/input.txt");

    int result = 0;
    while (input_file)
    {
        std::string line;
        std::getline(input_file, line);

        if (line.empty()) continue;

        auto to_int = [](auto&& str) {
            int value = 0;
            std::from_chars(str.data(), str.data() + str.size(), value);
            return value;
        };

        auto parts = line
            | std::views::split(' ')
            | std::views::filter([](auto&& part) { return !part.empty(); })
            | std::views::drop(2);
        
        auto winning_numbers = parts
            | std::views::take_while([](auto&& part) { return std::string_view(part) != "|"sv; })
            | std::views::transform(to_int);
            
        auto numbers = parts
            | std::views::drop_while([](auto&& part) { return std::string_view(part) != "|"sv; })
            | std::views::drop(1)
            | std::views::transform(to_int);

        int num_of = std::ranges::distance(winning_numbers | std::views::filter([&numbers](auto&& winnum)
        {
            return std::ranges::contains(numbers, winnum);
        }));
        
        result += std::pow(2, num_of - 1);
    }

    std::print(std::cout, "ANSWER: {}\n", result);
    
    return 0;
}
