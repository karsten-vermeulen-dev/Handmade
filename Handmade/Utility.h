#pragma once

//This code usually resides in the stdafx.h file and 
//sets the manifest so that the modern Windows controls 
//are used. If this is missing dialog boxes will look old
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include <Windows.h>
#include <map>
#include <string>
#include <vector>
#include "Vector.h"

class Utility
{

public:

	enum class Severity
	{
		Failure = MB_ICONERROR,
		Warning = MB_ICONWARNING,
		Default = MB_ICONINFORMATION
	};

	enum class Destination
	{
		LogFile,
		OutputWindow,
		WindowsMessageBox
	};

	static void SetWindowHandle(HWND windowHandle);

	static void RemoveCharacter(std::string& string, char character);

	static void ParseString(std::string& string,
		std::vector<std::string>& subStrings, char token);

	static bool LoadConfigFile(const std::string& filename,
		std::map<std::string, std::string>& dataMap);

	static void Log(Destination destination,
		float value, const std::string& label = "");
	static void Log(Destination destination,
		const Vector<float>& value, const std::string& label = "");
	static void Log(Destination destination,
		const std::string& message, Severity severity = Severity::Default);
	static void Log(Destination destination,
		float x, float y, const std::string& label = "");

private:

	static HWND windowHandle;

};