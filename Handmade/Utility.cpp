#include <assert.h>
#include <fstream>
#include <string>
#include "Utility.h"

HWND Utility::windowHandle = nullptr;
//======================================================================================================
void Utility::SetWindowHandle(HWND windowHandle)
{
	windowHandle = windowHandle;
}
//======================================================================================================
void Utility::RemoveCharacter(std::string& string, char character)
{
	auto it = std::find(string.begin(), string.end(), character);

	if (it != string.end())
	{
		do
		{
			string.erase(it);
			it = std::find(string.begin(), string.end(), character);
		} while (it != string.end());
	}
}
//======================================================================================================
void Utility::ParseString(std::string& string, std::vector<std::string>& subStrings, char token)
{
	size_t start = 0;
	size_t end = 0;

	assert(!string.empty());

	while (end != std::string::npos)
	{
		end = string.find(token, start);
		if ((end - start) > 0)
		{
			subStrings.push_back(string.substr(start, end - start));
		}
		start = end + 1;
	}
}
//======================================================================================================
bool Utility::LoadConfigFile(const std::string& filename, std::map<std::string, std::string>& dataMap)
{
	std::fstream file(filename, std::ios_base::in);

	if (!file.is_open())
	{
		return false;
	}

	std::string line;

	while (!file.eof())
	{
		std::getline(file, line);
		std::vector<std::string> subStrings;
		ParseString(line, subStrings, '=');

		if (!subStrings.empty())
		{
			dataMap[subStrings[0]] = subStrings[1];
		}
	}

	file.close();
	return true;
}
//======================================================================================================
void Utility::Log(Destination destination, const Vector<float>& value, const std::string& label)
{
	Log(destination, value.x, value.y, label);
}
//======================================================================================================
void Utility::Log(Destination destination, float value, const std::string& label)
{
	if (!label.empty())
	{
		if (destination == Destination::WindowsMessageBox)
		{
			MessageBox(windowHandle,
				reinterpret_cast<LPCSTR>(std::to_string(value).c_str()),
				reinterpret_cast<LPCSTR>(label.c_str()),
				MB_ICONINFORMATION | MB_OK);
		}

		else if (destination == Destination::OutputWindow)
		{
			std::string message = "[" + label + "] " + std::to_string(value) + "\n";
			OutputDebugString(reinterpret_cast<LPCSTR>(message.c_str()));
		}

		else if (destination == Destination::LogFile)
		{
			std::fstream file("Data/Output.log", std::ios_base::out | std::ios_base::app);
			std::string message = "[" + label + "] " + std::to_string(value) + "\n";
			file << message;
			file.close();
		}
	}
}
//======================================================================================================
void Utility::Log(Destination destination, const std::string& message, Severity severity)
{
	if (!message.empty())
	{
		if (destination == Destination::WindowsMessageBox)
		{
			MessageBox(windowHandle,
				reinterpret_cast<LPCSTR>(message.c_str()),
				"Log", static_cast<int>(severity) | MB_OK);
		}

		else if (destination == Destination::OutputWindow)
		{
			std::string finalMessage;

			if (severity == Severity::Failure)
			{
				finalMessage = "[FAILURE] " + message + "\n";
			}

			else if (severity == Severity::Warning)
			{
				finalMessage = "[WARNING] " + message + "\n";
			}

			else
			{
				finalMessage = message + "\n";
			}

			OutputDebugString(reinterpret_cast<LPCSTR>(finalMessage.c_str()));
		}

		else if (destination == Destination::LogFile)
		{
			std::string finalMessage;
			std::fstream file("Data/Output.log", std::ios_base::out | std::ios_base::app);

			if (severity == Severity::Failure)
			{
				finalMessage = "[FAILURE] " + message + "\n";
			}

			else if (severity == Severity::Warning)
			{
				finalMessage = "[WARNING] " + message + "\n";
			}

			else
			{
				finalMessage = message + "\n";
			}

			file << finalMessage;
			file.close();
		}
	}
}
//======================================================================================================
void Utility::Log(Destination destination, float x, float y, const std::string& label)
{
	if (!label.empty())
	{
		if (destination == Destination::WindowsMessageBox)
		{
			std::string message = "x = " + std::to_string(x) +
				", y = " + std::to_string(y);

			MessageBox(windowHandle,
				reinterpret_cast<LPCSTR>(message.c_str()),
				reinterpret_cast<LPCSTR>(message.c_str()),
				MB_ICONINFORMATION | MB_OK);
		}

		else if (destination == Destination::OutputWindow)
		{
			std::string message = "[" + label + "] " + "x = " + std::to_string(x) +
				", y = " + std::to_string(y) + "\n";
			OutputDebugString(reinterpret_cast<LPCSTR>(message.c_str()));
		}

		else if (destination == Destination::LogFile)
		{
			std::fstream file("Data/Output.log", std::ios_base::out | std::ios_base::app);
			std::string message = "[" + label + "] " + "x = " + std::to_string(x) +
				", y = " + std::to_string(y) + "\n";
			file << message;
			file.close();
		}
	}
}

