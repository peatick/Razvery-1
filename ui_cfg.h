#pragma once
#include "sdlutil.h"
#include <string>
#include <vector>
class UI_CFG {
public:
	void init(UI& ui) {
		ui.add_btn("File","Men_bar",true,{0,0,70,20});
		ui.add_btn("New","File",true,{0,20,70,20});
		ui.add_btn("Open","File",true,{0,40,70,20});
		ui.add_btn("Save","File",true,{0,60,70,20});
		ui.add_btn("Save as...","File",true,{0,80,70,20});
		ui.add_btn("Quit","File",true,{0,100,70,20});
		ui.add_btn("Edit","Men_bar",true,{70,0,70,20});
		ui.add_btn("View","Men_bar",true,{140,0,70,20});
		ui.add_btn("Texteditor","View",true,{140,20,70,20});
		ui.add_btn("LineNum","Texteditor",true,{210,20,70,20});
	}
};