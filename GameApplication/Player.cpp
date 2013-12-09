#include "Player.h"
#include <windows.h>
#include "../Window/Win32Window.h"

void Player::SetMoveDirection(int newDir){
	currentDir = newDir;
}

void Player::update(){
	MSG msg;
	ZeroMemory( &msg, sizeof( msg ) );
	// Check the message queue
	if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE) )
	{
		TranslateMessage( &msg );
		DispatchMessage( &msg );
	}
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	// Check any available messages from the queue
	switch (msg)
	{
		
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}