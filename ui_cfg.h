#pragma once
#include "sdlutil.h"
#include <string>
#include <vector>
class UI_CFG {
public:
	void init(UI& ui) {
		ui.button_map["File"] = { {0,0,70,20},"File" };
		ui.button_map["File"].isTGR = true;
		ui.button_map["Edit"] = { {70,0,70,20},"Edit" };
		ui.button_map["Edit"].isTGR = true;
	}
};