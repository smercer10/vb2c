#pragma once
#include <string>

class emitter
{
public:
    explicit emitter(const std::string& filename)
        : filepath_{filename + ".c"}
    {
    }

    void write_file() const;
    void emit(const std::string& code);
    void emit_line(const std::string& code); // Same as emit, but adds a newline
    void emit_header_line(const std::string& code);
    void header_prepend(const std::string& code); // For adding conditional includes

private:
    const std::string filepath_; // The file to write to
    std::string code_;
    std::string header_; // Anything that needs to be added to the top of the file
};

