// main.cpp
#include "pch.h"
#include "Game.h"

int main() {

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// (����) Ư�� �Ҵ� ��ȣ���� �ߴ��� �ɱ�
	//_CrtSetBreakAlloc(5504);



	Game game;

	if (!game.Initialize()) {
		std::cout << "���� �ʱ�ȭ ����" << std::endl;
		return false;	
	}

	game.Run();

	game.Release();



	return 0;
}