//
// Created by xenon on 22.06.2024.
//

#include <Clarity/Command.h>

using namespace clarity;

Command::Command(const std::string& _body) : body(_body) {}

bool Command::isValid() const {
    return !this->body.empty();
}

bool Command::operator==(const clarity::Command &a) const {

    if(!this->isValid() || !a.isValid()) {
        return false;
    }

    const std::string& first = this->getCommandName();
    const std::string& second = a.getCommandName();

    return std::equal(
            first.begin(),
            first.end(),
            second.begin(),
            second.end()
            );
}

bool Command::operator!=(const clarity::Command &a) const {
    return !(this->operator==(a));
}

std::string Command::getCommandName() const {
    if(!this->isValid()) {
        throw std::runtime_error("[!] Command not valid");
    }

    return this->body.substr(0, this->body.find(' '));
}

std::vector<std::string> Command::getAttributes() const {

    if(!this->isValid()) {
        throw std::runtime_error("[!] Command not valid");
    }

    if(this->body.find(' ') == std::string::npos) {
        return {};
    }

    std::vector<std::string> result;

    std::stringstream ss(this->body);
    std::string word;
    while (!ss.eof()) {
        std::getline(ss, word, ' ');
        result.push_back(word);
    }

    result.erase(result.begin());

    return result;

}

std::string Command::getRaw() const {
    return this->body;
}
