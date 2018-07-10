#include "ip_filter.h"

int main()
{
    ip_vector ip_pool;

    try
    {
        for(std::string line; std::getline(std::cin, line);)
        {
            line.resize(line.find_first_of('\t'));

            ip_pool.emplace_back(parse_ip(line));
        }

        std::sort(ip_pool.begin(), ip_pool.end(), [](const auto& lhs, const auto& rhs) {
            return std::tie(lhs[0], lhs[1], lhs[2], lhs[3]) >= std::tie(rhs[0], rhs[1], rhs[2], rhs[3]);
        });

        print_ip_pool(ip_pool);

        print_ip_pool(filter(ip_pool, 1));

        print_ip_pool(filter(ip_pool, 46, 70));

        print_ip_pool(filter_any(ip_pool, 46));
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
