#include "vb2c/emitter.h"
#include <fstream>

void emitter::write_file() const
{
    std::ofstream file(output_path_);

    if (!file.is_open())
    {
        throw std::runtime_error("Failed to open file for writing.");
    }

    file << header_ << code_;
    file.close();
}

void emitter::emit(const std::string& code)
{
    code_ += code;
}

void emitter::emit_line(const std::string& code)
{
    code_ += code + "\n";
}

void emitter::emit_header_line(const std::string& code)
{
    header_ += code + "\n";
}

void emitter::header_prepend(const std::string& code)
{
    header_ = code + "\n" + header_;
}

std::string emitter::get_combined() const
{
    return header_ + code_;
}
