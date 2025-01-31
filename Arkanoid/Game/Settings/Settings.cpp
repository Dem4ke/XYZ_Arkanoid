#include <cassert>
#include "Settings.h"
#include "../FileSystem/FileSystem.h"

namespace Arkanoid
{
	UGameSettings* UGameSettings::GetGameSettings()
	{
		if (!GameSettings)
		{
			GameSettings = new UGameSettings();
		}

		return GameSettings;
	}
	
	void UGameSettings::SaveSettings()
	{
		UFileSystem FileSystem;
		std::vector<std::string> Info;

		std::string ScreenWidthText = std::to_string(ScreenWidth) + "\n";
		std::string ScreenHeightText = std::to_string(ScreenHeight) + "\n";
		std::string TimePerFrameText = std::to_string(TimePerFrame) + "\n";
		std::string SoundPowerText = std::to_string(SoundPower) + "\n";

		Info.push_back(ScreenWidthText);
		Info.push_back(ScreenHeightText);
		Info.push_back(TimePerFrameText);
		Info.push_back(SoundPowerText);

		// Get info from config file and set game properties
		bool bIsSerialized = FileSystem.Serialize(PathToConfig, Info);
		assert(bIsSerialized);
	}

	void UGameSettings::SetScreenWidth(int Value)
	{
		ScreenWidth = Value;
	}

	void UGameSettings::SetScreenHeight(int Value)
	{
		ScreenHeight = Value;
	}

	void UGameSettings::SetTimePerFrame(float Value)
	{
		TimePerFrame = Value;
	}

	void UGameSettings::SetSoundPower(float Value)
	{
		SoundPower = Value;
	}

	int UGameSettings::GetScreenWidth() const
	{
		return ScreenWidth;
	}

	int UGameSettings::GetScreenHeight() const
	{
		return ScreenHeight;
	}

	float UGameSettings::GetTimePerFrame() const
	{
		return TimePerFrame;
	}

	float UGameSettings::GetSoundPower() const
	{
		return SoundPower;
	}

	const CScaleFactor& UGameSettings::GetScaleFactor()
	{
		return ScaleFactor;
	}

	/*//////////////////////////////////*/
	/*                                  */
	/*	      PRIVATE WORKTOOLS         */
	/*                                  */
	/*//////////////////////////////////*/

	UGameSettings::UGameSettings()
	{
		UFileSystem FileSystem;
		std::vector<std::string> Info;

		// Get info from config file and set game properties
		bool bIsDeserialized = FileSystem.Deserialize(PathToConfig, Info);
		assert(bIsDeserialized);
		
		ScreenWidth = std::stoi(Info[0]);
		ScreenHeight = std::stoi(Info[1]);
		TimePerFrame = std::stof(Info[2]);
		SoundPower = std::stof(Info[3]);

		// For 800 pixels in width and 600 in height ScaleFactor equals 1
		ScaleFactor.X = static_cast<float>(ScreenWidth) / 800.f;
		ScaleFactor.Y = static_cast<float>(ScreenHeight) / 600.f;
	}
}