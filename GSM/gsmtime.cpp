#include "gsmtime.h"

namespace kneedeepbts::gsm {
    int32_t FNDelta(int32_t v1, int32_t v2) {
        static const int32_t halfModulus = gHyperframe/2;
        int32_t delta = v1-v2;
        if (delta>=halfModulus) delta -= gHyperframe;
        else if (delta<-halfModulus) delta += gHyperframe;
        return (int32_t) delta;
    }

    int32_t FNCompare(int32_t v1, int32_t v2) {
        int32_t delta = FNDelta(v1,v2);
        if (delta>0) return 1;
        if (delta<0) return -1;
        return 0;
    }

    GsmTime &GsmTime::operator++() {
        mFN = (mFN + 1) % gHyperframe;
        return *this;
    }

    GsmTime &GsmTime::decTN(unsigned step) {
        assert(step <= 8);
        mTN -= step;
        if (mTN < 0) {
            mTN += 8;
            mFN -= 1;
            if (mFN < 0) mFN += gHyperframe;
        }
        return *this;
    }

    GsmTime &GsmTime::incTN(unsigned step) {
        assert(step <= 8);
        mTN += step;
        if (mTN > 7) {
            mTN -= 8;
            mFN = (mFN + 1) % gHyperframe;
        }
        return *this;
    }

    GsmTime &GsmTime::operator+=(int step) {
        // Remember the step might be negative.
        mFN += step;
        if (mFN < 0) mFN += gHyperframe;
        mFN = mFN % gHyperframe;
        return *this;
    }

    GsmTime GsmTime::operator-(int step) const {
        return operator+(-step);
    }

    GsmTime GsmTime::operator+(int step) const {
        GsmTime newVal = *this;
        newVal += step;
        return newVal;
    }

    // (pat) Notice that + and - are different.
    GsmTime GsmTime::operator+(const GsmTime &other) const {
        unsigned newTN = (mTN + other.mTN) % 8;
        uint64_t newFN = (mFN + other.mFN + (mTN + other.mTN) / 8) % gHyperframe;
        return GsmTime(newFN, newTN);
    }

    // FIXME: This should probably return a GsmTime that's the difference, then
    //        the user can apply FNDelta to get an integer.
    int GsmTime::operator-(const GsmTime &other) const {
        return FNDelta(mFN, other.mFN);
    }

    bool GsmTime::operator<(const GsmTime &other) const {
        if (mFN == other.mFN) return (mTN < other.mTN);
        return FNCompare(mFN, other.mFN) < 0;
    }

    bool GsmTime::operator>(const GsmTime &other) const {
        if (mFN == other.mFN) return (mTN > other.mTN);
        return FNCompare(mFN, other.mFN) > 0;
    }

    bool GsmTime::operator<=(const GsmTime &other) const {
        if (mFN == other.mFN) return (mTN <= other.mTN);
        return FNCompare(mFN, other.mFN) <= 0;
    }

    bool GsmTime::operator>=(const GsmTime &other) const {
        if (mFN == other.mFN) return (mTN >= other.mTN);
        return FNCompare(mFN, other.mFN) >= 0;
    }

    bool GsmTime::operator==(const GsmTime &other) const {
        return (mFN == other.mFN) && (mTN == other.mTN);
    }

    // FIXME: The << operator is "teh crahp"
    std::ostream& operator<<(std::ostream& os, const GsmTime& t) {
        os << std::to_string(t.TN()) << std::string(":") << std::to_string(t.FN());
        return os;
    }
}