#include "raylib.h"
#include "Ball.h"
#include "Paddle.h"


//----------------------------------------------------------------------------------
// Main entry point
//----------------------------------------------------------------------------------
int main(void) {
	// Inizializzazione
	//---------------------------------------------------------
	InitWindow(800, 600, "Pong");
	InitAudioDevice(); // Inizializza device audio

	SetWindowState(FLAG_VSYNC_HINT);

	// Load global data (assets that must be available in all screens, i.e. font)
	Font font = LoadFont("resources/mecha.png");
	Music music = LoadMusicStream("resources/ambient.ogg"); 
	Sound fxCoin = LoadSound("resources/coin.wav");

	SetMusicVolume(music, 1.0f);
	PlayMusicStream(music);

	SetTargetFPS(60); // Set our game to run at 60 frames-per-second

	// Creazione oggetti
	Ball ball(GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f, 5.0f);
	Paddle paddleSX(50, GetScreenHeight() / 2);
	Paddle paddleDX(GetScreenWidth() - 50, GetScreenHeight() / 2);
	const char* winnerText = nullptr;
	//--------------------------------------------------------------------------------------

	// Main game loop
	while(!WindowShouldClose()) {

		UpdateMusicStream(music); // NOTA: necessario per continuare la riproduzione nel loop

		// Calcolo nuova posizione degli oggetti prima di disegnarli
		//--------------------------------------------------------------------------------------
		ball.move(GetFrameTime());

		if(IsKeyDown(KEY_W)) 
			paddleSX.move(movement::UP, GetFrameTime());
		
		if(IsKeyDown(KEY_S)) 
			paddleSX.move(movement::DOWN, GetFrameTime());
		
		if(IsKeyDown(KEY_UP)) 
			paddleDX.move(movement::UP, GetFrameTime());
		
		if(IsKeyDown(KEY_DOWN)) 
			paddleDX.move(movement::DOWN, GetFrameTime());
		
		// Verifico se c'è collisione con player Paddle
		ball.checkCollisions(paddleSX.getRect(), paddleDX.getRect(), fxCoin);
		winnerText = ball.handleWinner();

		// Se sono nella schermata che mostra il vincitore e premo "spazio" ricomincio il gioco
		if(winnerText && IsKeyPressed(KEY_SPACE)) {
			ball = Ball(GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f, 5.0f);
			winnerText = nullptr;
		}
		//--------------------------------------------------------------------------------------

		// Disegno gli oggetti
		//--------------------------------------------------------------------------------------
		BeginDrawing();
		ClearBackground(BLACK);

		ball.draw();
		paddleSX.draw();
		paddleDX.draw();

		if(winnerText) {
			int textWidth = MeasureText(winnerText, 60);
			DrawText(winnerText, GetScreenWidth() / 2 - textWidth / 2, GetScreenHeight() / 2 - 30, 60, YELLOW);
		}

		DrawFPS(10, 10);
		EndDrawing();
		//--------------------------------------------------------------------------------------
	}

	// Unload global data loaded before closing
	//--------------------------------------------------------------------------------------
	UnloadFont(font);
	UnloadMusicStream(music);
	UnloadSound(fxCoin);

	CloseAudioDevice(); // Close audio context
	CloseWindow();
	//--------------------------------------------------------------------------------------

	return 0;
}