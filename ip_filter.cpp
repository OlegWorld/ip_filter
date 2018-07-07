#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <tuple>

// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]
using ip_vector = std::vector<std::vector<uint8_t>>;

std::vector<uint8_t > split(const std::string& str, char d)
{
    std::vector<uint8_t> r;
    r.reserve(4);

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while(stop != std::string::npos)
    {
        r.emplace_back(stoul(str.substr(start, stop - start)));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.emplace_back(stoul(str.substr(start)));

    return r;
}

ip_vector filter(const ip_vector& ip_pool, uint8_t value)
{
    ip_vector pool;
    for (const auto& ip : ip_pool)
        if (ip[0] == value)
            pool.push_back(ip);

    return pool;
}

ip_vector filter(const ip_vector& ip_pool, uint8_t value1, uint8_t value2)
{
    ip_vector pool;
    for (const auto& ip : ip_pool)
        if (ip[0] == value1 && ip[1] == value2)
            pool.push_back(ip);

    return pool;
}

ip_vector filter_any(const ip_vector& ip_pool, uint8_t value)
{
    ip_vector pool;
    for (const auto& ip : ip_pool)
        if (std::any_of(ip.begin(), ip.end(), [value](const auto& byte){ return byte == value; }))
            pool.push_back(ip);

    return pool;
}

void print(const ip_vector& ip_pool)
{
    for(const auto& ip : ip_pool)
    {
        for(const auto& ip_part : ip)
        {
            std::cout << unsigned(ip_part);

            if (ip_part != ip.back())
                std::cout << ".";
        }
        std::cout << std::endl;
    }
}

int main(int argc, char const *argv[])
{
    try
    {
        ip_vector ip_pool;

        for(std::string line; std::getline(std::cin, line);)
        {
            line.resize(line.find_first_of('\t'));

            ip_pool.emplace_back(split(line, '.'));
        }

        std::sort(ip_pool.begin(), ip_pool.end(), [](const auto& lhs, const auto& rhs) {
            return std::tie(lhs[0], lhs[1], lhs[2], lhs[3]) >= std::tie(rhs[0], rhs[1], rhs[2], rhs[3]);
        });

        print(ip_pool);

        auto v = filter(ip_pool, 1);
        print(v);

        v = filter(ip_pool, 46, 70);
        print(v);

        v = filter_any(ip_pool, 46);
        print(v);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
