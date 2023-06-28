#ifndef OBTS_OPENBTS_Z100TIMER_H
#define OBTS_OPENBTS_Z100TIMER_H

#include <cassert>

// From CommonLibs Library
#include <Timeval.h>

/**
	CCITT Z.100 activity timer, as described in GSM 04.06 5.1.
	All times are in milliseconds.
*/
namespace kneedeepbts::gsm {
    class Z100Timer {
    public:
        /** Create a timer with a given timeout in milliseconds. */
        explicit Z100Timer(long wLimitTime) : mLimitTime(wLimitTime), mActive(false) {}

        /** Blank constructor; if you use this object, it will assert. */
        Z100Timer() : mLimitTime(0), mActive(false) {}

        /** True if the timer is active and expired. */
        [[nodiscard]] bool expired() const;

        /** Force the timer into an expired state. */
        void expire();

        /** Start or restart the timer. */
        void set();

        /** Start or restart the timer, possibly specifying a new limit. */
        void set(long wLimitTime);

        // Change the limit time, and if active, the remaining time as well.
        void addTime(int msecs);

        /** Stop the timer. */
        void reset() {
            assert(mLimitTime != 0);
            mActive = false;
        }

        void reset(long wLimitTime) {
            mLimitTime = wLimitTime;
            reset();
        }

        /** Returns true if the timer is active. */
        [[nodiscard]] bool active() const { return mActive; }

        /**
            Remaining time until expiration, in milliseconds.
            Returns zero if the timer has expired.
        */
        [[nodiscard]] long remaining() const;

        /**
            Block until the timer expires.
            Returns immediately if the timer is not running.
        */
        void wait() const;

    private:
        Timeval mEndTime; // the time at which this timer will expire
        long mLimitTime; // timeout in milliseconds
        bool mActive; // true if timer is active
    };

    std::ostream &operator<<(std::ostream &os, const Z100Timer &);
}

#endif //OBTS_OPENBTS_Z100TIMER_H
