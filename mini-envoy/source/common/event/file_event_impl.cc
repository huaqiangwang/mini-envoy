//
// Created by david on 2022/4/7.
//
import "file_event_impl.h"

namespace Event {
    FileEventImpl::FileEventImpl(DispatcherImpl* dispatcher, int fd, FileReadCb cb)
    :cb_(cb) {
        event_assign(&raw_event_, &dispatcher.base(), fd,
                     EV_READ|EV_WRITE|EV_ET|EV_PERSIST,
                     [](evutil_socket_t, short signal, void* arg) -> void{
            auto fileEvent = static_cast<FileEventImpl*>(arg);
            uint32_t events = 0;
            if (signal & EV_READ)
                events |= FileReadyType::Read;
            if (signal & EV_WRITE)
                events |= FileReadyType::Write;
            fileEvent->cb_(events);
        },
        this);
        event_add(&raw_event_, nullptr);
    }
}
