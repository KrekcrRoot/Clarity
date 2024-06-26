//
// Created by xenon on 22.06.2024.
//

#include <Clarity/Console.h>
#include <Clarity/Command.h>
#include <iostream>
#include <string>

using namespace clarity;
using namespace std;

inline std::string trim(std::string& str)
{
    str.erase(str.find_last_not_of(' ')+1);
    str.erase(0, str.find_first_not_of(' '));
    return str;
}

[[maybe_unused]] Console::Console(const char& _prefix) : prefix(_prefix) {
    this->notFound = Executor::make("notFound", [](const Command& _){
        std::cerr << "[!] Command not found\n";
    });
}

[[maybe_unused]] void Console::init() {

    Command quit("quit");

    while (true) {
        std::cout << "\n>> ";
        string input;
        getline(cin, input);

        input = trim(input);

        if(input.empty()) continue;
        bool isCommand = input[0] == this->prefix;

        if(isCommand) {
            std::string commandBody = input.substr(1);
            Command command{commandBody};

            if(command == quit) break;
            this->findAndExecCommand(command);

            continue;
        }

        Command interrupt{input};
        this->findAndExecInterrupt(interrupt);
    }
}

void Console::findAndExecCommand(const clarity::Command &command) {
    auto it = this->commands.find(command.getCommandName());

    if(it != this->commands.end()) {
        this->commands[command.getCommandName()]->exec(command);
    }else{
        this->notFound->exec(command);
    }
}

void Console::findAndExecInterrupt(const clarity::Command &interrupt) {
    auto it = this->interrupts.find(interrupt.getCommandName());

    if(it != this->interrupts.end()) {
        this->interrupts[interrupt.getCommandName()]->exec(interrupt);
    }else{
        this->notFound->exec(interrupt);
    }
}

void Console::push(const std::shared_ptr<Executor>& executor) {
    if(executor->getCommand()->getCommandName() == "notFound") {
        this->notFound = executor;
        return;
    }

    this->commands[executor->getCommand()->getCommandName()] = executor;
}

void Console::pushInterrupt(const shared_ptr<Executor> &executor) {
    this->interrupts[executor->getCommand()->getCommandName()] = executor;
}

[[maybe_unused]] std::shared_ptr<Executor>
Console::make(const string &commandName, const function<void(const Command &)> &func, CommandType type) {

    const auto executor = std::make_shared<Executor>(commandName, func);

    switch (type) {
        case CommandType::Default:
            this->push(executor);
            break;
        case CommandType::Interrupt:
            this->pushInterrupt(executor);
            break;
    }

    return executor;
}

[[maybe_unused]] std::shared_ptr<Executor>
Console::make(const string &commandName, const function<void()> &func, CommandType type) {
    const auto executor = std::make_shared<Executor>(commandName, func);

    switch (type) {
        case CommandType::Default:
            this->push(executor);
            break;
        case CommandType::Interrupt:
            this->pushInterrupt(executor);
            break;
    }

    return executor;
}