#pragma once

#include "event_impl_base.h"

#include "envoy/event/signal.h"

namespace Event {

/**
 * libevent implementation of Event::SignalEvent.
 */
class SignalEventImpl : public SignalEvent, ImplBase {
public:
  SignalEventImpl(DispatcherImpl& dispatcher, int signal_num, SignalCb cb): cb_(cb) {
      evsignal_assign(&raw_event_, dispatcher.base(), signal_num,
                      [](evutil_socket_t, short, void*arg){
                          auto singleEvent = static_cast<SignalEventImpl*>(arg);
                          singleEvent->cb_();
                      },
      this);

      event_add(&raw_event_, nullptr);
  }

private:
  SignalCb cb_;
};

} // Event
