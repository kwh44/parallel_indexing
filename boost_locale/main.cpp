#include <boost/locale.hpp>
#include <boost/locale/conversion.hpp>
#include <iostream>
#include <boost/locale/generator.hpp>

using namespace boost::locale;

int main() {
    std::cout << "I am here\n";
    generator gen;
    auto loc = gen("en_US.UTF-8");
    std::string text{"Building CXX object"};
    std::cout << text << std::endl;
    auto normalized_text = boost::locale::fold_case(
            boost::locale::normalize(text, boost::locale::norm_type::norm_default, gen("en_US.UTF-8")));

    /*
    std::locale::global(gen("en_US.UTF-8"));
    std::wstring a = L"Façade", b = L"façade";
    bool eq = 0 == std::use_facet<collator<wchar_t> >(loc).compare(collator_base::secondary, a, b);
    std::wcout << a << L" and " << b << L" are " << (eq ? L"identical" : L"different") << std::endl;
    std::cout << boost::locale::as::spellout;
    std::cout << 22 << std::endl;
    */

    return 0;
}