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
	fp = fopen(filename, "rb"); //������ ���ǵ� ���ڷ� �����̸��̶� ��带 �޴´�, ����� ������ msdnȮ���Ұ�

	if (fp == NULL) { return NULL; }

	int size;
	char* buffer;

	// ���� ũ�⸦ ���ϴ� �κ�
	fseek(fp, 0, SEEK_END); // ���� �����͸� ������ ��ġ�� �̵��մϴ�.
	size = ftell(fp);		// ���� ������ ��ġ�� ��ȯ
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
	int pos = 0; //  ������ġ�� �˻��Ѵ�.

	if (doc[pos] != '{') return; // ������ {�� �����ϴ°�?

	pos++;

	while (pos < size) // ������ġ���� ����ũ�����
	{
		switch (doc[pos])
		{
			case'"':		// "�� �����ϴ� ���ڿ��ϰ��
			{
				char* begin = doc + pos + 1;	// ���ڿ��� ������ġ�� ���Ѵ��� �Ǿ��� "�� �����ҰŴϱ� �״����� ã������ +1
				char* end = strchr(begin, '"');	// ���ڿ����� ��ġ�ϴ� ���ڰ� �ִ��� �˻� / str(A,B) A���� B��ã�Ƽ� B�������� NULL�� ��ȯ �ִٸ� �����ϴ� ���� �����͸� ��ȯ
				if (end == NULL) break;			// ������ NULL�� ��ȯ�ߴٸ� �������ִ�, �׸�

				int stringLength = end - begin; // ""�� ������ ���ڿ��� ���� (���ڿ��� ���������� �޸𸮿� ����Ǵϱ� ���ּ� - �����ּҸ� �ؼ� int ĳ�����ϸ� ũ�Ⱑ ���´�

				json->tokens[tokenIndex].type = TOKEN_STRING; // ��ū�迭�� ���ڿ�Ÿ���� �����Ѵ�.

				json->tokens[tokenIndex].string = (char*)malloc(stringLength + 1); // ���ڿ� ���� + NULL��ŭ ������ �Ҵ��Ѵ�

				memset(json->tokens[tokenIndex].string, 0, stringLength + 1);	// �Ҵ��� ������ �ϴ� 0���� �ʱ�ȭ ���ѵд�.

				memcpy(json->tokens[tokenIndex].string, begin, stringLength);	// 

				tokenIndex++;

				pos = pos + stringLength + 1;
			}
			break;

			case '[':
			{
				pos++;

				while (doc[pos] != ']')	// ���ڿ� �迭�Ľ�
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

			case '0': case '1': case '2': case '3': case '4': case '5':    // ���ڰ� �����̸�
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

				// ��ū ������ �����̴�.
				json->tokens[tokenIndex].type = TOKEN_NUMBER;
				json->tokens[tokenIndex].number = atof(buffer);		// atof�� ���ڿ��� double�� ��ȯ��Ŵ

				free(buffer);

				tokenIndex++;

				pos = pos + stringLength + 1;
			}
			break;
				}
			}
		}
		pos++; // �������ڷ�
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
		if (json->tokens[i].type == TOKEN_STRING && strcmp(json->tokens[i].string, key) == 0)	// strcmp ���ڷ� ���� ���ڿ��� ���Ѵ�. (������� 0�� ��ȯ)
		{
			if (json->tokens[i + 1].type == TOKEN_STRING)
			{
				return json->tokens[i + 1].string; //�ٷδ��� ��ū ���ڿ��� ��ȯ
			}
		}
	}

	return NULL; // Ű�� ��ã���� null�� �ݳ��Ѵ�.
}

int JsonParser::getArrayCount(JSON* json, char* key)
{
	for (int i = 0; i < TOKEN_COUNT; i++)    // ��ū ������ŭ �ݺ�
	{
		// ��ū ������ ���ڿ��̸鼭 ��ū�� ���ڿ��� Ű�� ��ġ�Ѵٸ�
		if (json->tokens[i].type == TOKEN_STRING &&
			strcmp(json->tokens[i].string, key) == 0)
		{
			// �ٷ� ���� ��ū(i + 1)���� isArray�� true�� ��ū�� ������ ��� ��ȯ
			int j = 0;
			while (json->tokens[i + 1 + j].isArray == true)
				j++;

			return j;
		}
	}

	return 0;    // Ű�� ã�� �������� 0�� ��ȯ
}

double JsonParser::getNumber(JSON* json, char* key)
{
	for (int i = 0; i < TOKEN_COUNT; i++)    // ��ū ������ŭ �ݺ�
	{
		// ��ū ������ �����̸鼭 ��ū�� ���ڿ��� Ű�� ��ġ�Ѵٸ�
		if (json->tokens[i].type == TOKEN_STRING &&
			strcmp(json->tokens[i].string, key) == 0)
		{
			// �ٷ� ���� ��ū(i + 1)�� �����̸�
			if (json->tokens[i + 1].type == TOKEN_NUMBER)
				return json->tokens[i + 1].number;    // �ٷ� �ڿ� �ִ� ��ū�� ���� ��ȯ
		}
	}

	return 0.0;    // Ű�� ã�� �������� 0.0�� ��ȯ
}
