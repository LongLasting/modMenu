#pragma once
#include "action.h"
#include "actionValue.h"
#include "toggle.h"
namespace Menu {
	class Parent : public Action {
	protected:
		Option* FirstOption;
		DWORD Current;
		DWORD Top;
		DWORD Count;
		Option* CurrentOption;
		Parent* _Parent;
	public:
		Parent(const char8_t* _Name, myCoroutinePtr mcp, Parent* __parent) :Action(_Name, mcp), FirstOption(nullptr), Current(0), Top(0), Count(0), CurrentOption(nullptr), _Parent(__parent) {}
		void addAction(const char8_t* _Name, myCoroutinePtr mcp) {
			if (FirstOption == nullptr) {
				do {
					FirstOption = new Action(_Name, mcp);
				} while (FirstOption == nullptr);
			}
			else {
				Option* asdf = FirstOption;
				while (asdf->getNext() != nullptr) {
					asdf = asdf->getNext();
				}
				do {
					asdf->setNext(new Action(_Name, mcp));
				} while (asdf->getNext() == nullptr);
			}
			Top = 1;
			Current = 1;
			Count++;
		}
		void addActionValue(const char8_t* _Name, myCoroutinePtr mcp, float _Current, float _Min, float _Max, float _Step, float* _oData) {
			if (FirstOption == nullptr) {
				do {
					FirstOption = new numberAction(_Name, mcp, _Current, _Min, _Max, _Step, _oData);
				} while (FirstOption == nullptr);
			}
			else {
				Option* asdf = FirstOption;
				while (asdf->getNext() != nullptr) {
					asdf = asdf->getNext();
				}
				do {
					asdf->setNext(new numberAction(_Name, mcp, _Current, _Min, _Max, _Step, _oData));
				} while (asdf->getNext() == nullptr);
			}
			Top = 1;
			Current = 1;
			Count++;
		}
		void addActionValue(const char8_t* _Name, myCoroutinePtr mcp, int _Current, int _Min, int _Max, int _Step, int* _oData) {
			if (FirstOption == nullptr) {
				do {
					FirstOption = new numberAction(_Name, mcp, _Current, _Min, _Max, _Step, _oData);
				} while (FirstOption == nullptr);
			}
			else {
				Option* asdf = FirstOption;
				while (asdf->getNext() != nullptr) {
					asdf = asdf->getNext();
				}
				do {
					asdf->setNext(new numberAction(_Name, mcp, _Current, _Min, _Max, _Step, _oData));
				} while (asdf->getNext() == nullptr);
			}
			Top = 1;
			Current = 1;
			Count++;
		}
		void addToggle(const char8_t* _Name, myCoroutinePtr mcp, bool _callwhendisable) {
			if (FirstOption == nullptr) {
				do {
					FirstOption = new Toggle(_Name, mcp, _callwhendisable);
				} while (FirstOption == nullptr);
			}
			else {
				Option* asdf = FirstOption;
				while (asdf->getNext() != nullptr) {
					asdf = asdf->getNext();
				}
				do {
					asdf->setNext(new Toggle(_Name, mcp, _callwhendisable));
				} while (asdf->getNext() == nullptr);
			}
			Top = 1;
			Current = 1;
			Count++;
		}
		Parent* addParent(const char8_t* _Name, myCoroutinePtr mcp) {
			Parent* ret = nullptr;
			do {
				ret = new Parent(_Name, mcp, this);
			} while (ret == nullptr);
			if (FirstOption == nullptr) {
				FirstOption = ret;
			}
			else {
				Option* asdf = FirstOption;
				while (asdf->getNext() != nullptr) {
					asdf = asdf->getNext();
				}
				asdf->setNext(ret);
			}
			Top = 1;
			Current = 1;
			Count++;
			return ret;
		}
		void validate() {
			if (Count == 0) {
				CurrentOption = nullptr;
			}
			else {
				Option* asdf = FirstOption;
				for (DWORD ind = 1; ind <= Count || asdf != nullptr; ind++) {
					if (ind == Current) {
						CurrentOption = asdf;
						return;
					}
					asdf = asdf->getNext();
				}
			}
		}
		void keyeventCall() {
			validate();
			CurrentOption->call();
		}
		void stepOn() override {
			validate();
			CurrentOption->stepOn();
		}
		void stepOff() override {
			validate();
			CurrentOption->stepOff();
		}
		void moveDown() {
			Current++;
			if (Current > Count) {
				Current = 1;
				Top = 1;
			}
			else if (Current + 2 >= Top + Elems::ListedOptionCount && Top + Elems::ListedOptionCount < Count + 1) {
				Top++;
			}
			validate();

		}
		void moveUp() {
			Current--;
			if (Current <= Top + 1) {
				if (Top > 1) {
					Top--;
				}
				else if (Current < 1) {
					Current = Count;
					if (Count > Elems::ListedOptionCount) {
						Top = Count - Elems::ListedOptionCount + 1;
					}
				}
			}
		}

		Option* getFirstOption() {
			return FirstOption;
		}
		DWORD getTop() {
			return Top;
		}
		DWORD getCurrent() {
			return Current;
		}
		Parent* getParent() {
			return _Parent;
		}

		void render(ImDrawList* dl, DWORD index, bool Selected) override {
			_render(dl, index, Selected);
			std::u8string str(u8">>");
			ImVec2 TextSize = ImGui::GetFont()->CalcTextSizeA(Elems::OptionFontScale, FLT_MAX, 0, (const char*)str.c_str());
			dl->AddText(ImGui::GetFont(), Menu::Elems::OptionFontScale, ImVec2(Menu::Elems::PositionX + Menu::Elems::ParamsOffsetX + Menu::Elems::Width - TextSize.x, Menu::Elems::PositionY + Menu::Elems::HeaderHeight + Menu::Elems::Gap + index * Menu::Elems::OptionHeight + Menu::Elems::ParamsOffsetY), IM_COL32(Elems::ParamsRed, Elems::ParamsGreen, Elems::ParamsBlue, Elems::ParamsAlpha), (const char*)str.c_str());
		}
		Option* getCurrentOption() {
			return CurrentOption;
		}
		void call() override {
			if (this->getCoroutine()) {
				CoroutineHandle.CreateCoroutine(this->getCoroutine()(nullptr));
			}
			if (this->getCurrent() > 0) {
				g_pRendering = (Parent*)this;
			}
		}
	};
}