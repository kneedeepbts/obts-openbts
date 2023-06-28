/**@file Common-use GSM declarations, most from the GSM 04.xx and 05.xx series. */
/*
* Copyright 2008, 2009, 2010 Free Software Foundation, Inc.
* Copyright 2010 Kestrel Signal Processing, Inc.
* Copyright 2011, 2014 Range Networks, Inc.
*
* This software is distributed under multiple licenses;
* see the COPYING file in the main directory for licensing
* information for this specific distribution.
*
* This use of this software may be subject to additional restrictions.
* See the LEGAL file in the main directory for details.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

*/



#ifndef GSMCOMMON_H
#define GSMCOMMON_H

#include "Defines.h"
#include <cstdlib>
#include <sys/time.h>
#include <ostream>
#include <vector>

#include <Threads.h>
#include <Timeval.h>
#include <BitVector.h>
#include <ScalarTypes.h>

namespace GSM {
/**@namespace GSM This namespace covers L1 FEC, L2 and L3 message translation. */

/* forward references */
//class L1FEC;
//class L2LAPDm;
//class L3Processor;
//class L2Header;

/** A base class for GSM exceptions. */
class GSMError {};

/** Duration ofa GSM frame, in microseconds. */
const unsigned gFrameMicroseconds = 4615;

/** Sleep for a given number of GSM frame periods. */
inline void sleepFrames(unsigned frames)
	{ usleep(frames * gFrameMicroseconds); }

/** Sleep for 1 GSM frame period. */
inline void sleepFrame()
	{ usleep(gFrameMicroseconds); }

/** GSM Training sequences from GSM 05.02 5.2.3. */
extern const BitVector2 gTrainingSequence[];

/** C0T0 filler burst, GSM 05.02, 5.2.6 */
extern const BitVector2 gDummyBurst;

/** Random access burst synch. sequence */
extern const BitVector2 gRACHSynchSequence;

enum GSMAlphabet {
	ALPHABET_7BIT,
	ALPHABET_8BIT,
	ALPHABET_UCS2
};

/**@name Support for GSM 7-bit alphabet, GSM 03.38 6.2.1. */
/**
	Indexed by GSM 7-bit, returns ISO-8859-1.
	We do not support the extended table, so 0x1B is a space.
	FIXME -- ISO-8859-1 doesn't support Greek!
*/
static const unsigned char gGSMAlphabet[] = "@\243$\245\350\351\371\354\362\347\n\330\370\r\305\345D_FGLOPCSTZ \306\346\337\311 !\"#\244%&\'()*+,-./0123456789:;<=>?\241ABCDEFGHIJKLMNOPQRSTUVWXYZ\304\326\321\334\247\277abcdefghijklmnopqrstuvwxyz\344\366\361\374\341";
unsigned char encodeGSMChar(unsigned char ascii);
inline unsigned char decodeGSMChar(unsigned char sms) { return gGSMAlphabet[(unsigned)sms]; }

/**@name BCD-ASCII mapping, GMS 04.08 Table 10.5.118. */
/** Indexed by BCD, returns ASCII. */
static const char gBCDAlphabet[] = "0123456789.#abc";
char encodeBCDChar(char ascii);
inline char decodeBCDChar(char bcd) { return gBCDAlphabet[(unsigned)bcd]; }

/**@name Globally-fixed GSM timeout values (all in ms). */
/**@name GSM LAPDm timeouts, GSM 04.06 5.8, ITU-T Q.921 5.9 */
const unsigned T200ms = 900;		///< LAPDm ACK timeout, set for typical turnaround time
/**@name GSM timeouts for radio resource management, GSM 04.08 11.1. */
//const unsigned T3101ms = 4000;		///< L1 timeout for SDCCH assignment (pat) Started on Immediate Assignment, stopped when MS seizes channel.
// (pat 4-2014) Increase T3101 to allow time for a SACCH init first, and additionally the old value seemed too low anyway, so add 2 secs.
const unsigned T3101ms = 6000;		///< L1 timeout for SDCCH assignment (pat) Started on Immediate Assignment, stopped when MS seizes channel.
const unsigned T3107ms = 3000;		///< L1 timeout for TCH/FACCH assignment (pat) or any change of channel assignment.
// (pat) moved to config const unsigned T3109ms = 30000;		///< L1 timeout for an existing channel
const unsigned T3111ms = 2*T200ms;	///< L1 timeout for reassignment of a channel
/**@name GSM timeouts for mobility management, GSM 04.08 11.2. */
const unsigned T3260ms = 12000;		///< ID request timeout
/**@name GSM timeouts for SMS. GSM 04.11 */
const unsigned TR1Mms = 30000;		///< RP-ACK timeout

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

/** Codes for GSM band types, GSM 05.05 2.  */
enum GSMBand {
	GSM850=850,			///< US cellular
	EGSM900=900,		///< extended GSM
	DCS1800=1800,		///< worldwide DCS band
	PCS1900=1900		///< US PCS band
};

/**@name Actual radio carrier frequencies, in kHz, GSM 05.05 2 */
unsigned uplinkFreqKHz(GSMBand wBand, unsigned wARFCN);
unsigned uplinkOffsetKHz(GSMBand);
unsigned downlinkFreqKHz(GSMBand wBand, unsigned wARFCN);

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

/**
 L3 Protocol Discriminator, GSM 04.08 10.2, GSM 04.07 11.2.3.1.1.
*/
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

/**@name Tables related to Tx-integer; GSM 04.08 3.3.1.1.2 and 10.5.2.29. */
/** "T" parameter, from GSM 04.08 10.5.2.29.  Index is TxInteger. */
extern const unsigned RACHSpreadSlots[16];
/** "S" parameter, from GSM 04.08 3.3.1.1.2.  Index is TxInteger. */
extern const unsigned RACHWaitSParam[16];
extern const unsigned RACHWaitSParamCombined[16];

std::string data2hex(const unsigned char *data, unsigned nbytes);
std::string inline data2hex(const char *data, unsigned nbytes) { return data2hex((const unsigned char*)data,nbytes); }

}; 	// namespace GSM

#endif
