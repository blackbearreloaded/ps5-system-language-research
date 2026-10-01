#include "ps5_system_language.hpp"

#include <cassert>

int main()
{
    using ps5::i18n::language_tag;

    assert(language_tag(0) == "ja-JP");
    assert(language_tag(10) == "zh-Hant");
    assert(language_tag(11) == "zh-Hans");
    assert(language_tag(30) == "uk-UA");
    assert(language_tag(-1) == "en-US");
    assert(language_tag(31) == "en-US");
}
