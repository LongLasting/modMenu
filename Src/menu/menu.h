#pragma once
#include "parent.h"
#include "Functions.h"
namespace Menu {
	void init() {
		do {
			g_pRoot = new Parent(u8"Ö÷²Ëµ¥", nullptr, nullptr);
		} while (g_pRoot == nullptr);
		g_pRendering = g_pRoot;

		g_pRoot->addToggle(u8"Draw CrossHair", Function::DrawCrossHair, false);

		Parent* Settings = g_pRoot->addParent(u8"Settings", nullptr);
		Settings->addActionValue(u8"Menu Position X", nullptr, Elems::PositionX, 0, 1000, 1, &Elems::PositionX);
		Settings->addActionValue(u8"Menu Position Y", nullptr, Elems::PositionY, 0, 1000, 1, &Elems::PositionY);
		Settings->addActionValue(u8"Menu Width", nullptr, Elems::Width, 0, 1000, 1, &Elems::Width);
		Settings->addActionValue(u8"Header Height", nullptr, Elems::HeaderHeight, 0, 1000, 1, &Elems::HeaderHeight);
		Settings->addActionValue(u8"Header Text Scale", nullptr, Elems::HeaderFontScale, 0.0f, 1000.0f, 1.0f, &Elems::HeaderFontScale);
		Settings->addActionValue(u8"Header Text Offset X", nullptr, Elems::HeaderTextOffsetX, -50, 50, 1, &Elems::HeaderTextOffsetX);
		Settings->addActionValue(u8"Header Text Offset Y", nullptr, Elems::HeaderTextOffsetY, -50, 50, 1, &Elems::HeaderTextOffsetY);
		Settings->addActionValue(u8"Header Background Red", nullptr, Elems::HeaderBackgroundRed, 0, 255, 1, &Elems::HeaderBackgroundRed);
		Settings->addActionValue(u8"Header Background Green", nullptr, Elems::HeaderBackgroundGreen, 0, 255, 1, &Elems::HeaderBackgroundGreen);
		Settings->addActionValue(u8"Header Background Blue", nullptr, Elems::HeaderBackgroundBlue, 0, 255, 1, &Elems::HeaderBackgroundBlue);
		Settings->addActionValue(u8"Header Background Alpha", nullptr, Elems::HeaderBackgroundAlpha, 0, 255, 1, &Elems::HeaderBackgroundAlpha);
		Settings->addActionValue(u8"Header Text Red", nullptr, Elems::HeaderTextRed, 0, 255, 1, &Elems::HeaderTextRed);
		Settings->addActionValue(u8"Header Text Green", nullptr, Elems::HeaderTextGreen, 0, 255, 1, &Elems::HeaderTextGreen);
		Settings->addActionValue(u8"Header Text Blue", nullptr, Elems::HeaderTextBlue, 0, 255, 1, &Elems::HeaderTextBlue);
		Settings->addActionValue(u8"Header Text Alpha", nullptr, Elems::HeaderTextAlpha, 0, 255, 1, &Elems::HeaderTextAlpha);
		Settings->addActionValue(u8"Gap", nullptr, Elems::Gap, 0, 1000, 1, &Elems::Gap);
		Settings->addActionValue(u8"Listed Option Count", nullptr, (int)Elems::ListedOptionCount, 0, 25, 1, (int*)&Elems::ListedOptionCount);
		Settings->addActionValue(u8"Option Height", nullptr, Elems::OptionHeight, 0, 1000, 1, &Elems::OptionHeight);
		Settings->addActionValue(u8"Option Font Scale", nullptr, Elems::OptionFontScale, 0, 1000, 1, &Elems::OptionFontScale);
		Settings->addActionValue(u8"Option Text Offset X", nullptr, Elems::OptionTextOffsetX, 0, 1000, 1, &Elems::OptionTextOffsetX);
		Settings->addActionValue(u8"Option Text Offset Y", nullptr, Elems::OptionTextOffsetY, 0, 1000, 1, &Elems::OptionTextOffsetY);
		Settings->addActionValue(u8"Unselected Option Background Red", nullptr, Elems::UnselectedOptionBackgroundRed, 0, 1000, 1, &Elems::UnselectedOptionBackgroundRed);
		Settings->addActionValue(u8"Unselected Option Background Green", nullptr, Elems::UnselectedOptionBackgroundGreen, 0, 1000, 1, &Elems::UnselectedOptionBackgroundGreen);
		Settings->addActionValue(u8"Unselected Option Background Blue", nullptr, Elems::UnselectedOptionBackgroundBlue, 0, 1000, 1, &Elems::UnselectedOptionBackgroundBlue);
		Settings->addActionValue(u8"Unselected Option Background Alpha", nullptr, Elems::UnselectedOptionBackgroundAlpha, 0, 1000, 1, &Elems::UnselectedOptionBackgroundAlpha);
		Settings->addActionValue(u8"Unselected Option Text Red", nullptr, Elems::UnselectedOptionTextRed, 0, 1000, 1, &Elems::UnselectedOptionTextRed);
		Settings->addActionValue(u8"Unselected Option Text Green", nullptr, Elems::UnselectedOptionTextGreen, 0, 1000, 1, &Elems::UnselectedOptionTextGreen);
		Settings->addActionValue(u8"Unselected Option Text Blue", nullptr, Elems::UnselectedOptionTextBlue, 0, 1000, 1, &Elems::UnselectedOptionTextBlue);
		Settings->addActionValue(u8"Unselected Option Text Alpha", nullptr, Elems::UnselectedOptionTextAlpha, 0, 1000, 1, &Elems::UnselectedOptionTextAlpha);
		Settings->addActionValue(u8"Selected Option Background Red", nullptr, Elems::SelectedOptionBackgroundRed, 0, 1000, 1, &Elems::SelectedOptionBackgroundRed);
		Settings->addActionValue(u8"Selected Option Background Green", nullptr, Elems::SelectedOptionBackgroundGreen, 0, 1000, 1, &Elems::SelectedOptionBackgroundGreen);
		Settings->addActionValue(u8"Selected Option Background Blue", nullptr, Elems::SelectedOptionBackgroundBlue, 0, 1000, 1, &Elems::SelectedOptionBackgroundBlue);
		Settings->addActionValue(u8"Selected Option Background Alpha", nullptr, Elems::SelectedOptionBackgroundAlpha, 0, 1000, 1, &Elems::SelectedOptionBackgroundAlpha);
		Settings->addActionValue(u8"Selected Option Text Red", nullptr, Elems::SelectedOptionTextRed, 0, 1000, 1, &Elems::SelectedOptionTextRed);
		Settings->addActionValue(u8"Selected Option Text Green", nullptr, Elems::SelectedOptionTextGreen, 0, 1000, 1, &Elems::SelectedOptionTextGreen);
		Settings->addActionValue(u8"Selected Option Text Blue", nullptr, Elems::SelectedOptionTextBlue, 0, 1000, 1, &Elems::SelectedOptionTextBlue);
		Settings->addActionValue(u8"Selected Option Text Alpha", nullptr, Elems::SelectedOptionTextAlpha, 0, 1000, 1, &Elems::SelectedOptionTextAlpha);
		Settings->addActionValue(u8"Check Box Scale", nullptr, Elems::CheckBoxScale, 0, 30, 1, &Elems::CheckBoxScale);
		Settings->addActionValue(u8"Params Offset X", nullptr, Elems::ParamsOffsetX, -50, 50, 1, &Elems::ParamsOffsetX);
		Settings->addActionValue(u8"Params Offset Y", nullptr, Elems::ParamsOffsetY, -50, 50, 1, &Elems::ParamsOffsetY);
		Settings->addActionValue(u8"Params Red", nullptr, Elems::ParamsRed, 0, 255, 1, &Elems::ParamsRed);
		Settings->addActionValue(u8"Params Green", nullptr, Elems::ParamsGreen, 0, 255, 1, &Elems::ParamsGreen);
		Settings->addActionValue(u8"Params Blue", nullptr, Elems::ParamsBlue, 0, 255, 1, &Elems::ParamsBlue);
		Settings->addActionValue(u8"Params Alpha", nullptr, Elems::ParamsAlpha, 0, 255, 1, &Elems::ParamsAlpha);
	}

