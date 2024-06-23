//
// Created by xenon on 22.06.2024.
//

#include <Clarity/Executor.h>

using namespace clarity;

Executor::Executor(
        const std::string& commandName,
        const std::function<void(const Command&)>& func
        ) : type(ExecutorType::WithCommand) {
    this->command = std::make_shared<Command>(commandName);
    this->funcWithCommand = func;
}

Executor::Executor(
        const std::string& commandName,
        const std::function<void()>& func
        ) : type(ExecutorType::Void) {
    this->command = std::make_shared<Command>(commandName);
    this->funcWithoutCommand = func;
}

void Executor::exec(const Command& _command) {
    switch (this->type) {
        case WithCommand:
            this->funcWithCommand(_command);
            break;
        case Void:
            this->funcWithoutCommand();
            break;
    }
}

std::shared_ptr<Command> Executor::getCommand() const {
    return this->command;
}

std::shared_ptr<Executor> Executor::make(
        const std::string &commandName, const std::function<void(const Command &)> &func) {

    return make_shared<Executor>(commandName, func);
}

std::shared_ptr<Executor> Executor::make(
        const std::string &commandName, const std::function<void()> &func) {

    return make_shared<Executor>(commandName, func);
}