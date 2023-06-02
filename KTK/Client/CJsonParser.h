#pragma once
// 제이슨파싱을 위한 클래스를 만들어보자
#pragma once

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#pragma warning(disable:4996)

#define TOKEN_COUNT 2000


class JsonParser
{
public:
	typedef enum _TOKEN_TYPE
	{
		TOKEN_STRING, TOKEN_NUMBER,
	} TOKEN_TYPE;

	typedef struct _TOKEN
	{
		TOKEN_TYPE type;
		union { char* string; double number; };
		bool isArray;

	} TOKEN;

	typedef struct _JSON
	{
		TOKEN tokens[TOKEN_COUNT];
	} JSON;

public:
	JsonParser();
	~JsonParser();

	char* readFile(char* filename, int* readSize);

	void parseJSON(char* doc, int size, JSON* json);

	void freeJSON(JSON* json);

	char* getStirng(JSON* json, char* key);

	int getArrayCount(JSON* json, char* key);

	double getNumber(JSON* json, char* key);    // 키에 해당하는 숫자를 가져오는 함수
};

