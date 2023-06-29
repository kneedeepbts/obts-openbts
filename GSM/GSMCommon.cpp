/*
* Copyright 2008 Free Software Foundation, Inc.
* Copyright 2011, 2013, 2014 Range Networks, Inc.
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

#define LOG_GROUP LogGroup::GSM		// Can set Log.Level.GSM for debugging

#include "GSMCommon.h"

using namespace GSM;
using namespace std;


ostream& GSM::operator<<(ostream& os, L3PD val)
{
	switch (val) {
		case L3CallControlPD: os << "Call Control"; break;
		case L3MobilityManagementPD: os << "Mobility Management"; break;
		case L3RadioResourcePD: os << "Radio Resource"; break;
		default: os << hex << "0x" << (int)val << dec;
	}
	return os;
}


//const BitVector GSM::gTrainingSequence[] = {
//    BitVector("00100101110000100010010111"),
//    BitVector("00101101110111100010110111"),
//    BitVector("01000011101110100100001110"),
//    BitVector("01000111101101000100011110"),
//    BitVector("00011010111001000001101011"),
//    BitVector("01001110101100000100111010"),
//    BitVector("10100111110110001010011111"),
//    BitVector("11101111000100101110111100"),
//};

//// (pat) Dummy Burst defined in GSM 5.02 5.2.6
//// From 5.02 6.5.1: A base transceiver station must transmit a burst in every timeslot of every TDMA frame in the downlink of
//// radio frequency channel C0 of the cell allocation (to allow mobiles to make power measurements of the radio
//// frequency channels supporting the BCCH, see GSM 05.08). In order to achieve this requirement a dummy
//// burst is defined in clause 5.2.6 which shall be transmitted by the base transceiver station on all timeslots of all
//// TDMA frames of radio frequency channel C0 for which no other channel requires a burst to be transmitted.
//// (pat) But this is probably not correct for an idle SACCH, where we should be delivering L2 idle frames.
//const BitVector GSM::gDummyBurst("0001111101101110110000010100100111000001001000100000001111100011100010111000101110001010111010010100011001100111001111010011111000100101111101010000");
//
//const BitVector GSM::gRACHSynchSequence("01001011011111111001100110101010001111000");

// Must be unsigned char, not signed char, or the conversion in sprintf below will be negative
string GSM::data2hex(const unsigned char *data, unsigned nbytes)
{
	//LOG(DEBUG) << LOGVAR(nbytes);
	string result;
	result.reserve(2+2*nbytes);
	result.append("0x");
	if (nbytes == 0) { result.append("0"); return result; }
	for (unsigned i = 0; i < nbytes; i++) {
		char buf[20];	// Paranoid, only need 3.
		sprintf(buf,"%02x",*data++);
		//LOG(DEBUG) << LOGVAR(buf) <<LOGVAR(result);
		result.append(buf);
	}
	return result;
}

ostream& GSM::operator<<(ostream& os, TypeOfNumber type)
{
	switch (type) {
		case UnknownTypeOfNumber: os << "unknown"; break;
		case InternationalNumber: os << "international"; break;
		case NationalNumber: os << "national"; break;
		case NetworkSpecificNumber: os << "network-specific"; break;
		case ShortCodeNumber: os << "short code"; break;
		default: os << "?" << (int)type << "?";
	}
	return os;
}

ostream& GSM::operator<<(ostream& os, NumberingPlan plan)
{
	switch (plan) {
		case UnknownPlan: os << "unknown"; break;
		case E164Plan: os << "E.164/ISDN"; break;
		case X121Plan: os << "X.121/data"; break;
		case F69Plan: os << "F.69/Telex"; break;
		case NationalPlan: os << "national"; break;
		case PrivatePlan: os << "private"; break;
		default: os << "?" << (int)plan << "?";
	}
	return os;
}

ostream& GSM::operator<<(ostream& os, MobileIDType wID)
{
	switch (wID) {
		case NoIDType: os << "None"; break;
		case IMSIType: os << "IMSI"; break;
		case IMEIType: os << "IMEI"; break;
		case TMSIType: os << "TMSI"; break;
		case IMEISVType: os << "IMEISV"; break;
		default: os << "?" << (int)wID << "?";
	}
	return os;
}

ostream& GSM::operator<<(ostream& os, TypeAndOffset tao)
{
	switch (tao) {
		case TDMA_MISC: os << "(misc)"; break;
		case TCHF_0: os << "TCH/F"; break;
		case TCHH_0: os << "TCH/H-0"; break;
		case TCHH_1: os << "TCH/H-1"; break;
		case SDCCH_4_0: os << "SDCCH/4-0"; break;
		case SDCCH_4_1: os << "SDCCH/4-1"; break;
		case SDCCH_4_2: os << "SDCCH/4-2"; break;
		case SDCCH_4_3: os << "SDCCH/4-3"; break;
		case SDCCH_8_0: os << "SDCCH/8-0"; break;
		case SDCCH_8_1: os << "SDCCH/8-1"; break;
		case SDCCH_8_2: os << "SDCCH/8-2"; break;
		case SDCCH_8_3: os << "SDCCH/8-3"; break;
		case SDCCH_8_4: os << "SDCCH/8-4"; break;
		case SDCCH_8_5: os << "SDCCH/8-5"; break;
		case SDCCH_8_6: os << "SDCCH/8-6"; break;
		case SDCCH_8_7: os << "SDCCH/8-7"; break;
		case TDMA_BEACON: os << "BCH"; break;
		case TDMA_BEACON_BCCH: os << "BCCH"; break;
		case TDMA_BEACON_CCCH: os << "CCCH"; break;
		case TDMA_PDCH: os << "PDCH"; break;
		case TDMA_PACCH: os << "PACCH"; break;
		case TDMA_PTCCH: os << "PTCCH"; break;
		case TDMA_PDIDLE: os << "PDIDLE"; break;
		default: os << "?" << (int)tao << "?";
	}
	return os;
}

ostream& GSM::operator<<(ostream& os, ChannelType val)
{
	switch (val) {
		case UndefinedCHType: os << "undefined"; return os;
		case SCHType: os << "SCH"; break;
		case FCCHType: os << "FCCH"; break;
		case BCCHType: os << "BCCH"; break;
		case RACHType: os << "RACH"; break;
		case SDCCHType: os << "SDCCH"; break;
		case FACCHType: os << "FACCH"; break;
		case CCCHType: os << "CCCH"; break;
		case SACCHType: os << "SACCH"; break;
		case TCHFType: os << "TCH/F"; break;
		case TCHHType: os << "TCH/H"; break;
		case AnyTCHType: os << "any TCH"; break;
		case LoopbackFullType: os << "Loopback Full"; break;
		case LoopbackHalfType: os << "Loopback Half"; break;
		case PDTCHCS1Type: os << "PDTCHCS1"; break;
		case PDTCHCS2Type: os << "PDTCHCS2"; break;
		case PDTCHCS3Type: os << "PDTCHCS3"; break;
		case PDTCHCS4Type: os << "PDTCHCS4"; break;
		case PSingleBlock1PhaseType: os << "GPRS_SingleBlock1Phase"; break;
		case PSingleBlock2PhaseType: os << "GPRS_SingleBlock2Phase"; break;
		case AnyDCCHType: os << "any DCCH"; break;
		default: os << "?" << (int)val << "?"; break;
	}
	return os;
}
