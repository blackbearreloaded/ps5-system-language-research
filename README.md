# PS5 System Language Research

Independent documentation and minimal C++ code for detecting the language selected in PlayStation 5 system settings from a homebrew application.

## Quick start

Include [`include/ps5_system_language.hpp`](include/ps5_system_language.hpp), link the PS5 Payload SDK's `SceSystemService` stub, and call:

```cpp
const std::string_view locale = ps5::i18n::current_language_tag();
```

For a `prospero.mk` project, add the library to the existing link list:

```make
LDADD += -lSceSystemService
```

The header calls:

```cpp
sceSystemServiceParamGetInt(1, &language);
```

Parameter ID `1` requests the system language. The function returns `0` on success and writes the selected language ID to `language`. The helper returns `en-US` if the call fails or the firmware returns an unknown value.

## Language IDs

| ID | System language | BCP 47 tag |
|---:|---|---|
| 0 | Japanese | `ja-JP` |
| 1 | English (United States) | `en-US` |
| 2 | French (France) | `fr-FR` |
| 3 | Spanish (Spain) | `es-ES` |
| 4 | German | `de-DE` |
| 5 | Italian | `it-IT` |
| 6 | Dutch | `nl-NL` |
| 7 | Portuguese (Portugal) | `pt-PT` |
| 8 | Russian | `ru-RU` |
| 9 | Korean | `ko-KR` |
| 10 | Chinese (Traditional) | `zh-Hant` |
| 11 | Chinese (Simplified) | `zh-Hans` |
| 12 | Finnish | `fi-FI` |
| 13 | Swedish | `sv-SE` |
| 14 | Danish | `da-DK` |
| 15 | Norwegian | `nb-NO` |
| 16 | Polish | `pl-PL` |
| 17 | Portuguese (Brazil) | `pt-BR` |
| 18 | English (United Kingdom) | `en-GB` |
| 19 | Turkish | `tr-TR` |
| 20 | Spanish (Latin America) | `es-419` |
| 21 | Arabic | `ar` |
| 22 | French (Canada) | `fr-CA` |
| 23 | Czech | `cs-CZ` |
| 24 | Hungarian | `hu-HU` |
| 25 | Greek | `el-GR` |
| 26 | Romanian | `ro-RO` |
| 27 | Thai | `th-TH` |
| 28 | Vietnamese | `vi-VN` |
| 29 | Indonesian | `id-ID` |
| 30 | Ukrainian | `uk-UA` |

Values `0` through `29` follow the established SystemService ABI. Value `30` is community-documented and should be verified on the target firmware. Applications must retain an unknown-value fallback because later firmware may add values.

## Loading translations

Keep the platform lookup separate from the application's translation fallback rules:

```cpp
const auto locale = ps5::i18n::current_language_tag();

if (!load_translations(locale))
    load_translations("en-US");
```

Applications supporting fewer regions can deliberately collapse tags. For example, `en-US` and `en-GB` may both load an `en` resource, while `zh-Hans` and `zh-Hant` should normally remain distinct.

## Evidence and scope

- [`sceSystemServiceParamGetInt`](https://github.com/MaxMilu/ps5-direct-package-installer/blob/main/source/main.cpp) with parameter ID `1` has been used by PS5 homebrew tested on physical firmware 5.50; that implementation also uses IDs `10` and `11` for Traditional and Simplified Chinese.
- The [`OrbisSystemParamLanguage`](https://github.com/OpenOrbis/OpenOrbis-PS4-Toolchain/blob/master/include/orbis/_types/sys_service.h) definitions document the stable values `0` through `29` inherited by the interface.
- The community [`LibSceSystemService` language table](https://github.com/shadps4-emu/shadPS4/wiki/PS4-Modules/fce2cf380098958e3f720c6cc6b3b34795e77f5b) records Ukrainian as value `30`, but labels it unverified.

This repository documents a narrow compatibility technique. It does not claim that every listed language was tested on every PS5 firmware.

## Repository boundary

This repository intentionally contains no Sony SDK files, firmware images, decrypted system modules, decompiled proprietary code, symbol databases, credentials, exploits, or access-control bypass instructions.

## Disclaimer

This is an independent homebrew research project and is not affiliated with or endorsed by Sony Interactive Entertainment. PlayStation and PS5 are trademarks of Sony Interactive Entertainment Inc. Use homebrew only on hardware and content you own and accept the risks of modified-console software.

