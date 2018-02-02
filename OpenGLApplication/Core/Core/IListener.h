/*



*/
#pragma once
namespace Core
{
	class IListener
	{
	public:
		virtual ~IListener() = 0;

		virtual void NotifyBeginFrame()   = 0;
		virtual void NotifyDisplayFrame() = 0;
		virtual void NotifyEndFrame()     = 0;
		virtual void NotifyResize(int width, int height,
								  int previousWidth, int previousHeight) = 0;
	};

	inline IListener::~IListener()
	{
		
	}
}

