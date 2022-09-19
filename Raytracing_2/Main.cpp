#include "Main.h"
static class MAIN
{
public:

}Main;
int main()
{
#pragma region WindowInit
	int WindowWidth = 1270;
	int WindowHeight = 720;
	bool running = true;
	al_init();
	al_init_primitives_addon();
	ALLEGRO_EVENT_QUEUE* Queue = al_create_event_queue();;
	ALLEGRO_DISPLAY* Display = al_create_display(WindowWidth,WindowHeight);
	al_install_keyboard();

	al_register_event_source(Queue, al_get_keyboard_event_source());
	al_register_event_source(Queue, al_get_display_event_source(Display));
#pragma endregion
#pragma region RenderInit
	/*
		ViewPort viewPort = ViewPort();
		viewPort.InitViewPort(0.0f,0.0f,-10.0f,
			0.0f,0.0f,
			WindowWidth,WindowHeight,
			90.0f,90.0f,0.25);

		viewPort.InitGeometry();
		*/
#pragma endregion
#pragma region localMethods

#pragma endregion
	do
	{
		al_draw_pixel(5, 5, al_map_rgb(255, 255, 255));
		al_flip_display();

		//event handeling
#pragma region eventHandler
		ALLEGRO_EVENT Event;
		al_wait_for_event(Queue, &Event);
		if (Event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			running = false;
#pragma endregion
	} while (running);
	al_destroy_display(Display);
	al_uninstall_keyboard();
}