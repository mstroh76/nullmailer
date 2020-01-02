#include "inifile.h"
#include <string.h>
#include <stdlib.h>


void CINIFile::Trim(char* szInput) {
	TrimLeft(szInput);
	TrimRight(szInput);
}

void CINIFile::TrimLeft(char* szInput) {
	
	int length = (int)strlen(szInput);
	int count=0;
	while (szInput[count]==' ' || szInput[count]=='\t') {
		count++;
	}
	memmove(szInput, &szInput[count], length-count);
	szInput[length-count] = '\0';
}

void CINIFile::TrimRight(char* szInput) {

	int length = (int)strlen(szInput);
	int count = length-1;
	while (szInput[count]==' ' || szInput[count]=='\t' || szInput[count]=='\n' || szInput[count]=='\r') {
		count--;
	}
	szInput[count+1] = '\0';
}


CINIFile::CINIFile() {

	m_cOptionSeparator = '=';
}


void CINIFile::SetINIFilename(const char* szINIFilename) {

	strncpy(m_szINIFilename, szINIFilename, MAX_PATH);
	m_szINIFilename[MAX_PATH]='\0';
}


FILE* CINIFile::GetFile() {

	if (strlen(m_szINIFilename)<=0) {
		return(NULL);
	}
	FILE* ini_file = fopen(m_szINIFilename, "rb");
	return(ini_file);
}

int CINIFile::Valid() {

	FILE* ini_file = GetFile();
	if (ini_file) {
		fclose(ini_file);
		return(TRUE);
	} else { 
		return(FALSE);
	}
}

int CINIFile::GetBoolValue(int &bValue, const char* szType) {
	char szBuffer[255+1];

	if (GetStringValue(szBuffer,szType,255)) {
		Trim(szBuffer);
		if (!strcasecmp(szBuffer, "true") || !strcasecmp(szBuffer, "1")) {
			bValue = 1;
		} else if (!strcasecmp(szBuffer, "false") || !strcasecmp(szBuffer, "0")) {
			bValue = 0;
		} else {
			return(FALSE);
		}
		return(TRUE);
	} else {
		return(FALSE);
	}
}

int CINIFile::GetIntValue(int &nValue, const char* szType) {
	char szBuffer[255+1];

	if (GetStringValue(szBuffer,szType,255)) {
		nValue=atoi(szBuffer);
		return(TRUE);
	} else {
		return(FALSE);
	}
}

int CINIFile::GetStringValue(char* szValue, const char* szType, int nMaxSize) {
	char szLinebuffer[MAX_PATH+1];

	szValue[0] = '\0';
	FILE* ini_file = GetFile();
	if (!ini_file) {
		return(FALSE);
	}

	while (fgets(szLinebuffer,MAX_PATH,ini_file)) {
		Trim(szLinebuffer);
		if (szLinebuffer[0]=='#' || szLinebuffer[0]=='\0') {		
			continue;
		}
		if (strncasecmp(szLinebuffer, szType, strlen(szType))==0) {
			int count = (int)strlen(szType);
			while (szLinebuffer[count]==' ' || szLinebuffer[count]=='\t') {
				count++;
			}
			if (szLinebuffer[count]==m_cOptionSeparator) {
				strncpy(szValue, &szLinebuffer[count+1], nMaxSize);
				szValue[nMaxSize]='\0';
				TrimLeft(szValue);
				if (ini_file) {
					fclose(ini_file);
					ini_file = NULL;
				}
				return(TRUE);
			}
		}
	}
	if (ini_file) {
		fclose(ini_file);
		ini_file = NULL;
	}
	return(FALSE);
}

