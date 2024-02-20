#pragma once
#include <string>

namespace Token
{
    // Enumerators are suffixed with an underscore to avoid conflicts with C++ keywords
    enum class Type
    {
        // Special tokens
        eof_,
        newline_,
        number_,
        identifier_,
        string_,
        // Keywords
        label_,
        goto_,
        print_,
        input_,
        let_,
        if_,
        then_,
        endif_,
        while_,
        repeat_,
        endwhile_,
        // Operators
        eq_,
        plus_,
        minus_,
        mult_,
        div_,
        eqeq_,
        noteq_,
        lt_,
        lteq_,
        gt_,
        gteq_,
    };

    class Token
    {
    public:
        Type type;
        std::string value;

        [[nodiscard]] std::string type_as_string() const;
    };

    Type type_from_string(const std::string& str);
    bool is_keyword(Type type);
    bool is_comparison_operator(Type type);
}
