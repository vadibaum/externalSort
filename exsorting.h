//
// Created by vadim on 11.05.2021.
//

#ifndef EXTERNALSORT_EXSORTING_H
#define EXTERNALSORT_EXSORTING_H

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <queue>

void write_chunk(std::vector<std::string> &data, unsigned int &numberChunks,
                 std::ofstream &output, const std::string &stamp) ;

size_t process_input(const std::string & input_name, const std::string & stamp, size_t memoryLimit) ;

void merge(size_t numberChunks, const std::string & stamp, const std::string & output_name);
void clear_chunks(size_t numberChunks, const std::string &stamp) ;

#endif //EXTERNALSORT_EXSORTING_H
