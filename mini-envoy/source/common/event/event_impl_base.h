#pragma once

#include "event2/event_struct.h"

namespace Event {

/**
 * Base class for libevent event implementations. The event struct is embedded inside of this class
 * and derived classes are expected to assign it inside of the constructor.
 */
class ImplBase {
protected:
    // event_del is the opposite function of event_add, that is, removing event from the base_
  ~ImplBase(){event_del(&raw_event_)};

  event raw_event_;
};

} // Event
