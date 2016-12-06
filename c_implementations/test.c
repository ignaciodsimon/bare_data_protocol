#include <stdio.h>
#include <string.h>
#include "bare_parser/bare_parser.h"

/* Structure of a basic Bare message:
 *
 *   #$ <INSTRUCTION> $ <ID> $ <DATA-TYPE> $ <DATA-LENGTH> $ <PAYLOAD-DATA> $
 * 
 * Valid values:
 *
 *   INSTRUCTION: "OK" / "NOK"
 *   ID: integer
 *   DATA-TYPE:
 *     1 : single 3D data set (three floats separated by a "&").
 *     2 : multiple 3D data set (three floats separated by a "&", groups separated by "$").
 *     3 : raw data in chars.
 *   DATA-LENGTH: amount of sets or amount of raw chars the payload contains.
 *   PAYLOAD-DATA: data described previously.
 */

char rawString[] = "#$99$12345$3$10$ABCDEFGHIJ$";

int main(void)
{
	TParsedBareStruct _parsedData;

	_parsedData = parseBareFormat(rawString);
	printf("> Parsed data:\n  INSTRUCTION: %d\n  ID: %d\n  Data type: %d\n  Data length: %d\n  Raw-data: '%s'\n", _parsedData.acknowledge, _parsedData.ID,
		_parsedData.dataType, _parsedData.dataLength, (char*)_parsedData.payload);

	return 0;
}

