#pragma once
#include <Windows.h>
#include <coroutine>

class MyCoroutine {
public:
	struct promise_type {
		ULONGLONG ResumeTick = 0;
		std::suspend_always initial_suspend() noexcept { return {}; }
		std::suspend_always final_suspend() noexcept { return {}; }
		void unhandled_exception() noexcept {}
		MyCoroutine get_return_object() {
			return MyCoroutine{ std::coroutine_handle<promise_type>::from_promise(*this) };
		}
		std::suspend_always yield_value(ULONGLONG value) noexcept {
			if (ResumeTick == 0) {
				ResumeTick = GetTickCount64();
			}
			ResumeTick = ResumeTick + value;
			return {};
		}
		void return_void() noexcept {}
	};
	bool resume() {
		if (!coroHandle) {
			return false;
		}
		if (coroHandle.promise().ResumeTick > GetTickCount64()) {
			return false;
		}
		if (coroHandle.done()) {
			return false; // if its done, resume = crash
		}
		coroHandle.resume();
		return true;
	}
	bool isDone() const {
		return !coroHandle || coroHandle.done();
	}
	void Destroy() {
		if (coroHandle) {
			coroHandle.destroy();
			coroHandle = nullptr; // Reset handle after destruction
		}
	}
	explicit MyCoroutine(std::coroutine_handle<promise_type> handle) : coroHandle(handle) {}
private:
	std::coroutine_handle<promise_type> coroHandle;
};
class CoroutineNodeList {
private:
	struct CoroNode {
		MyCoroutine Coro;
		CoroNode* next;
		CoroNode(const MyCoroutine& Coro) :Coro(Coro), next(nullptr) {}
	};
	CoroNode* Head;
public:
	CoroutineNodeList() :Head(nullptr) {}

	void CreateCoroutine(const MyCoroutine& Coro) {
		CoroNode* newNode = new CoroNode(Coro);
		if (!Head) {
			Head = newNode;
		}
		else {
			CoroNode* temp = Head;
			while (temp->next) {
				temp = temp->next;
			}
			temp->next = newNode;
		}
		newNode->Coro.resume();
	}


	DWORD CoroutineManager() {
		DWORD coroCount = 0;
		CoroNode* curr = Head;
		CoroNode* prev = nullptr;
		while (curr) {
			if (curr->Coro.isDone()) {
				CoroNode* Delete = curr;
				curr = curr->next;
				if (prev) {
					prev->next = curr;
				}
				else {
					Head = curr;
				}
				Delete->Coro.Destroy();
				delete Delete;
			}
			else {
				curr->Coro.resume();
				prev = curr;
				curr = curr->next;
			}
			coroCount++;
		}
		return coroCount;
	}
};

/*
	必须先有一个协程函数,这是一个例子/need a Coroutine function first, and here is a example
	MyCoroutine coroutineExample(LPVOID lpParams){
		while(true){
			std::cout << GetTickCount64() << std::endl;
			co_yield 1;
		}
	}

	这个协程通过链表的方式进行控制，所以说你得初始化链表头/due to this coroutine manager controled by linked list, which means you have to create a pointer to its first node:
	coroutineHandle = CoroutineNodeList();

	如何在协程中加入新的任务/how to add functions into this manager:
	coroutineHandle.CreateCoroutine(coroutineExample(nullptr));

	恢复所有可恢复的协程/this will resume all resume-able coroutine:
	coroutineHandle.CoroutineManager();
*/