	void Render() {
		CoroutineHandle.CoroutineManager();
		if (Visible) {
			ImDrawList* DrawList = ImGui::GetForegroundDrawList();
			DrawList->AddRectFilled(ImVec2(Menu::Elems::PositionX, Menu::Elems::PositionY), ImVec2(Menu::Elems::PositionX + Menu::Elems::Width, Menu::Elems::PositionY + Menu::Elems::HeaderHeight), IM_COL32(Menu::Elems::HeaderBackgroundRed, Menu::Elems::HeaderBackgroundGreen, Menu::Elems::HeaderBackgroundBlue, Menu::Elems::HeaderBackgroundAlpha));
			DrawList->AddText(ImGui::GetFont(), Menu::Elems::HeaderFontScale, ImVec2(Menu::Elems::PositionX + Menu::Elems::HeaderTextOffsetX, Menu::Elems::PositionY + Menu::Elems::HeaderTextOffsetY), IM_COL32(Menu::Elems::HeaderTextRed, Menu::Elems::HeaderTextGreen, Menu::Elems::HeaderTextBlue, Menu::Elems::HeaderTextAlpha), (const char*)g_pRendering->getName());
			Option* renderingnow = g_pRendering->getFirstOption();
			DWORD alreadyRendered = 0;
			for (DWORD indexhere = 1; alreadyRendered < Elems::ListedOptionCount && renderingnow != nullptr; indexhere++) {
				if (indexhere >= g_pRendering->getTop()) {
					renderingnow->render(DrawList, alreadyRendered, indexhere == g_pRendering->getCurrent());
					alreadyRendered++;
				}
				renderingnow = renderingnow->getNext();
			}
		}
	}
}