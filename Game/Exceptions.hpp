#pragma once

#include <exception>
#include <string>

class load_exception : public std::exception {
private:
    std::string error;

public:
    load_exception(const std::string& type, const std::string& name, const std::string& filename) :
        error{ "Error with loading item of type: '" + type + "' with name: '" + name + "' and filename: '" + filename + "'" }
    {}
    [[nodiscard]] const char* what() const noexcept override {
        return error.c_str();
    }
};

class return_exception : public std::exception {
private:
    std::string error;

public:
    return_exception(const std::string& type, const std::string& name) :
        error{ "Error with returning item of type: '" + type + "' with name: '" + name + "' the item doesn't exist" }
    {}
    [[nodiscard]] const char* what() const noexcept override {
        return error.c_str();
    }
};

class open_file_exception : public std::exception {
private:
    std::string error;

public:
    open_file_exception(std::string Filename):
        error("Could open file with filename: '" + error + "'")
    {}
    [[nodiscard]] const char* what() const noexcept override {
        return error.c_str();
    }
};

class invalid_json_exception : public std::exception {
private:
    std::string error;
public:
    invalid_json_exception(std::string error):
        error(error)
    {}
    [[nodiscard]] const char* what() const noexcept override {
        return error.c_str();
    }
};