#pragma once
#include "action.h"

namespace Menu {
	class Toggle :public Action {
	protected:
		bool toggled;
		bool callwhendisable;
	public:
		Toggle(const char8_t* _Name, myCoroutinePtr mcp, bool _callwhendisable) :Action(_Name, mcp), callwhendisable(_callwhendisable), toggled(false) {}

		void call() override {
			toggled = !toggled;
			if (this->getCoroutine() != nullptr && (toggled || callwhendisable)) {
				CoroutineHandle.CreateCoroutine(this->getCoroutine()(&toggled));
			}
		}

		void stepOn() override {
			std::cerr << "bad invoke from non params option: toggle" << std::endl;
		}

		void stepOff() override {
			std::cerr << "bad invoke from non params option: toggle" << std::endl;
		}

		void render(ImDrawList* dl, DWORD index, bool selected) override {
			_render(dl, index, selected);
			float centerX = Menu::Elems::PositionX + Menu::Elems::Width - ((float)Menu::Elems::OptionHeight / 2) + Elems::ParamsOffsetX;
			float centerY = Menu::Elems::PositionY + Menu::Elems::HeaderHeight + Menu::Elems::Gap + index * Menu::Elems::OptionHeight + Menu::Elems::OptionHeight - ((float)Menu::Elems::OptionHeight / 2);

			ImU32 Colour = NULL;
			if (!selected) {
				Colour = IM_COL32(Menu::Elems::UnselectedOptionTextRed, Menu::Elems::UnselectedOptionTextGreen, Menu::Elems::UnselectedOptionTextBlue, Menu::Elems::UnselectedOptionTextAlpha);
			}
			else {
				Colour = IM_COL32(Menu::Elems::SelectedOptionTextRed, Menu::Elems::SelectedOptionTextGreen, Menu::Elems::SelectedOptionTextBlue, Menu::Elems::SelectedOptionTextAlpha);
			}
			if (toggled) {
				dl->AddRectFilled(ImVec2(centerX - Elems::CheckBoxScale, centerY - Elems::CheckBoxScale), ImVec2(centerX + Elems::CheckBoxScale, centerY + Elems::CheckBoxScale), Colour);
			}
			else {
				dl->AddRect(ImVec2(centerX - Elems::CheckBoxScale, centerY - Elems::CheckBoxScale), ImVec2(centerX + Elems::CheckBoxScale, centerY + Elems::CheckBoxScale), Colour);
			}
		}
	};
}