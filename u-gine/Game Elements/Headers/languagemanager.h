#ifndef WORLDDEFENDER_LANGUAGEMANAGER_H
#define WORLDDEFENDER_LANGUAGEMANAGER_H
#include "../../lib/rapidxml.hpp"
#include "../../include/string.h"
using namespace rapidxml;
class LanguageManager
{
public:
	enum Language {
		ES,
		EN
	};
	static LanguageManager& Instance();
	void LoadLanguage(Language lang);
	String * GetString(String code, int nParams, ...);
protected:
	LanguageManager() {};
	~LanguageManager() {};
private:
	static LanguageManager * languageManager;
	xml_node<> dictionary;
};
#endif // !WORLDDEFENDER_LANGUAGEMANAGER_H

