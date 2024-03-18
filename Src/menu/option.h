#pragma once
#include "myCoroutine.h"
#include "base.h"
#include "../imgui/imgui.h"

#pragma warning(disable: 4244)



namespace Menu {
	class Option {
	protected:
		char8_t Name[128];
		Option* Next;
	public:
		Option(const char8_t* _Name) :Next(nullptr) {
			std::u8string u8str(_Name);
			strncpy_s(reinterpret_cast<char*>(Name), sizeof(Name) / sizeof(Name[0]), reinterpret_cast<const char*>(u8str.c_str()), _TRUNCATE);
		}
		Option* getNext() {
			return Next;
		}
		void setNext(Option* _Next) {
			Next = _Next;
		}
		const char8_t* getName() {
			return &Name[0];
		}
		virtual void call() {
			std::cerr << "bad invoke from base" << std::endl;
		}
		virtual void stepOn() {
			std::cerr << "bad invoke from non params option: base" << std::endl;
		}
		virtual void stepOff() {
			std::cerr << "bad invoke from non params option: base" << std::endl;
		}
		void _render(ImDrawList* dl, DWORD index, bool selected) {
			ImU32 background = NULL;
			ImU32 text = NULL;
			if (!selected) {
				background = IM_COL32(Menu::Elems::UnselectedOptionBackgroundRed, Menu::Elems::UnselectedOptionBackgroundGreen, Menu::Elems::UnselectedOptionBackgroundBlue, Menu::Elems::UnselectedOptionBackgroundAlpha);
				text = IM_COL32(Menu::Elems::UnselectedOptionTextRed, Menu::Elems::UnselectedOptionTextGreen, Menu::Elems::UnselectedOptionTextBlue, Menu::Elems::UnselectedOptionTextAlpha);
			}
			else {
				background = IM_COL32(Menu::Elems::SelectedOptionBackgroundRed, Menu::Elems::SelectedOptionBackgroundGreen, Menu::Elems::SelectedOptionBackgroundBlue, Menu::Elems::SelectedOptionBackgroundAlpha);
				text = IM_COL32(Menu::Elems::SelectedOptionTextRed, Menu::Elems::SelectedOptionTextGreen, Menu::Elems::SelectedOptionTextBlue, Menu::Elems::SelectedOptionTextAlpha);
			}
			dl->AddRectFilled(ImVec2(Menu::Elems::PositionX, Menu::Elems::PositionY + Menu::Elems::HeaderHeight + Menu::Elems::Gap + index * Menu::Elems::OptionHeight), ImVec2(Menu::Elems::PositionX + Menu::Elems::Width, Menu::Elems::PositionY + Menu::Elems::HeaderHeight + Menu::Elems::Gap + index * Menu::Elems::OptionHeight + Menu::Elems::OptionHeight), background);
			dl->AddText(ImGui::GetFont(), Menu::Elems::OptionFontScale, ImVec2(Menu::Elems::PositionX + Menu::Elems::OptionTextOffsetX, Menu::Elems::PositionY + Menu::Elems::HeaderHeight + Menu::Elems::Gap + index * Menu::Elems::OptionHeight + Menu::Elems::OptionTextOffsetY), text, (const char*)this->getName());
		}
		virtual void render(ImDrawList* dl, DWORD index, bool selected) {
			_render(dl, index, selected);
		}
	};
	
}