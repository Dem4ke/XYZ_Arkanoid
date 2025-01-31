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
	
	/*//////////////////////////////////*/
	/*                                  */
	/*	      PRIVATE WORKTOOLS         */
	/*                                  */
	/*//////////////////////////////////*/

	UGameSettings::UGameSettings()
	{
		// Получение информации из конфига о разрешении экрана, расчет фактора масшабирования для всех элементов
		UFileSystem FileSystem;
		std::vector<std::string> Info;
		PathToConfig = "Config/GameSettings.conf";

		// Get info from config file and set game properties
		bool bIsDeserialized = FileSystem.Deserialize(PathToConfig, Info);
		assert(bIsDeserialized);
		
		ScreenWidth = std::stoi(Info[0]);
		ScreenHeight = std::stoi(Info[1]);
		TimePerFrame = std::stof(Info[2]);
		SoundPower = std::stof(Info[3]);
	}
}