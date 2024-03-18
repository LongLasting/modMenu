#include "myCoroutine.h"
#include "../ImGui/imgui.h"

namespace Function {
	static int g_CrossHairX = 960;
	static int g_CrossHairY = 540;
	static int g_CrossHairLength = 5;
	static int g_CrossHairGap = 2;
	static int g_CrossHairRedRed = 0xFF;
	static int g_CrossHairRedGreen = 0x00;
	static int g_CrossHairRedBlue = 0xFF;
	static int g_CrossHairRedAlpha = 0xFF;

	static MyCoroutine DrawCrossHair(LPVOID lpParams) {
		while (*(bool*)lpParams) {
			ImGui::GetForegroundDrawList()->AddLine(ImVec2(g_CrossHairX - g_CrossHairGap - g_CrossHairLength, g_CrossHairY), ImVec2(g_CrossHairX - g_CrossHairGap, g_CrossHairY), IM_COL32(g_CrossHairRedRed, g_CrossHairRedGreen, g_CrossHairRedBlue, g_CrossHairRedAlpha));
			ImGui::GetForegroundDrawList()->AddLine(ImVec2(g_CrossHairX + g_CrossHairGap + g_CrossHairLength + 1, g_CrossHairY), ImVec2(g_CrossHairX + g_CrossHairGap + 1, g_CrossHairY), IM_COL32(g_CrossHairRedRed, g_CrossHairRedGreen, g_CrossHairRedBlue, g_CrossHairRedAlpha));

			ImGui::GetForegroundDrawList()->AddLine(ImVec2(g_CrossHairX, g_CrossHairY - g_CrossHairGap - g_CrossHairLength), ImVec2(g_CrossHairX, g_CrossHairY - g_CrossHairGap), IM_COL32(g_CrossHairRedRed, g_CrossHairRedGreen, g_CrossHairRedBlue, g_CrossHairRedAlpha));
			ImGui::GetForegroundDrawList()->AddLine(ImVec2(g_CrossHairX, g_CrossHairY + g_CrossHairGap + g_CrossHairLength + 1), ImVec2(g_CrossHairX, g_CrossHairY + g_CrossHairGap + 1), IM_COL32(g_CrossHairRedRed, g_CrossHairRedGreen, g_CrossHairRedBlue, g_CrossHairRedAlpha));
			co_yield 1;
		}
	}
}