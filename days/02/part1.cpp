#include <iostream>
#include <stdexcept>
#include <ranges>
#include <cstdint>
#include <regex>

const std::regex game_regex("Game (\\d+): (.*)");
const std::regex draw_regex("(\\d+) (red|green|blue)");

bool is_game_valid(const std::string draws){
    for(const auto& draw : draws | std::views::split(';')){
        for(auto match_ptr = std::sregex_iterator(draw.begin(), draw.end(), draw_regex);
            match_ptr != std::sregex_iterator();
            match_ptr++
        ){
            const auto match = *match_ptr;
            const uint32_t number = std::stoi(match[1]);
            const auto color = match[2].str();
            if(
                (color == "red" && number > 12) ||
                (color == "green" && number > 13) ||
                (color == "blue" && number > 14)
            )
                return false;
        }
    }
    return true;
}

int main(int argc, char**argv){
    uint32_t sum = 0;
    std::smatch match;
    for(std::string line; std::getline(std::cin, line);)
        if(std::regex_match(line, match, game_regex)){
            if(is_game_valid(match[2]))
                sum += std::stoi(match[1]);
        }else
            throw std::runtime_error("Incompatible format");
    

    std::cout << sum << std::endl;
    return 0;
}