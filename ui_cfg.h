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
		ui.button_map["View"] = { {140,0,70,20},"View" };
		ui.button_map["View"].isTGR = true;
		ui.button_map["Texteditor"] = { {140,20,70,20},"Texteditor" };
		ui.button_map["Texteditor"].isTGR = true;
		ui.button_map["Texteditor"].group = "View";
	}
};