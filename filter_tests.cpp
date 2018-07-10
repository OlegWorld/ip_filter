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
    v.emplace_back(parse_ip("192.165.6.4"));
    v.emplace_back(parse_ip("193.168.0.1"));
    v.emplace_back(parse_ip("191.168.0.1"));

    v = filter(v, 192);

    ip_address ref1 = {192, 168, 0, 1};
    ip_address ref2 = {192, 165, 6, 4};
    EXPECT_EQ(v.size(), 2);
    EXPECT_EQ(v[0], ref1);
    EXPECT_EQ(v[1], ref2);
}

TEST(filter_test, filter_first_n_second_byte)
{
    ip_vector v;

    v.emplace_back(parse_ip("192.168.0.1"));
    v.emplace_back(parse_ip("192.165.6.4"));
    v.emplace_back(parse_ip("193.168.0.1"));
    v.emplace_back(parse_ip("191.168.0.1"));
    v.emplace_back(parse_ip("192.168.76.43"));

    v = filter(v, 192, 168);

    ip_address ref1 = {192, 168, 0, 1};
    ip_address ref2 = {192, 168, 76, 43};
    EXPECT_EQ(v.size(), 2);
    EXPECT_EQ(v[0], ref1);
    EXPECT_EQ(v[1], ref2);
}

TEST(filter_any_test, filter_any)
{
    ip_vector v;

    v.emplace_back(parse_ip("192.168.0.1"));
    v.emplace_back(parse_ip("192.165.6.4"));
    v.emplace_back(parse_ip("193.6.0.1"));
    v.emplace_back(parse_ip("191.168.0.1"));
    v.emplace_back(parse_ip("192.1.76.43"));
    v.emplace_back(parse_ip("6.168.0.1"));
    v.emplace_back(parse_ip("56.67.0.5"));
    v.emplace_back(parse_ip("191.168.0.6"));
    v.emplace_back(parse_ip("56.15.0.1"));

    v = filter_any(v, 6);

    ip_address ref1 = {192, 165, 6, 4};
    ip_address ref2 = {193, 6, 0, 1};
    ip_address ref3 = {6, 168, 0, 1};
    ip_address ref4 = {191, 168, 0, 6};
    EXPECT_EQ(v.size(), 4);
    EXPECT_EQ(v[0], ref1);
    EXPECT_EQ(v[1], ref2);
    EXPECT_EQ(v[2], ref3);
    EXPECT_EQ(v[3], ref4);
}

TEST(print_test, nothrow_test)
{
    ip_vector v;

    v.emplace_back(parse_ip("192.168.0.1"));
    v.emplace_back(parse_ip("192.165.6.4"));
    v.emplace_back(parse_ip("193.6.0.1"));
    v.emplace_back(parse_ip("191.168.0.1"));
    v.emplace_back(parse_ip("192.1.76.43"));
    v.emplace_back(parse_ip("6.168.0.1"));
    v.emplace_back(parse_ip("56.67.0.5"));
    v.emplace_back(parse_ip("191.168.0.6"));
    v.emplace_back(parse_ip("56.15.0.1"));

    EXPECT_NO_THROW(print_ip_pool(v));
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
