#ifndef OBTS_OPENBTS_GSMCLOCK_H
#define OBTS_OPENBTS_GSMCLOCK_H

#include <cstdint>

#include "gsmtime.h"

#include "Timeval.h"
#include "Threads.h"

/**
	A class for calculating the current GSM frame number.
	Has built-in concurrency protections.
*/
namespace kneedeepbts::gsm {
    class GsmClock {

    public:
        explicit GsmClock(const GsmTime &when = GsmTime(0)) : mBaseFN(when.FN()) {}

        /** Set the clock to a value. */
        void clockSet(const GsmTime &);

        bool isClockValid() const { return isValid; }    // Dont need a semaphore for POD.

        /** Read the clock. */
        int32_t FN() const;

        /** Read the clock. */
        GsmTime clockGet() const { return GsmTime(FN()); }

        /** Block until the clock passes a given time. */
        void wait(const GsmTime &) const;

        /** Return the system time associated with a given timestamp. */
        // (pat) in secs with microsec resolution.
        // (pat) This is updated at every CLOCK IND from the transceiver, so it is possible
        // for this time to skip either forward or backward, either as a result of the FN being
        // changed forward or backward by the radio, or jitter in when the CLOCK IND is processed.
        // If the when argument was retrieved during the same CLOCK IND interval then it is ok,
        // but we cannot guarantee that.
        double systime(const GsmTime &when) const;

        Timeval systime2(const GsmTime &when) const;

    private:
        bool isValid{};
        mutable Mutex mLock;
        int32_t mBaseFN;
        Timeval mBaseTime;    // Defaults to now.
    };
}

#endif //OBTS_OPENBTS_GSMCLOCK_H
