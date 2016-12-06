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

/*
 * Structures used to move data once parsed.
 */
typedef struct{
    int acknowledge ;
    int ID;
    int dataType;
    int dataLength;
    void* payload;
}TParsedBareStruct;

typedef struct{
	float x;
	float y;
	float z;
}TPayload3D;

/*
 * Parses raw answer from the server in "Bare" format
 */
extern TParsedBareStruct parseBareFormat(char* bareAnswer);

#endif
