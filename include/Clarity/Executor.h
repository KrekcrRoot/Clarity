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

    class Executor {

    public:
        explicit Executor(
            const string& commandName,
            const function<void(const Command&)>& func
        );

        void exec(const Command&);
        [[nodiscard]] shared_ptr<Command> getCommand() const;

        static shared_ptr<Executor> make(
            const string& commandName,
            const function<void(const Command&)>& func
        );

    private:
        shared_ptr<Command> command;
        function<void(const Command&)> body;

    };

}

#endif //CLARITY_DEV_EXECUTOR_H
