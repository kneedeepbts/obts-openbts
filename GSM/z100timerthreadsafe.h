#ifndef OBTS_OPENBTS_Z100TIMERTHREADSAFE_H
#define OBTS_OPENBTS_Z100TIMERTHREADSAFE_H

#include "z100timer.h"

// From CommonLibs Library
#include <Threads.h>

namespace kneedeepbts::gsm {
    class Z100TimerThreadSafe : public Z100Timer {
    public:
        bool expired() const {
            ScopedLock lock(mtLock);
            return Z100Timer::expired();
        }

        void expire() {
            ScopedLock lock(mtLock);
            Z100Timer::expire();
        }

        void set() {
            ScopedLock lock(mtLock);
            Z100Timer::set();
        }

        void set(long wLimitTime) {
            ScopedLock lock(mtLock);
            Z100Timer::set(wLimitTime);
        }

        void addTime(int msecs) {
            ScopedLock lock(mtLock);
            Z100Timer::addTime(msecs);
        }

        void reset() {
            ScopedLock lock(mtLock);
            Z100Timer::reset();
        }

        void reset(long wLimitTime) {
            ScopedLock lock(mtLock);
            Z100Timer::reset(wLimitTime);
        }

        // bool active() const;  // No need to protect.
        long remaining() const {
            ScopedLock lock(mtLock);
            return Z100Timer::remaining();
        }

        void wait() const {
            ScopedLock lock(mtLock);
            Z100Timer::wait();
        }

    private:
        mutable Mutex mtLock;
    };
}

#endif //OBTS_OPENBTS_Z100TIMERTHREADSAFE_H
