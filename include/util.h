#ifndef UTIL_H
#define UTIL_H

struct Util {
    static int parseASCIINumber(char string[]) {
        int num = 0;
        int i = 0;
        while(string[i] != '\0') {
            int asciiInt = string[i] - '0';
            if(asciiInt >= 0 && asciiInt <= 9) {
                num *= 10;
                num += asciiInt;
            }

            i++;
        }

        return num;
    }

    static bool strStartsWith(char str[], char startswith[]) {
        // Source: https://stackoverflow.com/a/4770992
        return strncmp(startswith, str, strlen(startswith)) == 0;
    }
};

#endif
