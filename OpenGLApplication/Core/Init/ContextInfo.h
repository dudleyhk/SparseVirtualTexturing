/*



*/
#pragma once



namespace Core
{
	struct ContextInfo
	{
		int major_version;
		int minor_version;
		bool core;

		ContextInfo()
		{
			major_version = 3;
			minor_version = 3;
			core = true;
		}

		ContextInfo(int majorVersion, int minorVersion, bool core)
		{
			this->major_version = majorVersion;
			this->minor_version = minorVersion;
			this->core = core;
		}

		ContextInfo(const ContextInfo& contextInfo)
		{
			major_version = contextInfo.major_version;
			minor_version = contextInfo.minor_version;
			core = contextInfo.core;
		}

		void operator=(const ContextInfo& contextInfo)
		{
			major_version = contextInfo.major_version;
			minor_version = contextInfo.minor_version;
			core = contextInfo.core;
		}
	};
}