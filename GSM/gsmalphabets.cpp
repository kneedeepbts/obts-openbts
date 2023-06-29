#include "gsmalphabets.h"

#include <cstdlib>

namespace kneedeepbts::gsm {
    unsigned char encodeGsmChar(unsigned char ascii) {
        // Given an ASCII char, return the corresponding GSM char.
        // Do it with a lookup table, generated on the first call.
        // You might be tempted to replace this init with some more clever NULL-pointer trick.
        // -- Don't.  This is thread-safe.
        static char reverseTable[256] = {'?'};
        static volatile bool init = false;
        if (!init) {
            for (size_t i = 0; i < sizeof(gGsmAlphabet); i++) {
                reverseTable[(unsigned) gGsmAlphabet[i]] = i;
            }
            // Set the flag last to be thread-safe.
            init = true;
        }
        return reverseTable[(unsigned) ascii];
    }

    char encodeBcdChar(char ascii) {
        // Given an ASCII char, return the corresponding BCD.
        if ((ascii >= '0') && (ascii <= '9')) return ascii - '0';
        switch (ascii) {
            case '.':
                return 11;
            case '*':
                return 11;
            case '#':
                return 12;
            case 'a':
                return 13;
            case 'b':
                return 14;
            case 'c':
                return 15;
            default:
                return 15;
        }
    }
}