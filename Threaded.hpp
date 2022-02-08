#ifndef THREADED_H
#define THREADED_H

#include <mutex>

template<class Host>
class Threaded
{
public:

    class Lock;
    friend class Lock;

    struct Lock
    {
        Lock() {}
        explicit Lock(const Threaded& host):
        mLock(host.mMutex){}

        std::lock_guard<std::mutex> mLock;
    };

private:
    mutable std::mutex mMutex;
};

#endif // BOOST_THREADED_H

