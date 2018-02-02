/*



*/
#pragma once
#include <string>

namespace Core
{
	struct WindowInfo
	{
		std::string name;
		int width;
		int height;
		int position_x;
		int position_y;
		bool is_resizable;

		WindowInfo()
		{
			name = "OpenGL Application";
			width = 800;
			height = 600;
			position_x = 500;
			position_y = 500;
			is_resizable = true;
		}

		WindowInfo(std::string name,
				   int startPositionX, int startPositionY,
				   int width, int height,
				   bool isResizable)
		{

			this->name = name;
			this->position_x = startPositionX;
			this->position_y = startPositionY;

			this->width  = width;
			this->height = height;
			this->is_resizable = isResizable;
		}


		WindowInfo(const WindowInfo& windowInfo)
		{
			name = windowInfo.name;
			position_x = windowInfo.position_x;
			position_y = windowInfo.position_y;

			width = windowInfo.width;
			height = windowInfo.height;
			is_resizable = windowInfo.is_resizable;
		}

		void operator=(const WindowInfo& windowInfo)
		{

			name = windowInfo.name;

			position_x = windowInfo.position_x;
			position_y = windowInfo.position_y;

			width = windowInfo.width;
			height = windowInfo.height;
			is_resizable = windowInfo.is_resizable;
		}
	};
}