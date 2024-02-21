#pragma once
#include <string>
#include <utility>

class emitter
{
public:
    explicit emitter(std::string output_path)
        : output_path_{std::move(output_path)}
    {
    }

    void write_file() const;
    void emit(const std::string& code);
    void emit_line(const std::string& code); // Same as emit, but adds a newline
    void emit_header_line(const std::string& code);
    void header_prepend(const std::string& code); // For adding conditional includes

private:
    const std::string output_path_;
    std::string code_;
    std::string header_; // Anything that needs to be added to the top of the file
};

