//
// Created by xenon on 22.06.2024.
//

#include <Clarity/Executor.h>

using namespace clarity;

Executor::Executor(
        const std::string& commandName,
        const std::function<void(const Command&)>& func
        ) {
    this->command = std::make_shared<Command>(commandName);
    this->body = func;
}

void Executor::exec(const Command& _command) {
    this->body(_command);
}

std::shared_ptr<Command> Executor::getCommand() const {
    return this->command;
}

std::shared_ptr<Executor> Executor::make(
        const std::string &commandName, const std::function<void(const Command &)> &func) {

    return make_shared<Executor>(commandName, func);
}