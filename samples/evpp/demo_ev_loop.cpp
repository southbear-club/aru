#include "ars/components/evpp/EventLoopThread.hpp"
#include "ars/sdk/memory/mem.hpp"

using namespace ars::evpp;

static void onTimer(TimerID timerID, int n) {
    printf("tid=%ld timerID=%lu time=%lus n=%d\n", ars::sdk::gettid(), (unsigned long)timerID, (unsigned long)time(NULL), n);
}

int main(int argc, char* argv[]) {
    ars::sdk::memcheck_register();

    printf("main tid=%ld\n", ars::sdk::gettid());

    EventLoopPtr loop(new EventLoop);

    // runEvery 1s
    loop->setInterval(1000, std::bind(onTimer, std::placeholders::_1, 100));

    // runAfter 10s
    loop->setTimeout(10000, [&loop](TimerID timerID){
        loop->stop();
    });

    loop->queueInLoop([](){
        printf("queueInLoop tid=%ld\n", ars::sdk::gettid());
    });

    loop->runInLoop([](){
        printf("runInLoop tid=%ld\n", ars::sdk::gettid());
    });

    // run until loop stopped
    loop->run();

    return 0;
}
