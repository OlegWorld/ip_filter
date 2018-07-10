#include <iostream>
#include "gtest/gtest.h"
#include "ip_filter.h"

TEST(parse_ip_test, parsing_ip)
{
    ip_address ip;
    EXPECT_NO_THROW(ip = parse_ip("192.168.0.1"));

    ip_address ref = {192, 168, 0, 1};
    EXPECT_EQ(ip, ref);
}

TEST(parse_ip_test, parsing_bugged_ip_short)
{
    EXPECT_THROW(parse_ip("192.168.0"), ip_parser_error);
}

TEST(parse_ip_test, parsing_wrong_data)
{
    EXPECT_THROW(parse_ip("Not an ip"), std::invalid_argument);
}

TEST(filter_test, filter_first_byte)
{
    ip_vector v;

    v.emplace_back(parse_ip("192.168.0.1"));
    v.emplace_back(parse_ip("192.168.0.1"));
    v.emplace_back(parse_ip("192.168.0.1"));
    v.emplace_back(parse_ip("192.168.0.1"));
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
