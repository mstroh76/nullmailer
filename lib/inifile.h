#ifndef __INI_FILE_H__
#define __INI_FILE_H__

#include <stdio.h>

#ifndef MAX_PATH
#define MAX_PATH 1024
#endif

#ifndef BOOL
#define BOOL int
#endif

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

class CINIFile {
	private:
		char m_szINIFilename[MAX_PATH+1];
		char m_cOptionSeparator;

	private:
		FILE* GetFile();
		void Trim(char* szInput);
		void TrimLeft(char* szInput);
		void TrimRight(char* szInput);

	public:
		CINIFile();
		int Valid();
		int GetStringValue(char* szValue, const char* szType, int nMaxSize);
		int GetBoolValue(int &bValue, const char* szType);
		int GetIntValue(int &nValue, const char* szType);
		void SetINIFilename(const char* szINIFilename);
		void SetOptionSeparator(char cOptionSeparator) { 
			m_cOptionSeparator = cOptionSeparator; 
		};
};


#endif //__INI_FILE_H__

