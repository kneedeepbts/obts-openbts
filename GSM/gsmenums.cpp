#include "gsmenums.h"

namespace kneedeepbts::gsm {
    std::ostream &operator<<(std::ostream &os, L3PD val) {
        switch (val) {
            case L3CallControlPD:
                os << "Call Control";
                break;
            case L3MobilityManagementPD:
                os << "Mobility Management";
                break;
            case L3RadioResourcePD:
                os << "Radio Resource";
                break;
            default:
                os << std::hex << "0x" << (int) val << std::dec;
        }
        return os;
    }

    std::ostream &operator<<(std::ostream &os, TypeOfNumber type) {
        switch (type) {
            case UnknownTypeOfNumber:
                os << "unknown";
                break;
            case InternationalNumber:
                os << "international";
                break;
            case NationalNumber:
                os << "national";
                break;
            case NetworkSpecificNumber:
                os << "network-specific";
                break;
            case ShortCodeNumber:
                os << "short code";
                break;
            default:
                os << "?" << (int) type << "?";
        }
        return os;
    }

    std::ostream &operator<<(std::ostream &os, NumberingPlan plan) {
        switch (plan) {
            case UnknownPlan:
                os << "unknown";
                break;
            case E164Plan:
                os << "E.164/ISDN";
                break;
            case X121Plan:
                os << "X.121/data";
                break;
            case F69Plan:
                os << "F.69/Telex";
                break;
            case NationalPlan:
                os << "national";
                break;
            case PrivatePlan:
                os << "private";
                break;
            default:
                os << "?" << (int) plan << "?";
        }
        return os;
    }

    std::ostream &operator<<(std::ostream &os, MobileIDType wID) {
        switch (wID) {
            case NoIDType:
                os << "None";
                break;
            case IMSIType:
                os << "IMSI";
                break;
            case IMEIType:
                os << "IMEI";
                break;
            case TMSIType:
                os << "TMSI";
                break;
            case IMEISVType:
                os << "IMEISV";
                break;
            default:
                os << "?" << (int) wID << "?";
        }
        return os;
    }

    std::ostream &operator<<(std::ostream &os, TypeAndOffset tao) {
        switch (tao) {
            case TDMA_MISC:
                os << "(misc)";
                break;
            case TCHF_0:
                os << "TCH/F";
                break;
            case TCHH_0:
                os << "TCH/H-0";
                break;
            case TCHH_1:
                os << "TCH/H-1";
                break;
            case SDCCH_4_0:
                os << "SDCCH/4-0";
                break;
            case SDCCH_4_1:
                os << "SDCCH/4-1";
                break;
            case SDCCH_4_2:
                os << "SDCCH/4-2";
                break;
            case SDCCH_4_3:
                os << "SDCCH/4-3";
                break;
            case SDCCH_8_0:
                os << "SDCCH/8-0";
                break;
            case SDCCH_8_1:
                os << "SDCCH/8-1";
                break;
            case SDCCH_8_2:
                os << "SDCCH/8-2";
                break;
            case SDCCH_8_3:
                os << "SDCCH/8-3";
                break;
            case SDCCH_8_4:
                os << "SDCCH/8-4";
                break;
            case SDCCH_8_5:
                os << "SDCCH/8-5";
                break;
            case SDCCH_8_6:
                os << "SDCCH/8-6";
                break;
            case SDCCH_8_7:
                os << "SDCCH/8-7";
                break;
            case TDMA_BEACON:
                os << "BCH";
                break;
            case TDMA_BEACON_BCCH:
                os << "BCCH";
                break;
            case TDMA_BEACON_CCCH:
                os << "CCCH";
                break;
            case TDMA_PDCH:
                os << "PDCH";
                break;
            case TDMA_PACCH:
                os << "PACCH";
                break;
            case TDMA_PTCCH:
                os << "PTCCH";
                break;
            case TDMA_PDIDLE:
                os << "PDIDLE";
                break;
            default:
                os << "?" << (int) tao << "?";
        }
        return os;
    }

    std::ostream &operator<<(std::ostream &os, ChannelType val) {
        switch (val) {
            case UndefinedCHType:
                os << "undefined";
                return os;
            case SCHType:
                os << "SCH";
                break;
            case FCCHType:
                os << "FCCH";
                break;
            case BCCHType:
                os << "BCCH";
                break;
            case RACHType:
                os << "RACH";
                break;
            case SDCCHType:
                os << "SDCCH";
                break;
            case FACCHType:
                os << "FACCH";
                break;
            case CCCHType:
                os << "CCCH";
                break;
            case SACCHType:
                os << "SACCH";
                break;
            case TCHFType:
                os << "TCH/F";
                break;
            case TCHHType:
                os << "TCH/H";
                break;
            case AnyTCHType:
                os << "any TCH";
                break;
            case LoopbackFullType:
                os << "Loopback Full";
                break;
            case LoopbackHalfType:
                os << "Loopback Half";
                break;
            case PDTCHCS1Type:
                os << "PDTCHCS1";
                break;
            case PDTCHCS2Type:
                os << "PDTCHCS2";
                break;
            case PDTCHCS3Type:
                os << "PDTCHCS3";
                break;
            case PDTCHCS4Type:
                os << "PDTCHCS4";
                break;
            case PSingleBlock1PhaseType:
                os << "GPRS_SingleBlock1Phase";
                break;
            case PSingleBlock2PhaseType:
                os << "GPRS_SingleBlock2Phase";
                break;
            case AnyDCCHType:
                os << "any DCCH";
                break;
            default:
                os << "?" << (int) val << "?";
                break;
        }
        return os;
    }
}
