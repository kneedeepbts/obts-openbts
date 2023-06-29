#ifndef OBTS_OPENBTS_GSMBAND_H
#define OBTS_OPENBTS_GSMBAND_H

#include <cstdint>

namespace kneedeepbts::gsm {
    /** Codes for GSM band types, GSM 05.05 2.  */
    enum GsmBand {
        GSM850 = 850, // US cellular
        EGSM900 = 900, // extended GSM
        DCS1800 = 1800, // worldwide DCS band
        PCS1900 = 1900 //< US PCS band
    };

    /**@name Actual radio carrier frequencies, in kHz, GSM 05.05 2 */
    uint32_t uplinkFreqKHz(GsmBand wBand, uint32_t wARFCN);
    uint32_t downlinkFreqKHz(GsmBand wBand, uint32_t wARFCN);
}

#endif //OBTS_OPENBTS_GSMBAND_H
