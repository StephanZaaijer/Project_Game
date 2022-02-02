#pragma once

#include <exception>
#include <string>

class LoadException : public std::exception {
private:
    std::string error;

public:
    LoadException(const std::string& type, const std::string& name, const std::string& filename) :
        error{ "Error with loading item of type: '" + type + "' with name: '" + name + "' and filename: '" + filename + "'" }
    {}
    [[nodiscard]] const char* what() const noexcept override {
        return error.c_str();
    }
};

class ReturnException : public std::exception {
private:
    std::string error;

public:
    ReturnException(const std::string& type, const std::string& name) :
        error{ "Error with returning item of type: '" + type + "' with name: '" + name + "' the item doesn't exist" }
    {}
    [[nodiscard]] const char* what() const noexcept override {
        return error.c_str();
    }
};

class OpenFileException : public std::exception {
private:
    std::string error;

public:
    OpenFileException(const std::string &filename):
        error("Could open file with filename: '" + filename + "'")
    {}
    [[nodiscard]] const char* what() const noexcept override {
        return error.c_str();
    }
};

class InvalidJsonException : public std::exception {
private:
    std::string error;
public:
    InvalidJsonException(const std::string &error):
        error(error)
    {}
    [[nodiscard]] const char* what() const noexcept override {
        return error.c_str();
    }
};

class UnknownColorException: public std::exception {
private:
    std::string error;
public:
    UnknownColorException(const std::string &Color) :
            error("The color: " + Color + " is not found as SF::Color") {}

    UnknownColorException(const sf::Color &Color) :
            error("The color with rgb value: (" + std::to_string(Color.r) + ", " + std::to_string(Color.g) + ", " +
                  std::to_string(Color.b) + ") is not found") {}

    [[nodiscard]] const char *what() const noexcept override {
        return error.c_str();
    }
};

