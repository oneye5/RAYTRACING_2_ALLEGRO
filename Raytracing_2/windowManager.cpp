#include "windowManager.h"


	int WindowWidth = 200;
	int WindowHeight = 200;
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
		viewPort.InitViewPort(0.0f, 0.0f, 0.0f,
			0.0f, 0.0f,
			WindowWidth, WindowHeight,
			60.0f, 60.0f);

		viewPort.InitGeometry();
	}
	 void Render()
	{
		auto pixels = viewPort.Render();
		int x = 0;
		int y = 0;
		for (int i = 0; i < pixels.size(); i++)
		{
			al_draw_pixel(x, y, al_map_rgb(pixels[i].R, pixels[i].G, pixels[i].B));
			x++;
			if (x > WindowWidth - 1)
			{
				y++;
					x = 0;
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
