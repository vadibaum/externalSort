//
// Created by vadim on 11.05.2021.
//

#ifndef EXTERNALSORT_RANDOMSTRINGS_H
#define EXTERNALSORT_RANDOMSTRINGS_H

#include <random>
#include<string>
#include <iostream>
#include <iterator>
#include <vector>

std::string generate_random_string(size_t length);
void generate_spaghetti_strings(size_t S_LEN, size_t N_STRS) ;
void generate_random_blocks(size_t S_LEN, size_t N_STRS) ;
void generate_spaghetti_strings_bounded(size_t S_LEN, size_t N_STRS, size_t MEMORY_BOUND) ;
void generate_bounded(size_t S_LEN, size_t MEMORY_BOUND) ;

#endif //EXTERNALSORT_RANDOMSTRINGS_H
