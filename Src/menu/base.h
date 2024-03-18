#pragma once
#include "../ImGui/imconfig.h"
#include "myCoroutine.h"
#include <iostream>



namespace Menu {
	bool Visible = true;
	CoroutineNodeList CoroutineHandle;
	using myCoroutinePtr = MyCoroutine(*)(LPVOID);

	class Parent;

	Parent* g_pRoot = nullptr;
	Parent* g_pRendering = nullptr;

	namespace Elems {
		int PositionX = 30;
		int PositionY = 30;
		int Width = 450;
		int HeaderHeight = 30;
		float HeaderFontScale = 24.0f;
		int HeaderTextOffsetX = 7;
		int HeaderTextOffsetY = 3;
		int HeaderBackgroundRed = 0xFF;
		int HeaderBackgroundGreen = 0x00;
		int HeaderBackgroundBlue = 0xFF;
		int HeaderBackgroundAlpha = 0xFF;
		int HeaderTextRed = 0xFF;
		int HeaderTextGreen = 0xFF;
		int HeaderTextBlue = 0xFF;
		int HeaderTextAlpha = 0xFF;
		int Gap = 1;

		DWORD ListedOptionCount = 15;

		int OptionHeight = 30;
		float OptionFontScale = 24.0f;
		int OptionTextOffsetX = 7;
		int OptionTextOffsetY = 3;
		int UnselectedOptionBackgroundRed = 0x10;
		int UnselectedOptionBackgroundGreen = 0x10;
		int UnselectedOptionBackgroundBlue = 0x10;
		int UnselectedOptionBackgroundAlpha = 0xAF;
		int UnselectedOptionTextRed = 0xFF;
		int UnselectedOptionTextGreen = 0x00;
		int UnselectedOptionTextBlue = 0xFF;
		int UnselectedOptionTextAlpha = 0xFF;
		int SelectedOptionBackgroundRed = 0xFF;
		int SelectedOptionBackgroundGreen = 0xFF;
		int SelectedOptionBackgroundBlue = 0xFF;
		int SelectedOptionBackgroundAlpha = 0xFF;
		int SelectedOptionTextRed = 0xFF;
		int SelectedOptionTextGreen = 0x00;
		int SelectedOptionTextBlue = 0xFF;
		int SelectedOptionTextAlpha = 0xFF;

		int CheckBoxScale = 10;

		int ParamsOffsetX = -7;
		int ParamsOffsetY = 2;

		int ParamsRed = 0xFF;
		int ParamsGreen = 0x00;
		int ParamsBlue = 0xFF;
		int ParamsAlpha = 0xFF;
	}
}