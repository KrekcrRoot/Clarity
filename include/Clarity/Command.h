//
// Created by xenon on 22.06.2024.
//

#ifndef CLARITY_DEV_COMMAND_H
#define CLARITY_DEV_COMMAND_H

#include <string>
#include <iostream>
#include <vector>
#include <sstream>

namespace clarity {

    enum CommandType {
        Default,
        Interrupt,
    };

    class Command {

    public:
        explicit Command(const std::string& _body);
        [[nodiscard]] bool isValid() const;

        [[nodiscard, maybe_unused]] std::string getRaw() const;

//        Get metadata
        [[nodiscard]] std::string getCommandName() const;
        [[nodiscard, maybe_unused]] std::vector<std::string> getArguments() const;

//        Operators
        bool operator==(const Command& a) const;
        bool operator!=(const Command& a) const;


    private:
        const std::string& body;

    };

}

#endif //CLARITY_DEV_COMMAND_H
