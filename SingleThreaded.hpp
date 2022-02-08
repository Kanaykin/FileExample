#ifndef SINGLE_THREADED_H
#define SINGLE_THREADED_H

// no synchronization

template<class Host>
class SingleThreaded
{
public:
    struct Lock
    {
        Lock() {}
        explicit Lock(const SingleThreaded&) {}
    };
};

#endif // SINGLE_THREADED_H

