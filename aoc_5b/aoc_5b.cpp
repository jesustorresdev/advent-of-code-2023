import std;

// We use epsilon to offset the max_t and min_t when the solution is exactly on the edge
constexpr double EPSILON = 0.0001f;

int main(int argc, char* argv[])
{
    std::ifstream input_file("data/input.txt");

    std::string time_line;
    std::getline(input_file, time_line);

    std::string distance_line;
    std::getline(input_file, distance_line);
    
    auto time_digits = time_line
        | std::views::filter([](char& c) { return !std::isspace(c); })
        | std::views::drop_while([](char& c) { return c != ':'; })
        | std::views::drop(1);
    
    auto t = std::stod(std::string{time_digits.begin(), time_digits.end()});
    
    auto distance_digits = distance_line
        | std::views::filter([](char& c) { return !std::isspace(c); })
        | std::views::drop_while([](char& c) { return c != ':'; })
        | std::views::drop(1);

    auto d = std::stod(std::string{distance_digits.begin(), distance_digits.end()});
    
    // Quadratic formula
    double common = std::sqrt(t*t - 4.0f*d) / 2.0f;
    int max_t = static_cast<int>(std::floor(t / 2.0f + common - EPSILON));
    int min_t = static_cast<int>(std::ceil(t / 2.0f - common + EPSILON));
    
    int result = max_t - min_t + 1;
    std::print(std::cout, "ANSWER: {}\n", result);
    
    return 0;
}
