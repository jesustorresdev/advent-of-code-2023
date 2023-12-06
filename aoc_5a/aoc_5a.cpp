import std;

// We use epsilon to offset the max_t and min_t when the solution is exactly on the edge
constexpr double EPSILON = 0.0001f;

int main(int argc, char* argv[])
{
    std::ifstream input_file("data/input.txt");
 
    auto to_int = [](auto&& str)
    {
        int value;
        std::from_chars(str.data(), str.data() + str.size(), value);
        return value;
    };

    std::string time_line;
    std::getline(input_file, time_line);

    std::string distance_line;
    std::getline(input_file, distance_line);
    
    auto times = time_line | std::views::split(' ')
         | std::views::filter([](auto&& num) { return !num.empty(); })
         | std::views::drop(1)
         | std::views::transform(to_int) ;
    
    auto distances = distance_line | std::views::split(' ')
         | std::views::filter([](auto&& num) { return !num.empty(); })
         | std::views::drop(1)
         | std::views::transform(to_int);

    auto choices = std::views::zip(times, distances) | std::views::transform([](auto&& pair)
    {
        auto [t, d] = pair;
        // Quadratic formula
        double common = std::sqrt(t*t - 4.0f*d) / 2.0f;
        int max_t = static_cast<int>(std::floor(t / 2.0f + common - EPSILON));
        int min_t = static_cast<int>(std::ceil(t / 2.0f - common + EPSILON));

        return max_t - min_t + 1;
    });

    int result = std::accumulate(choices.begin(), choices.end(), 1, std::multiplies<int>());
    
    std::print(std::cout, "ANSWER: {}\n", result);
    
    return 0;
}
