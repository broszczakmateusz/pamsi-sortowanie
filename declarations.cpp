//
// Created by root on 13.03.2021.
//
#include "Array.cpp"
#include "size.h"
#include "Array.h"



template class Array<int, SIZE>;
template std::ostream& operator << (std::ostream & Strm, const Array<int, SIZE> & Arr);

