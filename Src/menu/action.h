#pragma once
#include "option.h"
namespace Menu {
	class Action :public Option {
	protected:
		myCoroutinePtr myCoroutine;
	public:
		Action(const char8_t* _Name, myCoroutinePtr _myCoroutine) :Option(_Name), myCoroutine(_myCoroutine) {}

		myCoroutinePtr getCoroutine() const {
			return myCoroutine;
		}

		void call() override {
			if (myCoroutine) {
				CoroutineHandle.CreateCoroutine(myCoroutine(nullptr));
			}
		}
		void stepOn() override {
			std::cerr << "bad invoke from non params option: action" << std::endl;
		}
		void stepOff() override {
			std::cerr << "bad invoke from non params option: action" << std::endl;
		}
		void render(ImDrawList* dl, DWORD index, bool selected) override {
			_render(dl, index, selected);
			//no params to draw
		}
	};
}