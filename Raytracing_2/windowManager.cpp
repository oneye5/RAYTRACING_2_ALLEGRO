#include "windowManager.h"


	int WindowWidth = 1270;
	int WindowHeight = 720;
	bool running = true;
	ALLEGRO_DISPLAY* Display;
	ViewPort viewPort;
	ALLEGRO_EVENT_QUEUE* Queue;
	void WindowManager::initWindow()
	{
		al_init();
		al_init_primitives_addon();
		Queue = al_create_event_queue();;
		Display = al_create_display(WindowWidth, WindowHeight);
		al_install_keyboard();

		al_register_event_source(Queue, al_get_keyboard_event_source());
		al_register_event_source(Queue, al_get_display_event_source(Display));
	}
	void WindowManager::initRenderer()
	{
		ViewPort viewPort = ViewPort();
		viewPort.InitViewPort(0.0f, 0.0f, -10.0f,
			0.0f, 0.0f,
			WindowWidth, WindowHeight,
			90.0f, 90.0f, 0.25);

		viewPort.InitGeometry();
	}
	 void Render()
	{
		auto pixels = viewPort.Render();
		int i = 0;
		for(int y = 0; y < WindowHeight-1;i++)
		{
			for (int x = 0; x < WindowWidth - 1; i++)
			{
				i++;
				al_draw_pixel(x, y, al_map_rgb(pixels[i].R, pixels[i].G, pixels[i].B));
			}
		}
	}
	void WindowManager::windowLoop()

	{
#pragma endregion
		do
		{
			Render();
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
