#include <iostream>
#include "BigInt.hpp"
int main()
{
    // BigInt a(10, "19825072886297376093294460641399416807580174927113702623907667638483965014577259475218658892128279883381924"), b(10, "9999999999999999999999999999999999999999999999");
    // std::cout << (a / b).toString(10) << std::endl;
    // std::cout << a.toString(10) << std::endl;

    for (int a = 1000; a < 20000; ++a)
    {
        for (int b = 1; b < 50; ++b)
        {
            std::string a_str = std::to_string(a);
            std::string b_str = std::to_string(b);

            int res_int = a % b;

            BigInt a_bigint(10, a_str);
            BigInt b_bigint(10, b_str);

            BigInt res_bigint = a_bigint % b_bigint;

            if (std::to_string(res_int) != res_bigint.toString(10))
            {
                std::cout << res_int << " " << res_bigint.toString(10) << std::endl;
            }
        }
    }
}