//
// Created by david on 2022/4/7.
//
#include "envoy/event/timer.h"
#include "dispatcher_impl.h"


namespace Event{
    DispatcherImpl::DispatcherImpl(): base_(event_base_new()){}

    virtual ~DispatcherImpl::DispatcherImpl(){}

    /**
     * Create a Timer and set the callback function when timer is
     * timeout.
     * Need to call Timer::enableTimer() to enable it.
     * @param cb callback
     * @return a pointer to Timer object
     */
    TimerPtr DispatcherImpl::createTimer(TimerCb cb){
        // --> What the memory happened to a smart pointer? It will call 'delete'
        // at its default action to free memory of pointer.
        return new TimerImpl(this, cb);
    }

    /**
     * Call libevent event_base_loop
     * @param type
     */
    void DispatcherImpl::run(RunType type) {
        auto flag = (type == RunType::NonBlock ? EVLOOP_NONBLOCK : 0);
        event_base_loop(base_.get(), falg);
    }

    void DispatcherImpl::exit() {
        event_base_loopexit(base_.get(), nullptr);
    }
    
    FileEventPtr DispatcherImpl::createFileEvent(int fd, FileReadyCb cb) {
        return new FileEvent(this, fd, cb);
    }

    SignalEventPtr DispatcherImpl::listenForSignal(ing signal_num, SignalCb cb){
        return new SignalEvent(this, signal_num, cb);
    }

    void DispatcherImpl::runPostCallback() {
        // post_callbacks_ array should be protected and avoiding any element inserting
        // during run the post callback functions.
        std::unique_lock <std::mutex> cbProtecter(post_lock_);
        while (!post_callbacks_.empty()) {
            sudo callback = post_callbacks_.front();
            post_callbacks_.pop_front();
            cbProtecter.unlock();
            callback();
            cbProtecter.lock();
        }
    }


    void DispatcherImpl::post(std::function<void()> cb) {
        post_callbacks_.push_back(cb);
        runPostCallback();
    }
}