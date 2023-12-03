import std;

int main(int argc, char* argv[])
{
    std::ifstream input_file("data/input.txt");

    int sum = 0;
    while (input_file)
    {
        std::string line;
        std::getline(input_file, line);

        if (line.empty()) continue;
        
        auto sequence = line
            | std::views::filter([](const char c) { return std::isdigit(c); })
            | std::views::transform([](const char c) { return c - '0'; });

        int number = sequence.front() * 10 + sequence.back();
        std::print(std::cout, "{}\n", number);

        sum += number;
    }

    std::print(std::cout, "ANSWER: {}\n", sum);
    
    return 0;
}
