#ifndef OBTS_OPENBTS_GSMTIME_H
#define OBTS_OPENBTS_GSMTIME_H

#include <cassert>
#include <string>

/**
	GSM frame clock value. GSM 05.02 4.3
	No internal thread sync.
*/
namespace kneedeepbts::gsm {
    /** The GSM hyperframe is largest time period in the GSM system, GSM 05.02 4.3.3. */
    // It is 2715648 or 3 hours, 28 minutes, 53 seconds
    const uint32_t gHyperframe = 2048UL * 26UL * 51UL;

    /** Duration ofa GSM frame, in microseconds. */
    const unsigned gFrameMicroseconds = 4615;

    /** Get a clock difference, within the modulus, v1-v2. */
    int32_t FNDelta(int32_t v1, int32_t v2);

    /**
	Compare two frame clock values.
	@return 1 if v1>v2, -1 if v1<v2, 0 if v1==v2
    */
    int32_t FNCompare(int32_t v1, int32_t v2);

    class GsmTime {

    public:
        explicit GsmTime(int wFN = 0, int wTN = 0) : mFN(wFN), mTN(wTN) {}

        /** Move the time forward to a given position in a given modulus. */
        void rollForward(unsigned wFN, unsigned modulus) {
            assert(modulus < gHyperframe);
            while ((mFN % modulus) != wFN) mFN = (mFN + 1) % gHyperframe;
        }

        /**@name Accessors. */
        //@{
        [[nodiscard]] int FN() const { return mFN; }
        void FN(unsigned wFN) { mFN = wFN; }
        [[nodiscard]] unsigned TN() const { return mTN; }
        void TN(unsigned wTN) { mTN = wTN; }

        // Operators
        GsmTime &operator++();
        GsmTime &operator+=(int step);
        GsmTime operator-(int step) const;
        GsmTime operator+(int step) const;
        GsmTime operator+(const GsmTime &other) const;
        int operator-(const GsmTime &other) const;
        bool operator<(const GsmTime &other) const;
        bool operator>(const GsmTime &other) const;
        bool operator<=(const GsmTime &other) const;
        bool operator>=(const GsmTime &other) const;
        bool operator==(const GsmTime &other) const;

        // Methods
        GsmTime &decTN(unsigned step = 1);
        GsmTime &incTN(unsigned step = 1);

        /**@name Standard derivations. */
        //@{

        /** GSM 05.02 3.3.2.2.1 */
        [[nodiscard]] unsigned SFN() const { return mFN / (26 * 51); }

        /** GSM 05.02 3.3.2.2.1 */
        [[nodiscard]] unsigned T1() const { return SFN() % 2048; }

        /** GSM 05.02 3.3.2.2.1 */
        [[nodiscard]] unsigned T2() const { return mFN % 26; }

        /** GSM 05.02 3.3.2.2.1 */
        [[nodiscard]] unsigned T3() const { return mFN % 51; }

        /** GSM 05.02 3.3.2.2.1. */
        [[nodiscard]] unsigned T3p() const { return (T3() - 1) / 10; }

        /** GSM 05.02 6.3.1.3. */
        [[nodiscard]] unsigned TC() const { return (FN() / 51) % 8; }

        /** GSM 04.08 10.5.2.30. */
        [[nodiscard]] unsigned T1p() const { return SFN() % 32; }

        /** GSM 05.02 6.2.3 */
        [[nodiscard]] unsigned T1R() const { return T1() % 64; }

    private:
        int mFN; // frame number in the hyperframe
        int mTN; // timeslot number
    };

    std::ostream& operator<<(std::ostream& os, const GsmTime& t);
}

#endif //OBTS_OPENBTS_GSMTIME_H
