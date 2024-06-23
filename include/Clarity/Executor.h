//
// Created by xenon on 22.06.2024.
//

#ifndef CLARITY_DEV_EXECUTOR_H
#define CLARITY_DEV_EXECUTOR_H

#include <Clarity/Command.h>
#include <memory>
#include <functional>

using namespace std;

namespace clarity {

    enum ExecutorType {
        Void,
        WithCommand,
    };

    class Executor {

    public:

//        Constructors

        explicit Executor(
            const string& commandName,
            const function<void(const Command&)>& func
        );

        explicit Executor(
            const string& commandName,
            const function<void()>& func
        );

        static shared_ptr<Executor> make(
                const string& commandName,
                const function<void(const Command&)>& func
        );

        static shared_ptr<Executor> make(
                const string& commandName,
                const function<void()>& func
        );

//        Callers

        void exec(const Command&);
        [[nodiscard]] shared_ptr<Command> getCommand() const;


    private:
        shared_ptr<Command> command;
        function<void(const Command&)> funcWithCommand;
        function<void()> funcWithoutCommand;
        const ExecutorType type;

    };

}

#endif //CLARITY_DEV_EXECUTOR_H
