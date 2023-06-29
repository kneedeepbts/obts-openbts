#ifndef OBTS_OPENBTS_GSMBURSTS_H
#define OBTS_OPENBTS_GSMBURSTS_H

// From CommonLibs
#include <BitVector.h>

namespace kneedeepbts::gsm {
    /** GSM Training sequences from GSM 05.02 5.2.3. */
    inline const BitVector gTrainingSequence[] = {
            BitVector("00100101110000100010010111"),
            BitVector("00101101110111100010110111"),
            BitVector("01000011101110100100001110"),
            BitVector("01000111101101000100011110"),
            BitVector("00011010111001000001101011"),
            BitVector("01001110101100000100111010"),
            BitVector("10100111110110001010011111"),
            BitVector("11101111000100101110111100"),
    };

    /** C0T0 filler burst, GSM 05.02, 5.2.6 */
    // (pat) Dummy Burst defined in GSM 5.02 5.2.6
    // From 5.02 6.5.1: A base transceiver station must transmit a burst in every timeslot of every TDMA frame in the downlink of
    // radio frequency channel C0 of the cell allocation (to allow mobiles to make power measurements of the radio
    // frequency channels supporting the BCCH, see GSM 05.08). In order to achieve this requirement a dummy
    // burst is defined in clause 5.2.6 which shall be transmitted by the base transceiver station on all timeslots of all
    // TDMA frames of radio frequency channel C0 for which no other channel requires a burst to be transmitted.
    // (pat) But this is probably not correct for an idle SACCH, where we should be delivering L2 idle frames.
    inline const BitVector gDummyBurst("0001111101101110110000010100100111000001001000100000001111100011100010111000101110001010111010010100011001100111001111010011111000100101111101010000");

    /** Random access burst synch. sequence */
    inline const BitVector gRACHSynchSequence("01001011011111111001100110101010001111000");

}

#endif //OBTS_OPENBTS_GSMBURSTS_H
