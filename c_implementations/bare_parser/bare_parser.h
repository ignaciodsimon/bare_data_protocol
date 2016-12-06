/*
 * Set of functions to parse data formatted in "Bare".
 *
 * Joe.
 */

#ifndef BARE_PARSER_H_
#define BARE_PARSER_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct{
    int acknowledge ;
    int ID;
    int dataType;
    int dataLength;
    void* payload;
}TParsedBareStruct;

/*
 * Parses raw answer from the server in "Bare" format
 */
TParsedBareStruct parseBareFormat(char* bareAnswer);

#endif
