//
// Created by vadim on 11.05.2021.
//

#include "randomstrings.h"

const char charset[] = "   !#$%&\'()*+,-./"
                       "0123456789"
                       ":;<=>?@"
                       "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                       "[\\]^_`"
                       "abcdefghijklmnopqrstuvwxyz"
                       "{|}~";

const size_t max_index = sizeof(charset) / sizeof(*charset) - 2;
const size_t letter_size = sizeof(char);

// Generate random string of the size length
std::string generate_random_string(size_t length) {

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, max_index);

    std::string str;
    str.reserve(length);
    std::generate_n(std::back_inserter(str), length,
                    [&]() { return charset[dist(gen)]; });
    return str;
}

void generate_random_blocks(size_t S_LEN, size_t N_STRS) {

    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<> dist(0, max_index);

    std::vector<std::string> strs;
    strs.reserve(N_STRS);
    std::generate_n(std::back_inserter(strs), strs.capacity(),
                    [&] {
                        std::string str;
                        str.reserve(S_LEN);
                        std::generate_n(std::back_inserter(str), S_LEN,
                                        [&]() { return charset[dist(rng)]; });
                        return str;
                    });
    std::copy(strs.begin(), strs.end(),
              std::ostream_iterator<std::string>(std::cout, "\n"));
}

// Generates a text of at least size MEMORY_BOUND bytes from strings of maximum size S_LEN
void generate_bounded(size_t S_LEN, size_t MEMORY_BOUND) {

    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<> dist(0, S_LEN);

    size_t memory_used = 0;

    while (memory_used <= MEMORY_BOUND) {
        size_t current_lines = dist(rng);
        std::string current_string = generate_random_string(current_lines);
        std::cout << current_string << '\n';
        memory_used += current_string.size() + 1;
    }
}

// Generates random N_STRS random strings of the maximum size of S_LEN
void generate_spaghetti_strings(size_t S_LEN, size_t N_STRS) {

    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<> dist(0, max_index);

    std::random_device string_generator;
    std::mt19937 string_random(string_generator());
    std::uniform_int_distribution<> dist_string(1, S_LEN);

    std::vector<std::string> strs;
    strs.reserve(N_STRS);
    std::generate_n(std::back_inserter(strs), strs.capacity(),
                    [&] {
                        std::string str;
                        size_t current_length = dist_string(string_random);
                        str.reserve(current_length);
                        std::generate_n(std::back_inserter(str), current_length,
                                        [&]() { return charset[dist(rng)]; });
                        return str;
                    });
    std::copy(strs.begin(), strs.end(),
              std::ostream_iterator<std::string>(std::cout, "\n"));
}
// Generates random N_STRS random strings of the maximum size of S_LEN
// but saves it to the buffer of the size MEMORY_BOUND before writing every chunk
void generate_spaghetti_strings_bounded(size_t S_LEN, size_t N_STRS, size_t MEMORY_BOUND) {

    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<> dist(0, max_index);

    std::random_device string_generator;
    std::mt19937 string_random(string_generator());
    std::uniform_int_distribution<> dist_string(1, S_LEN);


    size_t chunk = 0;
    while (chunk < N_STRS) {

        std::vector<std::string> strs;
        strs.clear();

        if ((N_STRS - chunk) < MEMORY_BOUND / (letter_size * S_LEN)) {
            strs.reserve(N_STRS - chunk);
        }
        else {
            strs.reserve(MEMORY_BOUND / (letter_size * S_LEN));
        }

        std::generate_n(std::back_inserter(strs), strs.capacity(),
                        [&] {
                            std::string str;
                            size_t current_length = dist_string(string_random);
                            str.reserve(current_length);
                            std::generate_n(std::back_inserter(str), current_length,
                                            [&]() { return charset[dist(rng)]; });
                            return str;
                        });
        chunk += strs.size();
        std::copy(strs.begin(), strs.end(),
                  std::ostream_iterator<std::string>(std::cout, "\n"));
    }
}