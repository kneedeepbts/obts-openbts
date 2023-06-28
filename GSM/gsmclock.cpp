#include "gsmclock.h"

#include <cmath>

namespace kneedeepbts::gsm {
    void GsmClock::clockSet(const GsmTime& when) {
        ScopedLock lock(mLock);
        mBaseTime = Timeval(0);
        mBaseFN = when.FN();
        isValid = true;
    }


    int32_t GsmClock::FN() const {
        ScopedLock lock(mLock);
        Timeval now;
        int32_t deltaSec = now.sec() - mBaseTime.sec();
        int32_t deltaUSec = now.usec() - mBaseTime.usec();
        int64_t elapsedUSec = 1000000LL*deltaSec + deltaUSec;
        int64_t elapsedFrames = elapsedUSec / gFrameMicroseconds;
        int32_t currentFN = (mBaseFN + elapsedFrames) % gHyperframe;
        return currentFN;
    }

    double GsmClock::systime(const GsmTime& when) const {
        ScopedLock lock(mLock);
        const double slotMicroseconds = (48.0 / 13e6) * 156.25;
        const double frameMicroseconds = slotMicroseconds * 8.0;
        int32_t elapsedFrames = when.FN() - mBaseFN;
        if (elapsedFrames<0) elapsedFrames += gHyperframe;
        double elapsedUSec = elapsedFrames * frameMicroseconds + when.TN() * slotMicroseconds;
        double baseSeconds = mBaseTime.sec() + mBaseTime.usec()*1e-6;
        double st = baseSeconds + 1e-6*elapsedUSec;
        return st;
    }

    Timeval GsmClock::systime2(const GsmTime& when) const {
        double ftime = systime(when);
        unsigned sec = std::floor(ftime);
        unsigned usec = (ftime - sec) * 1e6;
        return Timeval(sec,usec);
    }

    void GsmClock::wait(const GsmTime& when) const {
        int32_t now = FN();
        int32_t target = when.FN();
        int32_t delta = FNDelta(target,now);
        if (delta<1) return;
        static const int32_t maxSleep = 51*26;
        if (delta>maxSleep) delta=maxSleep;
        //sleepFrames(delta); Moving here to break a dependency
        usleep(delta * gFrameMicroseconds);
    }
}