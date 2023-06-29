#include "gsmband.h"

#include <cassert>

namespace kneedeepbts::gsm {
    uint32_t uplinkFreqKHz(GsmBand band, unsigned ARFCN)
    {
        switch (band) {
            case GSM850:
                assert((ARFCN>=128)&&(ARFCN<=251));
                return 824200+200*(ARFCN-128);
            case EGSM900:
                if (ARFCN<=124) return 890000+200*ARFCN;
                assert((ARFCN>=975)&&(ARFCN<=1023));
                return 890000+200*(ARFCN-1024);
            case DCS1800:
                assert((ARFCN>=512)&&(ARFCN<=885));
                return 1710200+200*(ARFCN-512);
            case PCS1900:
                assert((ARFCN>=512)&&(ARFCN<=810));
                return 1850200+200*(ARFCN-512);
            default:
                assert(0);
        }
    }

    uint32_t downlinkFreqKHz(GsmBand band, unsigned ARFCN)
    {
        uint32_t uplink_freq = uplinkFreqKHz(band,ARFCN);
        switch (band) {
            case GSM850:
                return uplink_freq + 45000;
            case EGSM900:
                return uplink_freq + 45000;
            case DCS1800:
                return uplink_freq + 95000;
            case PCS1900:
                return uplink_freq + 80000;
            default:
                assert(0);
        }
    }
}
