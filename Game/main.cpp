// main.cpp
#include "pch.h"
#include "Game.h"

int main() {

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// (선택) 특정 할당 번호에서 중단점 걸기
	//_CrtSetBreakAlloc(5504);



	Game game;

	if (!game.Initialize()) {
		std::cout << "게임 초기화 실패" << std::endl;
		return false;	
	}

	game.Run();

	game.Release();



	return 0;
}