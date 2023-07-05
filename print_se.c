#include <stdio.h>

// make a funkton to take an argument of size 1 byte and print it
void print_simple(char c) {
    printf("%c\n", c);
}

void print_complex(char *c) {
    // print all characters until we reach a null character using print simple
    while (*c != '\0') {
        // check if the character is the start of a 2 byte utf-8 character
        if ((*c & 0b11100000) == 0b11000000) {
            // check if the next byte is not a null character if it is brake
            if (*(c + 1) == '\0') {
                break;
            }
            // creata a switch that checks if the character is å,ä,ö or Å,Ä,Ö
            switch (*c) {
                case 0b11000010:
                    if (*(c + 1) == 0b10100010) {
                        printf("å\n"); // replase with write(KEY_A_RING)
                        c += 2;
                    }
                    break;
                case 0b11000011:
                    if (*(c + 1) == 0b10100010) {
                        printf("ä\n"); // replase with write(KEY_A_UMLAUT)
                        c += 2;
                    }
                    if (*(c + 1) == 0b10100011) {
                        printf("ö\n"); // replase with write(KEY_O_UMLAUT)
                        c += 2;
                    }
                    break;
                case 0b11000001:
                    if (*(c + 1) == 0b10100010) {
                        // reqires presing and relesing shift
                        printf("Å\n"); // replase with write(KEY_A_RING)
                        c += 2;
                    }
                    if (*(c + 1) == 0b10100011) {
                        // reqires presing and relesing shift
                        printf("Ä\n"); // replase with write(KEY_A_UMLAUT)
                        c += 2;
                    }
                    if (*(c + 1) == 0b10100101) {
                        // reqires presing and relesing shift
                        printf("Ö\n"); // replase with write(KEY_O_UMLAUT)
                        c += 2;
                    }
                    break;
                    // if it is not a special character print the first byte and continue
                default:
                    print_simple(*c); // replase with write(*c)
                    c++;
            }
            continue;
        }

        print_simple(*c); // replase with write(*c)
        c++;
    }

}

int main() {
    // print a string using print_complex that contains a,b,c, å,ä,ö and Å,Ä,Ö
    char str[] = "abcåäöÅÄÖ";
    printf("%s\n", str);
    print_complex(str);
    return 0;
}