#include "..\Headers\languagemanager.h"
#include <stdio.h>
#include <stdarg.h>
using namespace rapidxml;

LanguageManager * LanguageManager::languageManager = nullptr;

LanguageManager & LanguageManager::Instance()
{
	if (!languageManager)
		languageManager = new LanguageManager();
	return *languageManager;
}

void LanguageManager::LoadLanguage(Language lang)
{
	String mapInfo;
	switch (lang)
	{
	case LanguageManager::ES:
		mapInfo = String::Read("lang/ES.txt");
		break;
	case LanguageManager::EN:
		mapInfo = String::Read("lang/EN.txt");
		break;
	default:
		break;
	}
	xml_document<> doc;

	doc.parse<0>((char*)mapInfo.ToCString());
	dictionary = *(doc.first_node("Dictionary"));
}

String * LanguageManager::GetString(String code, int nParams, ...)
{
	String * stringOriginal, *StringReturn;
	va_list vl;
	va_start(vl, nParams);
	stringOriginal = new String(dictionary.first_node(code.ToCString())->first_attribute("value")->value());
	int charPos = 0;
	while (charPos < stringOriginal->Length()) {
		if ((*stringOriginal)[charPos] == '%') {
			if ((*stringOriginal)[charPos + 1] == '{') {
				if (atoi(&(*stringOriginal)[charPos + 2]) < nParams) {
					(*StringReturn) += vl[(*stringOriginal)[charPos + 2]];
				}
				charPos += 3;
			}
			else {
				(*StringReturn) += (*stringOriginal)[charPos];
			}
		}
		else {
			(*StringReturn) += (*stringOriginal)[charPos];
		}
		charPos++;
	}
	va_end(vl);
	return StringReturn;
}
