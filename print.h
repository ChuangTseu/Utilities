#ifndef PRINT_H
#define PRINT_H

#include <iostream>

template <class First>
void print_internal(std::ostream& os, const First& arg) {
    os << arg;
}

template <class First, class... Rest>
void print_internal(std::ostream& os, const First& arg, const Rest&... args) {
    os << arg;
    print_internal(os, args...);
}

template <class... Rest>
void print(Rest... args) {
    print_internal(std::cout, args...);
}

template <class First>
void printn_internal(std::ostream& os, const First& arg) {
    os << arg << '\n';
}

template <class First, class... Rest>
void printn_internal(std::ostream& os, const First& arg, const Rest&... args) {
    os << arg;
    printn_internal(os, args...);
}

template <class... Rest>
void printn(Rest... args) {
    printn_internal(std::cout, args...);
}

#endif // PRINT_H
