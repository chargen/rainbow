#include "Platform.h"
#if defined(RAINBOW_ANDROID)

#include "Platforms/SysUtil.h"

namespace Rainbow
{
	namespace SysUtil
	{
		bool has_accelerometer()
		{
			return true;
		}

		bool has_touchscreen()
		{
			return true;
		}

		void locales(Vector<char*> &locales)
		{
			locales.push_back(new char[3]);
			strcpy(locales[0], "en");
		}
	}
}

#endif
