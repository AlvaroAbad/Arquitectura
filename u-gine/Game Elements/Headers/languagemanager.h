#ifndef WORLDDEFENDER_LANGUAGEMANAGER_H
#define WORLDDEFENDER_LANGUAGEMANAGER_H
class LanguageManager
{
public:
	enum Language {
		ES,
		EN
	};
	LanguageManager& Instance();
	void LoadLanguage(Language lang);
	void GetString();
protected:
	LanguageManager();
	~LanguageManager();
private:
	static LanguageManager * languageManager;
};
#endif // !WORLDDEFENDER_LANGUAGEMANAGER_H

