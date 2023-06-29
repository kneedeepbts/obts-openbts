#ifndef GSMCOMMON_H
#define GSMCOMMON_H

#include <ostream>

namespace kneedeepbts::gsm {
    /** GSM 04.08 Table 10.5.118 and GSM 03.40 9.1.2.5 */
    enum TypeOfNumber {
        UnknownTypeOfNumber = 0,
        InternationalNumber = 1,
        NationalNumber = 2,
        NetworkSpecificNumber = 3,
        ShortCodeNumber = 4,
        AlphanumericNumber = 5,
        AbbreviatedNumber = 6
    };
    std::ostream& operator<<(std::ostream&, TypeOfNumber);

    /** GSM 04.08 Table 10.5.118 and GSM 03.40 9.1.2.5 */
    enum NumberingPlan {
        UnknownPlan = 0,
        E164Plan = 1,
        X121Plan = 3,
        F69Plan = 4,
        NationalPlan = 8,
        PrivatePlan = 9,
        ERMESPlan = 10
    };
    std::ostream& operator<<(std::ostream&, NumberingPlan);

    /**@name GSM Logical channel (LCH) types. */
    /** Codes for logical channel types. */
    enum ChannelType {
        ///@name Non-dedicated control channels.
        SCHType,		///< sync
        FCCHType,		///< frequency correction
        BCCHType,		///< broadcast control
        CCCHType,		///< common control, a combination of several sub-types
        RACHType,		///< random access
        SACCHType,		///< slow associated control (acutally dedicated, but...)
        CBCHType,		///< cell broadcast channel
        ///@name Dedicated control channels (DCCHs).
        SDCCHType,		///< standalone dedicated control
        FACCHType,		///< fast associated control
        ///@name Traffic channels
        TCHFType,		///< full-rate traffic
        TCHHType,		///< half-rate traffic
        AnyTCHType,		///< any TCH type
        //@name Packet channels for GPRS.
        PDTCHCS1Type,
        PDTCHCS2Type,
        PDTCHCS3Type,
        PDTCHCS4Type,
        //@name Packet CHANNEL REQUEST responses
        // These are used only as return value from decodeChannelNeeded(), and do not correspond
        // to any logical channels.
        PSingleBlock1PhaseType,
        PSingleBlock2PhaseType,
        ///@name Special internal channel types.
        LoopbackFullType,		///< loopback testing
        LoopbackHalfType,		///< loopback testing
        AnyDCCHType,			///< any dedicated control channel
        UndefinedCHType,		///< undefined
    };
    std::ostream& operator<<(std::ostream& os, ChannelType val);

    /** Mobile identity types, GSM 04.08 10.5.1.4 */
    enum MobileIDType {
        NoIDType = 0,
        IMSIType = 1,
        IMEIType = 2,
        IMEISVType = 3,
        TMSIType = 4
    };
    std::ostream& operator<<(std::ostream& os, MobileIDType);

    /** Type and TDMA offset of a logical channel, from GSM 04.08 10.5.2.5 */
    enum TypeAndOffset {
        TDMA_MISC=0,
        TCHF_0=1,
        TCHH_0=2, TCHH_1=3,
        SDCCH_4_0=4, SDCCH_4_1=5, SDCCH_4_2=6, SDCCH_4_3=7,
        SDCCH_8_0=8, SDCCH_8_1=9, SDCCH_8_2=10, SDCCH_8_3=11,
        SDCCH_8_4=12, SDCCH_8_5=13, SDCCH_8_6=14, SDCCH_8_7=15,
        /// Some extra ones for our internal use.
        TDMA_BEACON_BCCH=253,
        TDMA_BEACON_CCCH=252,
        TDMA_BEACON=255,
        //TDMA_PDTCHF,	// packet data traffic logical channel, full speed.
        TDMA_PDCH,		// packet data channel, inclusive
        TDMA_PACCH,		// packet control channel, shared with data but distinguished in MAC header.
        TDMA_PTCCH,		// packet data timing advance logical channel
        TDMA_PDIDLE		// Handles the packet channel idle frames.
    };
    std::ostream& operator<<(std::ostream& os, TypeAndOffset);

    /** L3 Protocol Discriminator, GSM 04.08 10.2, GSM 04.07 11.2.3.1.1. */
    enum L3PD {
        L3GroupCallControlPD=0x00,
        L3BroadcastCallControlPD=0x01,
        // L3PDSS1PD=0x02,		// 2 is EPS (4G) session management
        L3CallControlPD=0x03,	// call control, call related SSD [Supplementary Service Data] messages.
        // L3PDSS2PD=0x04,			// 4 is GPRS Transparent Transport Protocol.
        L3MobilityManagementPD=0x05,
        L3RadioResourcePD=0x06,
        // 7 is EPS (4G) mobility mananagement messages.
        L3GPRSMobilityManagementPD=0x08,
        L3SMSPD=0x09,
        L3GPRSSessionManagementPD=0x0a,
        L3NonCallSSPD=0x0b,		// non-call SSD [Supplementary Service Data] messages.
        L3LocationPD=0x0c,		// Location services specified in 3GPP TS 44.071
        L3ExtendedPD=0x0e,		// reserved to extend PD to a full octet.
        L3TestProcedurePD=0x0f,
        L3UndefinedPD=-1
    };
    std::ostream& operator<<(std::ostream& os, L3PD val);
};

#endif
