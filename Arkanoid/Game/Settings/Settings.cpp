#include <cassert>
#include "Settings.h"
#include "../FileSystem/FileSystem.h"

namespace Arkanoid
{
	/*//////////////////////////////////*/
	/*                                  */
	/*	          CResources            */
	/*                                  */
	/*//////////////////////////////////*/

	CResources::CResources()
	{
		// Load font from file
		bool bIsLoaded = Font.loadFromFile("Resources/Fonts/Roboto-Regular.ttf");
		assert(bIsLoaded);

		// Long sounds or background music (not loads file but opens it for a whole session)
		bIsLoaded = BackgroundMusic.openFromFile("Resources/Sounds/Clinthammer__Background_Music.wav");
		assert(bIsLoaded);
	}

	void CResources::SetSoundsVolume(float Value)
	{
		Sound.setVolume(Value);
	}

	void CResources::SetBackgroundMusicVolume(float Value)
	{
		BackgroundMusic.setVolume(Value);
	}

	void CResources::PlaySound(sf::SoundBuffer& SoundAsset)
	{
		Sound.setBuffer(SoundAsset);
		Sound.play();
	}

	void CResources::PlayBackgroundMusic()
	{
		BackgroundMusic.play();
		BackgroundMusic.setLoop(true);
	}

	void CResources::StopBackgroundMusic()
	{
		BackgroundMusic.pause();
	}

	const sf::Font& CResources::GetFont()
	{
		return Font;
	}

	/*//////////////////////////////////*/
	/*                                  */
	/*	         UGameSettings          */
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
		MusicPower = std::stof(Info[4]);

		bIsFullscreen = std::stoi(Info[5]);
		bIsSoundsOn = std::stoi(Info[6]);
		bIsMusicOn = std::stoi(Info[7]);

		// For 1280 pixels in width and 720 in height ScaleFactor equals 1
		ScaleFactor.X = static_cast<float>(ScreenWidth) / 1280.f;
		ScaleFactor.Y = static_cast<float>(ScreenHeight) / 720.f;

		Resources.SetSoundsVolume(SoundPower);
		Resources.SetBackgroundMusicVolume(MusicPower);

		if (!bIsSoundsOn)
		{
			Resources.SetSoundsVolume(0.f);
		}

		if (bIsMusicOn) 
		{
			Resources.PlayBackgroundMusic();
		} 
	}

	UGameSettings& UGameSettings::Instance()
	{
		static UGameSettings GameSettings;
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
		std::string MusicPowerText = std::to_string(MusicPower) + "\n";

		std::string IsFullscreenText = std::to_string(bIsFullscreen) + "\n";
		std::string SoundsOnText = std::to_string(bIsSoundsOn) + "\n";
		std::string MusicOnText = std::to_string(bIsMusicOn) + "\n";

		Info.push_back(ScreenWidthText);
		Info.push_back(ScreenHeightText);
		Info.push_back(TimePerFrameText);
		Info.push_back(SoundPowerText);
		Info.push_back(MusicPowerText);

		Info.push_back(IsFullscreenText);
		Info.push_back(SoundsOnText);
		Info.push_back(MusicOnText);

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

	void UGameSettings::SetFullscreenMode(bool bIsOn)
	{
		bIsFullscreen = bIsOn;
	}

	void UGameSettings::SetSoundsOn(bool bIsOn)
	{
		bIsSoundsOn = bIsOn;
	}

	void UGameSettings::SetMusicOn(bool bIsOn)
	{
		bIsMusicOn = bIsOn;
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

	bool UGameSettings::IsFullscreenMode() const
	{
		return bIsFullscreen;
	}

	bool UGameSettings::IsSoundsOn() const
	{
		return bIsSoundsOn;
	}

	bool UGameSettings::IsMusicOn() const
	{
		return bIsMusicOn;
	}

	const CScaleFactor& UGameSettings::GetScaleFactor()
	{
		return ScaleFactor;
	}

	CResources* UGameSettings::GetResources()
	{
		return &Resources;
	}
}