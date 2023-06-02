#include "CJsonParser.h"

JsonParser::JsonParser()
{
}

JsonParser::~JsonParser()
{

}

char* JsonParser::readFile(char* filename, int* readSize)
{
	FILE* fp;
	fp = fopen(filename, "rb"); //파일을 열건데 인자로 파일이름이랑 모드를 받는다, 모드의 종류는 msdn확인할것

	if (fp == NULL) { return NULL; }

	int size;
	char* buffer;

	// 파일 크기를 구하는 부분
	fseek(fp, 0, SEEK_END); // 파일 포인터를 지정된 위치로 이동합니다.
	size = ftell(fp);		// 현재 파일의 위치를 반환
	fseek(fp, 0, SEEK_SET);

	buffer = (char*)malloc(size + 1);

	memset(buffer, 0, size + 1);

	if (fread(buffer, size, 1, fp) < 1)
	{
		*readSize = 0;
		free(buffer);
		fclose(fp);
		return NULL;
	}

	*readSize = size;

	fclose(fp);

	return buffer;

}

void JsonParser::parseJSON(char* doc, int size, JSON* json)
{
	int tokenIndex = 0;
	int pos = 0; //  문자위치를 검색한다.

	if (doc[pos] != '{') return; // 문서가 {로 시작하는가?

	pos++;

	while (pos < size) // 시작위치부터 문서크기까지
	{
		switch (doc[pos])
		{
			case'"':		// "로 시작하는 문자열일경우
			{
				char* begin = doc + pos + 1;	// 문자열의 시작위치를 구한다음 맨앞이 "로 시작할거니까 그다음을 찾기위한 +1
				char* end = strchr(begin, '"');	// 문자열내에 일치하는 문자가 있는지 검사 / str(A,B) A에서 B를찾아서 B가없으면 NULL을 반환 있다면 존재하는 곳의 포인터를 반환
				if (end == NULL) break;			// 위에서 NULL을 반환했다면 문제가있다, 그만

				int stringLength = end - begin; // ""를 제외한 문자열의 길이 (문자열은 순차적으로 메모리에 저장되니까 끝주소 - 시작주소를 해서 int 캐스팅하면 크기가 나온다

				json->tokens[tokenIndex].type = TOKEN_STRING; // 토큰배열에 문자열타입을 저장한다.

				json->tokens[tokenIndex].string = (char*)malloc(stringLength + 1); // 문자열 길이 + NULL만큼 공간을 할당한다

				memset(json->tokens[tokenIndex].string, 0, stringLength + 1);	// 할당한 공간에 일단 0으로 초기화 시켜둔다.

				memcpy(json->tokens[tokenIndex].string, begin, stringLength);	// 

				tokenIndex++;

				pos = pos + stringLength + 1;
			}
			break;

			case '[':
			{
				pos++;

				while (doc[pos] != ']')	// 문자열 배열파싱
				{
					if (doc[pos] == '"')
					{
						char* begin = doc + pos + 1;
						char* end = strchr(begin, '"');
						if (end == NULL) break;

						int stringLength = end - begin;

						json->tokens[tokenIndex].type = TOKEN_STRING;
						json->tokens[tokenIndex].string = (char*)malloc(stringLength + 1);
						json->tokens[tokenIndex].isArray = true;
						memset(json->tokens[tokenIndex].string, 0, stringLength + 1);

						memcpy(json->tokens[tokenIndex].string, begin, stringLength);

						tokenIndex++;

						pos = pos + stringLength + 1;
					}
					break;

			case '0': case '1': case '2': case '3': case '4': case '5':    // 문자가 숫자이면
			case '6': case '7': case '8': case '9': case '-':
			{
				char* begin = doc + pos;
				char* end;
				char* buffer;

				end = strchr(begin, ',');
				if (end == NULL)
				{
					end = strchr(doc + pos, '}');
					if (end == NULL) break;
				}

				int stringLength = end - begin;

				buffer = (char*)malloc(stringLength + 1);

				memset(buffer, 0, stringLength + 1);

				memcpy(buffer, begin, stringLength);

				// 토큰 종류는 숫자이다.
				json->tokens[tokenIndex].type = TOKEN_NUMBER;
				json->tokens[tokenIndex].number = atof(buffer);		// atof는 문자열을 double로 변환시킴

				free(buffer);

				tokenIndex++;

				pos = pos + stringLength + 1;
			}
			break;
				}
			}
		}
		pos++; // 다음문자로
	}
}

void JsonParser::freeJSON(JSON* json)
{
	for (int i = 0; i < TOKEN_COUNT; ++i)
	{
		if (json->tokens[i].type == TOKEN_STRING)
			free(json->tokens[i].string);
	}
}

char* JsonParser::getStirng(JSON* json, char* key)
{
	for (int i = 0; i < TOKEN_COUNT; ++i)
	{
		if (json->tokens[i].type == TOKEN_STRING && strcmp(json->tokens[i].string, key) == 0)	// strcmp 인자로 들어온 문자열을 비교한다. (같을경우 0을 반환)
		{
			if (json->tokens[i + 1].type == TOKEN_STRING)
			{
				return json->tokens[i + 1].string; //바로다음 토큰 문자열을 반환
			}
		}
	}

	return NULL; // 키를 못찾으면 null을 반납한다.
}

int JsonParser::getArrayCount(JSON* json, char* key)
{
	for (int i = 0; i < TOKEN_COUNT; i++)    // 토큰 개수만큼 반복
	{
		// 토큰 종류가 문자열이면서 토큰의 문자열이 키와 일치한다면
		if (json->tokens[i].type == TOKEN_STRING &&
			strcmp(json->tokens[i].string, key) == 0)
		{
			// 바로 뒤의 토큰(i + 1)부터 isArray가 true인 토큰의 개수를 세어서 반환
			int j = 0;
			while (json->tokens[i + 1 + j].isArray == true)
				j++;

			return j;
		}
	}

	return 0;    // 키를 찾지 못했으면 0을 반환
}

double JsonParser::getNumber(JSON* json, char* key)
{
	for (int i = 0; i < TOKEN_COUNT; i++)    // 토큰 개수만큼 반복
	{
		// 토큰 종류가 숫자이면서 토큰의 문자열이 키와 일치한다면
		if (json->tokens[i].type == TOKEN_STRING &&
			strcmp(json->tokens[i].string, key) == 0)
		{
			// 바로 뒤의 토큰(i + 1)이 숫자이면
			if (json->tokens[i + 1].type == TOKEN_NUMBER)
				return json->tokens[i + 1].number;    // 바로 뒤에 있는 토큰의 숫자 반환
		}
	}

	return 0.0;    // 키를 찾지 못했으면 0.0을 반환
}
