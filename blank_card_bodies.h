#ifndef STRINGS_H
#define STRINGS_H

#include <string>

inline std::string blank_card = R"(
 ---------
|r        |
|s        |
|         |
body
|         |
|        r|
|        s|
 ---------)";

inline std::string blank_card_body_royal = R"(|         |
|    r    |
|         |
|         |)";

inline std::string blank_card_body_1 = R"(|         |
|    s    |
|         |
|         |)";

inline std::string blank_card_body_2 = R"(|         |
|   s s   |
|         |
|         |)";

inline std::string blank_card_body_3 = R"(|         |
|   s s   |
|    s    |
|         |)";

inline std::string blank_card_body_4 = R"(|         |
|   s s   |
|   s s   |
|         |)";

inline std::string blank_card_body_5 = R"(|         |
|  s s s  |
|   s s   |
|         |)";

inline std::string blank_card_body_6 = R"(|         |
|  s s s  |
|  s s s  |
|         |)";

inline std::string blank_card_body_7 = R"(|   s s   |
|  s s s  |
|   s s   |
|         |)";

inline std::string blank_card_body_8 = R"(|   s s   |
|  s s s  |
|   s s   |
|    s    |)";

inline std::string blank_card_body_9 = R"(|   s s   |
|  s s s  |
|  s s s  |
|    s    |)";

inline std::string blank_card_body_10 = R"(|   s s   |
|  s s s  |
|  s s s  |
|   s s   |)";

#endif // STRINGS_H