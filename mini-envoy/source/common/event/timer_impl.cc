//
// Created by david on 2022/4/7.
//

#include "timer_impl.h"
#include "event2/event.h"


namespace Event{
    // TODO: how about using the pointer of base class of DispatcherImpl
    // NO, the base class of DispatcherImpl, the Dispatcher, does not have
    // the base() method.
    /**
     * Create libevent event and insert that to dispatch.base
     * @param dispatcher
     * @param cb
     */
    TimerImpl::TimerImpl(DispatcherImpl& dispatcher, TimerCb cb): cb_(cb) {
        struct event* event;
        evtimer_assign(&raw_event_, &dispatcher.base(),
                       [](evutil_socket_t,short, void* arg) -> void{
            static_cast<TimerImpl*>(arg)->cb_();}, this);
    }

    TimerImpl::enableTimer(const std::chrono::milliseconds& d){
        if (d.count() == 0){
            event.active&raw_event_, EV_TIMEOUT, 0);
        }else{
            std::chrono::microseconds us = std::chrono::duration_cast<std::chrono::microseconds>(d);
            timeval tv;
            tv.tv_sec = us.count() / 1000000;
            tv.tv_usec = us.count() % 1000000;
            event_add(&raw_event_, &tv)
        }
    }

    TimerImpl::disableTimer() {event_del(&raw_event_);}
}