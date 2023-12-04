import std;

using namespace std::literals;

int to_int(const std::string_view str) {
    int value = 0;
    std::from_chars(str.data(), str.data() + str.size(), value);
    return value;
};

void update_won_cards(std::vector<int>& won_cards, int current_card, int num_of_won_cards)
{
    for (int next_card = current_card; next_card <= current_card + num_of_won_cards; ++next_card)
    {
        if (next_card >= won_cards.size())
        {
            won_cards.push_back(next_card == current_card ? 1 : won_cards[current_card]);
        }
        else
        {
            won_cards[next_card] += next_card == current_card ? 1 : won_cards[current_card];
        }
    }
}

int main(int argc, char* argv[])
{
    std::ifstream input_file("data/input.txt");
    std::vector<int> won_cards; 

    int card_id = 0;
    for (card_id = 0; input_file; ++card_id)
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
        
        update_won_cards(won_cards, card_id, num_of);
    }

    won_cards.resize(card_id);
    int result = std::accumulate(won_cards.begin(), won_cards.end(), 0);
    
    std::print(std::cout, "ANSWER: {}\n", result);
    
    return 0;
}
