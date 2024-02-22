#pragma once
#include <string>

namespace token
{
    // A tkn prefix is used to avoid conflict with C++ keywords
    enum class tkn_type
    {
        // Special tokens
        tkn_eof,
        tkn_newline,
        tkn_number,
        tkn_identifier,
        tkn_string,
        // Keywords
        tkn_label,
        tkn_goto,
        tkn_print,
        tkn_input,
        tkn_let,
        tkn_if,
        tkn_then,
        tkn_endif,
        tkn_while,
        tkn_repeat,
        tkn_endwhile,
        // Operators
        tkn_eq,
        tkn_plus,
        tkn_minus,
        tkn_mult,
        tkn_div,
        tkn_eqeq,
        tkn_noteq,
        tkn_lt,
        tkn_lteq,
        tkn_gt,
        tkn_gteq,
    };

    class token
    {
    public:
        tkn_type type;
        std::string value;

        [[nodiscard]] std::string type_as_string() const;
    };

    tkn_type type_from_string(const std::string &str);
    bool is_keyword(tkn_type type);
    bool is_comparison_op(tkn_type type);
} // namespace token
