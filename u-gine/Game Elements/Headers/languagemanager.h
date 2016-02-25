#ifndef WORLDDEFENDER_LANGUAGEMANAGER_H
#define WORLDDEFENDER_LANGUAGEMANAGER_H
#include "../../include/string.h"
#include <map>
class LanguageManager
{
public:
	enum Language {
		ES,
		EN
	};
	static LanguageManager& Instance();
	void LoadLanguage(Language lang);
	String GetString(String code, int nParams, ...);
protected:
	LanguageManager() {};
	~LanguageManager() {};
private:
	static LanguageManager * languageManager;
	std::map<String, String> dictionary;
};
#endif // !WORLDDEFENDER_LANGUAGEMANAGER_H

