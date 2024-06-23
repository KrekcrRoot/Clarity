//
// Created by xenon on 22.06.2024.
//

#ifndef CLARITY_DEV_CONSOLE_H
#define CLARITY_DEV_CONSOLE_H

#include <Clarity/Executor.h>

#include <map>
#include <string>
#include <memory>

namespace clarity {

    class Console {

    public:

//        Constructors

        explicit Console(const char& _prefix = '/');

//        Initialization

        [[maybe_unused]] void init();

//        Add commands

        void push(const std::shared_ptr<Executor>& executor);
        void pushInterrupt(const std::shared_ptr<Executor>& executor);

//        Create commands and interrupters

        [[maybe_unused]] std::shared_ptr<Executor> make(
                const string& commandName,
                const function<void(const Command&)>& func,
                CommandType type
        );

        [[maybe_unused]] std::shared_ptr<Executor> make(
                const string& commandName,
                const function<void()>& func,
                CommandType type
        );

    private:
        std::map<std::string, std::shared_ptr<Executor>> commands, interrupts;
        std::shared_ptr<Executor> notFound;
        const char& prefix;

        void findAndExecCommand(const Command& command);
        void findAndExecInterrupt(const Command& interrupt);

    };

}

#endif //CLARITY_DEV_CONSOLE_H
