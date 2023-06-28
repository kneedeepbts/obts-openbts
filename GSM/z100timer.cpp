#include "z100timer.h"

namespace kneedeepbts::gsm {
    bool Z100Timer::expired() const {
        assert(mLimitTime != 0);
        // A non-active timer does not expire.
        if (!mActive) return false;
        return mEndTime.passed();
    }

    void Z100Timer::set() {
        assert(mLimitTime != 0);
        mEndTime = Timeval(mLimitTime);
        mActive = true;
    }

    void Z100Timer::addTime(int msecs)    // Can be positive or negative
    {
        mLimitTime += msecs;
        if (mLimitTime < 0) { mLimitTime = 0; }
        if (mActive) {
            long remaining = mEndTime.remaining() + msecs;
            if (remaining < 0) { remaining = 0; }
            mEndTime.future(remaining);
        }
    }

    void Z100Timer::expire() {
        mEndTime = Timeval(0);
        mActive = true;
    }

    void Z100Timer::set(long wLimitTime) {
        mLimitTime = wLimitTime;
        set();
    }

    long Z100Timer::remaining() const {
        if (!mActive) return 0;
        long rem = mEndTime.remaining();
        if (rem < 0) rem = 0;
        return rem;
    }

    void Z100Timer::wait() const {
        while (!expired()) msleep(remaining());
    }

    std::ostream &operator<<(std::ostream &os, const Z100Timer &zt) {
        if (zt.active()) { os << zt.remaining(); }
        else { os << "inactive"; }
        return os;
    }
}
