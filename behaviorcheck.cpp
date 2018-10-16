#include "behaviorcheck.h"

#pragma warning(disable:4503)

using namespace std;

void behaviorCheck()
{
	int warningcount = 0;

	// test if anim file used has been registered
	for (auto it = usedAnim.begin(); it != usedAnim.end(); ++it)
	{
		vecstr forwardPort = behaviorJoints[it->first];

		for (auto& behavior : forwardPort)
		{
			for (auto& path : it->second)
			{
				string filename = GetFileName(path);

				if (!registeredAnim[behavior][filename])
				{
					WarningMessage(1013, behavior + ".hkx", path);
					++warningcount;
				}
			}
		}
	}

	// test duplicate anim file
	for (auto& animation : animModMatch)		// first string
	{
		for (auto duplicatelist : animation.second)		// second string
		{
			if (duplicatelist.second.size() == 2)
			{
				if (duplicatelist.second[0].size() > 1)
				{
					string warning;

					for (auto& duplicate : duplicatelist.second[1])
					{
						warning = warning + duplicate + ",";
					}

					warning.pop_back();
					WarningMessage(1014, animation.first, duplicatelist.first, warning);
					++warningcount;
				}
			}
			else
			{
				ErrorMessage(1066);
				interMsg("Conflict Test failed!");
				return;
			}
		}
	}
	
	interMsg("Warning Count: " + to_string(warningcount));
}
