#ifndef OBTS_OPENBTS_GSMUTILITIES_H
#define OBTS_OPENBTS_GSMUTILITIES_H

#include <cstdint>
#include <unistd.h>

#include "gsmconstants.h"

namespace kneedeepbts::gsm {
/** Sleep for a given number of GSM frame periods. */
    inline void sleepFrames(uint32_t frames) {
        usleep(frames * kneedeepbts::gsm::FRAME_DURATION_US);
    }
}

#endif //OBTS_OPENBTS_GSMUTILITIES_H
