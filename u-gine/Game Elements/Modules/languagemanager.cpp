#include "..\Headers\languagemanager.h"
#include "../../lib/rapidxml.hpp"
#include <stdio.h>
#include <stdarg.h>
using namespace rapidxml;
extern LanguageManager::Language lang;

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
	xml_node<> * xmlDictionary;
	xml_node<>* entrie;
	String key, value;
	doc.parse<0>((char*)mapInfo.ToCString());
	xmlDictionary = doc.first_node("Dictionary");
	entrie = xmlDictionary->first_node("entrie");
	dictionary.clear();
	while (entrie)
	{
		key=entrie->first_attribute("key")->value();
		value= entrie->first_attribute("value")->value();
		dictionary.insert(std::pair<String, String>(key, value));
		entrie = entrie->next_sibling("entrie");
	}

}

String LanguageManager::GetString(String code, int nParams, ...)
{
	String stringOriginal, StringReturn;
	va_list vl;
	va_start(vl, nParams);
	stringOriginal = dictionary.at(code);
	int charPos = 0;
	while (charPos < stringOriginal.Length()) {
		if (stringOriginal[charPos] == '%') {
			if (stringOriginal[charPos + 1] == '{') {
				if (atoi(&stringOriginal[charPos + 2]) < nParams) {
					StringReturn += va_arg(vl, String);
				}
				charPos += 3;
			}
			else {
				StringReturn += stringOriginal[charPos];
			}
		}
		else {
			StringReturn += stringOriginal[charPos];
		}
		charPos++;
	}
	va_end(vl);
	return StringReturn;
}
