/*
 * Set of functions to parse data formatted in "Bare".
 * 
 * Joe.
 */

#include "bare_parser.h"

TParsedBareStruct parseBareFormat(char bareAnswer[])
{
	char* _newPart;
	char* _newSubPart;
	char* _endString;
	char* _endSubString;
	int _expectedPayloadSize = 0;
	TServerAnswer _parsedData = {.acknowledge = 0};

	// Checks Start word
	_newPart = strtok_r(bareAnswer, "$", &_endString);
	if(strcmp((char *)_newPart, "#"))
		return _parsedData;

	// Checks acknowledge is OK
	_newPart = strtok_r(NULL, "$", &_endString);
	if(strcmp((char *)_newPart, "OK"))
		return _parsedData;
	else
		_parsedData.acknowledge = 1;

	// Gets rest of header data
	_newPart = strtok_r(NULL, "$", &_endString);
	_parsedData.ID  = atoi(_newPart);
	_newPart = strtok_r(NULL, "$", &_endString);
	_parsedData.dataType = atoi(_newPart);
	_newPart = strtok_r(NULL, "$", &_endString);
	_expectedPayloadSize = atoi(_newPart);

	switch (_parsedData.dataType)
	{
		// Data is the three status numbers from data-server, same as receiving one set of coordinates
		case 1:
		// Data is a set of positions
		case 2:
		// Creates space in memory for data
		_parsedData.payload = (TPayload*)malloc(sizeof(TPayload) * _expectedPayloadSize);

		_newPart = strtok_r(NULL, "$", &_endString);
		while(_newPart)
		{
			// Finishes when finds the stop word
			if(!strcmp((char *)_newPart, "#"))
				return _parsedData;

			// Extracts X, Y and Z data
			_newSubPart = strtok_r(_newPart, "&", &_endSubString);
			((TPayload *)_parsedData.payload)[_parsedData.dataLength].x = strtof(_newSubPart, NULL);
			_newSubPart = strtok_r(NULL, "&", &_endSubString);
			((TPayload *)_parsedData.payload)[_parsedData.dataLength].y = strtof(_newSubPart, NULL);
			_newSubPart = strtok_r(NULL, "&", &_endSubString);
			((TPayload *)_parsedData.payload)[_parsedData.dataLength].z = strtof(_newSubPart, NULL);

			// Accounts for the new data in the structure
			_parsedData.dataLength ++;

			_newPart = strtok_r(NULL, "$", &_endString);
		}
		break;

		// Data is to be treated as a raw set of chars
		case 3:
		_parsedData.payload = (char*)malloc(sizeof(char) * (_expectedPayloadSize + 1));
		memset(((char *)_parsedData.payload), '\0', _expectedPayloadSize + 1);
		memcpy(((char *)_parsedData.payload), _newPart = strtok_r(NULL, "$", &_endString), sizeof(char) * _expectedPayloadSize);
		_parsedData.dataLength = strlen((char *)_parsedData.payload);
		break;
	}

	return _parsedData;
}
