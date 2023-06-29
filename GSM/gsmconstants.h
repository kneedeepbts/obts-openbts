#ifndef OBTS_OPENBTS_GSMCONSTANTS_H
#define OBTS_OPENBTS_GSMCONSTANTS_H

#include <cstdint>

namespace kneedeepbts::gsm {
    /**@name GSM LAPDm timeouts, GSM 04.06 5.8, ITU-T Q.921 5.9 */
    inline const uint32_t T200_MS = 900; // LAPDm ACK timeout, set for typical turnaround time

    /**@name GSM timeouts for radio resource management, GSM 04.08 11.1. */
    //const unsigned T3101ms = 4000;		///< L1 timeout for SDCCH assignment (pat) Started on Immediate Assignment, stopped when MS seizes channel.
    // (pat 4-2014) Increase T3101 to allow time for a SACCH init first, and additionally the old value seemed too low anyway, so add 2 secs.
    inline const uint32_t T3101_MS = 6000; // L1 timeout for SDCCH assignment (pat) Started on Immediate Assignment, stopped when MS seizes channel.
    inline const uint32_t T3107_MS = 3000; // L1 timeout for TCH/FACCH assignment (pat) or any change of channel assignment.
    // (pat) moved to config const unsigned T3109ms = 30000;		///< L1 timeout for an existing channel
    inline const uint32_t T3111_MS = 2 * T200_MS; // L1 timeout for reassignment of a channel

    /**@name GSM timeouts for mobility management, GSM 04.08 11.2. */
    inline const uint32_t T3260_MS = 12000;		///< ID request timeout

    /**@name GSM timeouts for SMS. GSM 04.11 */
    inline const uint32_t TR1M_MS = 30000;		///< RP-ACK timeout

    // GSM 05.02 v5.0.0 sec 4.3.1
    inline const uint32_t FRAME_DURATION_US = 4615; // 8 * (3 / 5200) sec

    // GSM 05.02 v5.0.0 sec 4.3.3
    inline const uint32_t FRAME_NUMBER_MAX = (26 * 51 * 2048) - 1;
}

#endif //OBTS_OPENBTS_GSMCONSTANTS_H
