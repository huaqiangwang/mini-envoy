# Event Dispatcher

Event dispatcher is a libevent derived object, which arranges all libevent `Event` that connects to a 'event_base' object. It also handles the corner cases, such as clean up.

Essentially, a libevent `event` is a 'Event' of a file descriptor or timer or signal.

```C++
    event_base_once(base_.get(), -1, EV_TIMEOUT, [](evutil_socket_t, short, void* arg) -> void {
      static_cast<DispatcherImpl*>(arg)->runPostCallbacks();
    }, this, nullptr);
```
'fd' of '-1' means 'no fd'， which this is a not a file descriptor event, might be timer event.

## New Timer interface

- **createTimer**:

- **enableTimer**:

- **disableTimer**:

## New file event interfaces

- **FileEvent(callback* cb);**
- **activate(R|W)**: Make cb be called manually

## socket event interface

- **ListenerImpl::ListenerImpl**
 call evconnlistener_new to create event and add it to base

## Corner Case: defer delete

During the deleting a event list, it might happen that some event has been put into the deleting list.
Base on this, two delete list are used.

The interface API is `void DispatcherImpl::deferredDelete`, which put the event to be deleted to
the deleting list that `current_to_delete` is pointing to.
It enables a timer event to call `void DispatcherImpl::clearDeferredDeleteList()` for the first
element to be deleted. There are two delete list, `to_delete_1_` and `to_delete_2_`,
thus the timer mentioned above will be called at least twice.
The rotation of current_to_delete_ list is done in the timer handler `clearDeferredDeleteList()`.

This looks like solving problem such as empty a list but still having change to fill in some element. and avoid the lock to it.
Anyway, is there any other solution by using queue?



## libevent concepts
### bufferevent
http://www.wangafu.net/~nickm/libevent-book/Ref6_bufferevent.html


## Corner Case: 