#pragma once
#include "action.h"

namespace Menu {
	class numberAction :public Action {
		template<typename T>
		struct Params {
			T Current;
			T Max;
			T Min;
			T Step;
			T* oData;
			Params(T _Current, T _Min, T _Max, T _Step, T* _oData = nullptr) :Current(_Current), Max(_Max), Min(_Min), Step(_Step) {
				if (_oData == nullptr) {
					oData = &Current;
				}
				else {
					oData = _oData;
				}
			}
			void stepOn() {
				Current += Step;
				if (Current > Max) {
					Current = Max;
				}
				else if (Current < Min) {
					Current = Min;
				}
				if (oData) {
					*oData = Current;
				}
			}
			void stepOff() {
				Current -= Step;
				if (Current > Max) {
					Current = Max;
				}
				else if (Current < Min) {
					Current = Min;
				}
				if (oData) {
					*oData = Current;
				}
			}
			LPVOID lpParams() {
				return oData;
			}
		};
	protected:
		Params<int>* intInfo;
		Params<float>* floatInfo;
	public:
		numberAction(const char8_t* _Name, myCoroutinePtr mcp, int _Current, int _Max, int _Min, int _Step, int* _oData) :Action(_Name, mcp) {
			floatInfo = nullptr;
			do {
				intInfo = new Params<int>(_Current, _Max, _Min, _Step, _oData);
			} while (intInfo == nullptr);
		}
		numberAction(const char8_t* _Name, myCoroutinePtr mcp, float _Current, float _Max, float _Min, float _Step, float* _oData) :Action(_Name, mcp) {
			intInfo = nullptr;
			do {
				floatInfo = new Params<float>(_Current, _Max, _Min, _Step, _oData);
			} while (floatInfo == nullptr);
		}
		void call() override {
			if (this->getCoroutine()) {
				if (intInfo) {
					CoroutineHandle.CreateCoroutine(this->getCoroutine()(intInfo->oData));
				}
				else if (floatInfo) {
					CoroutineHandle.CreateCoroutine(this->getCoroutine()(floatInfo->oData));
				}
			}
		}
		void stepOn() override {
			if (intInfo) {
				intInfo->stepOn();
			}
			else if (floatInfo) {
				floatInfo->stepOn();
			}
		}
		void stepOff() override {
			if (intInfo) {
				intInfo->stepOff();
			}
			else if (floatInfo) {
				floatInfo->stepOff();
			}
		}

		void render(ImDrawList* dl, DWORD index, bool selected) override {
			_render(dl, index, selected);
			//now draw params
			char8_t* buffer[32];
			if (intInfo) {
				sprintf_s(reinterpret_cast<char*>(buffer), 32, "%d", intInfo->Current);
			}
			else if (floatInfo) {
				sprintf_s(reinterpret_cast<char*>(buffer), 32, "%.2f", floatInfo->Current);
			}
			ImVec2 TextSize = ImGui::GetFont()->CalcTextSizeA(Elems::OptionFontScale, FLT_MAX, 0, (const char*)buffer);
			dl->AddText(ImGui::GetFont(), Menu::Elems::OptionFontScale, ImVec2(Menu::Elems::PositionX + Menu::Elems::ParamsOffsetX + Menu::Elems::Width - TextSize.x, Menu::Elems::PositionY + Menu::Elems::HeaderHeight + Menu::Elems::Gap + index * Menu::Elems::OptionHeight + Menu::Elems::ParamsOffsetY), IM_COL32(Elems::ParamsRed, Elems::ParamsGreen, Elems::ParamsBlue, Elems::ParamsAlpha), (const char*)buffer);

		}
	};
}