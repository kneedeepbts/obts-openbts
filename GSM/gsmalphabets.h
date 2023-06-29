#ifndef OBTS_OPENBTS_GSMALPHABETS_H
#define OBTS_OPENBTS_GSMALPHABETS_H

namespace kneedeepbts::gsm {
    enum GsmAlphabet {
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
    static const unsigned char gGsmAlphabet[] = "@\243$\245\350\351\371\354\362\347\n\330\370\r\305\345D_FGLOPCSTZ \306\346\337\311 !\"#\244%&\'()*+,-./0123456789:;<=>?\241ABCDEFGHIJKLMNOPQRSTUVWXYZ\304\326\321\334\247\277abcdefghijklmnopqrstuvwxyz\344\366\361\374\341";

    unsigned char encodeGsmChar(unsigned char ascii);

    inline unsigned char decodeGsmChar(unsigned char sms) {
        return gGsmAlphabet[(unsigned)sms];
    }

    /**@name BCD-ASCII mapping, GMS 04.08 Table 10.5.118. */
    /** Indexed by BCD, returns ASCII. */
    static const char gBcdAlphabet[] = "0123456789.#abc";

    char encodeBcdChar(char ascii);

    inline char decodeBcdChar(char bcd) {
        return gBcdAlphabet[(unsigned)bcd];
    }
}

#endif //OBTS_OPENBTS_GSMALPHABETS_H
