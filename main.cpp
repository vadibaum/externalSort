#include <iostream>
#include <random>
#include "randomstrings.h"
#include "exsorting.h"

const std::string HELP =
        "-h --help\n"
        "Shows this.\n\n"
        "-v --validate\n"
        "Checks whatever the file is sorted line by line.\n\n"
        "-g --generate NLENGTH NLINES\n"
        "Generates a random text file with NLINES lines, each line has a random length with a maximum of NLENGTH.\n"
        "(!) writes every new line to output, slower\n\n"
        "-bg --blockgenerate S_LEN N_STRS\n"
        "Generates a text file with N_STRS lines, each line has a length of S_LEN.\n\n"
        "-sg --spaghettigenerate S_LEN N_STRS\n"
        "Generates a text file with N_STRS lines, each line has a random length with a maximum S_LEN.\n\n"
        "-sb --boundedgenerate S_LEN N_STRS MEMORY_BOUND\n"
        "Generates a text file with N_STRS lines, each line has a random length with a maximum S_LEN.\n"
        "saves strings to a buffer of the size MEMORY_BOUND (default value 19MB)\n\n"
        "-b --bitgenerate S_LEN LIMIT\n"
        "Generates with size greater than LIMIT, random strings with a maximum size S_LEN.\n"
        "(!) writes every new line to output, slower\n\n"
        "-s --sort INPUT OUTPUT SIZE\n"
        "Sorts INPUT file using an external search by splitting it to chunks of the SIZE, writes a result to output.\n"
        ;

int main(int argc, const char *argv[]) {
    if (!strcmp(argv[1], "-h") || !strcmp(argv[1], "--help")) {
        std::cout << HELP << std::endl;
    }

    else if (!strcmp(argv[1], "-g") || !strcmp(argv[1], "--generate")) {

        size_t nlength = std::stoi(argv[2]);
        size_t nlines = std::stoi(argv[3]);

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<size_t> dist(1, nlength);

        for (int n = 0; n < nlines; n++) {
            size_t current_length = dist(gen);
            std::cout << generate_random_string(current_length);
            std::cout << '\n';
        }
    }

    if (!strcmp(argv[1], "-bg") || !strcmp(argv[1], "--blockgenerate")) {

        static const size_t S_LEN = std::stoi(argv[2]);;
        static const size_t N_STRS = std::stoi(argv[3]);;

        generate_random_blocks(S_LEN, N_STRS);
    }

    else if (!strcmp(argv[1], "-sg") || !strcmp(argv[1], "--spaghettigenerate")) {
        static const size_t S_LEN = std::stoi(argv[2]);;
        static const size_t N_STRS = std::stoi(argv[3]);;

        generate_spaghetti_strings(S_LEN, N_STRS);
    }

    else if (!strcmp(argv[1], "-sb") || !strcmp(argv[1], "--boundedgenerate")) {
        static const size_t S_LEN = std::stoi(argv[2]);;
        static const size_t N_STRS = std::stoi(argv[3]);;
        static const size_t MEMORY_BOUND = std::stoi(argv[4]);

        generate_spaghetti_strings_bounded(S_LEN, N_STRS, MEMORY_BOUND);
    }

    else if (!strcmp(argv[1], "-b") || !strcmp(argv[1], "--bitgenerate")) {
        static const size_t S_LEN = std::stoi(argv[2]);;
        static const size_t MEMORY_BOUND = std::stoi(argv[3]);

        generate_bounded(S_LEN, MEMORY_BOUND);
    }

    else if (!strcmp(argv[1], "-v") || !strcmp(argv[1], "--validate")) {

        std::string input_name = std::string(argv[2]);

        std::ifstream input_file;

        input_file.open(input_name.c_str());

        size_t line_num = 0;

        std::string previous;
        if (!std::getline(input_file, previous))
            std::cout << "Empty file" << std::endl;
        else
            for (std::string line; std::getline(input_file, line);) {
                if (line >= previous) {
                    previous = line;
                    line_num++;
                }
                else {
                    std::cout << "Break on the line " << line_num << std::endl;
                    return 0;
                }
            }

        std::cout << "The file is sorted." << std::endl;
    }

    else if (!strcmp(argv[1], "-s") || !strcmp(argv[1], "--sort")) {

        std::string input_file = std::string(argv[2]);
        std::string output_file = std::string(argv[3]);
        size_t nbytes = std::stoi(argv[4]);

        // stamps are used to identification of the chunks from particular run
        std::time_t t = std::time(nullptr);
        std::tm tm = *std::localtime(&t);
        std::ostringstream oss;
        oss << std::put_time(&tm, "%d%m%Y%H%M%S");
        std::string hash = oss.str();

        size_t nchunks = process_input(input_file, hash, nbytes);
        merge(nchunks, hash, output_file);
        clear_chunks(nchunks, hash);

    }

    else {
        std::cout << HELP << std::endl;
        return 1;
    }

    return 0;
}