//======================================================================================================
//OLD binary resource loading code (WIP)
//======================================================================================================

//bool ReadResourceData(const string& filename, int fileIndex)
//{
//	unsigned int filePosition = 0;
//	m_file.open(filename, iobase::binary);
//
//	if (!m_file)
//	{
//		return false;
//	}
//
//	//if index position passed is not the first position in file
//	if (fileIndex > 0)
//	{
//		//loop through all data in file until correct file index position is found
//		for (int i = 0; i < fileIndex; i++)
//		{
//			m_file.seekg(filePosition);
//			m_file.read((char*)&m_dataBufferSize, 4);
//			filePosition += m_dataBufferSize += 4;
//		}
//	}
//
//	//seek to correct index position in file and read in size value of binary data
//	m_file.seekg(filePosition);
//	m_file.read((char*)&m_dataBufferSize, 4);
//
//	//allocate memory according to binary data size
//	m_dataBuffer = (char*)malloc(m_dataBufferSize);
//
//	//read in binary data and store in data buffer
//	m_file.read(m_dataBuffer, m_dataBufferSize);
//
//	//close binary file
//	m_file.close();
//
//	return true;
//}
////======================================================================================================
//Mix_Chunk* LoadSFXResource(const string& filename, int fileIndex)
//{
//	if (!ReadResourceData(filename, fileIndex))
//	{
//		//Error!
//	}
//
//	else
//	{
//		//read image data from buffer into Rwops struct
//		m_RW = SDL_RWFromMem(m_dataBuffer, m_dataBufferSize);
//
//		//add audio buffer to vector to keep track of the data which stays in memory as long as audio data is used
//		//this is because there is streaming between the buffer, RWops struct and actual audio data 
//		m_dataBufferManager.push_back(m_dataBuffer);
//
//		//load sfx data from RWops struct
//		m_sfxData = Mix_LoadWAV_RW(m_RW, 1);
//
//		//if sfx loading failed, display error message and return false
//		if (!m_sfxData)
//		{
//			DisplayError("Resource File Error", "Resource file \"" + filename + "\" could not be loaded.");
//		}
//	}
//
//	return m_sfxData;
//}
////======================================================================================================
//Mix_Music* LoadMusicResource(const string& filename, int fileIndex)
//{
//	if (!ReadResourceData(filename, fileIndex))
//	{
//		//Error!
//	}
//
//	else
//	{
//		//read image data from buffer into Rwops struct
//		m_RW = SDL_RWFromMem(m_dataBuffer, m_dataBufferSize);
//
//		//add audio buffer to vector to keep track of the data which stays in memory as long as audio data is used
//		//this is because there is streaming between the buffer, RWops struct and actual audio data 
//		m_dataBufferManager.push_back(m_dataBuffer);
//
//		//load music data from RWops struct
//		m_musicData = Mix_LoadMUS_RW(m_RW);
//
//		//if music loading failed, display error message and return false
//		if (!m_musicData)
//		{
//			DisplayError("Resource File Error", "Resource file \"" + filename + "\" could not be loaded.");
//		}
//	}
//
//	return m_musicData;
//}
////======================================================================================================
//SDL_Surface* LoadImageResource(const string& filename, int fileIndex)
//{
//	if(!ReadResourceData(filename, fileIndex))
//	{
//		//Error!
//	}
//
//	else
//	{
//		//read image data from buffer into Rwops struct
//		m_RW = SDL_RWFromMem(m_dataBuffer, m_dataBufferSize);
//
//		//assign image data of Rwops to SDL surface pointer
//		m_imageData = IMG_Load_RW(m_RW, 1);
//
//		//free raw binary image data from memory
//		free(m_dataBuffer);
//
//		//if image loading failed, display error message and return false
//		if(!m_imageData)
//		{
//			DisplayError("Resource File Error", "Resource file \"" + filename + "\" could not be loaded.");
//		}
//	}
//
//	return m_imageData;
//}