#include <iostream>
#include <string>
#include <boost/locale/generator.hpp>
#include <boost/locale.hpp>

int main() {
    boost::locale::generator gen;
    std::locale::global(gen("en_us.UTF-8"));
    std::string text = "paralleO GRÜSSEN InDexing";
    auto normalized_text = boost::locale::fold_case(
            boost::locale::normalize(text));
    std::cout << normalized_text << std::endl;
    return 0;
}