#ifndef PRINT_H
#define PRINT_H

#include <iostream>

namespace detail {
    template <class First>
    void print_internal(std::ostream& os, const First& arg) {
        os << arg;
    }

    template <class First, class... Rest>
    void print_internal(std::ostream& os, const First& arg, const Rest&... args) {
        os << arg;
        print_internal(os, args...);
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

    template <class First>
    void printsn_internal(std::ostream& os, const First& arg) {
        os << arg << '\n';
    }

    template <class First, class... Rest>
    void printsn_internal(std::ostream& os, const First& arg, const Rest&... args) {
        os << arg << ' ';
        printn_internal(os, args...);
    }

    template <class Between, class Last, class First>
    void print_generic_internal(std::ostream& os, const Between& between_printed, const Last& last_printed, const First& arg) {
        os << arg << last_printed;
    }

    template <class Between, class Last, class First, class... Rest>
    void print_generic_internal(std::ostream& os, const Between& between_printed, const Last& last_printed, const First& arg, const Rest&... args) {
        os << arg << between_printed;
        print_generic_internal(os, between_printed, last_printed, args...);
    }

}

template <class... Rest>
void print(Rest... args) {
    detail::print_internal(std::cout, args...);
}

template <class... Rest>
void printn(Rest... args) {
    detail::printn_internal(std::cout, args...);
}

template <class... Rest>
void printsn(Rest... args) {
    detail::printsn_internal(std::cout, args...);
}

template <class Between, class Last, class... Rest>
void print_generic(const Between& between_printed, const Last& last_printed, Rest... args) {
    detail::print_generic_internal(std::cout, between_printed, last_printed, args...);
}

#endif // PRINT_H
