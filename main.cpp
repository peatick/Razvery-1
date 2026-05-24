#include "sdl2/include/SDL.h"
#include "sdl2/include/SDL_ttf.h"
#include "sdlutil.h"
#include "ui_cfg.h"
#include <algorithm>
#include <climits>
#include <deque>
#include <sstream>
#include <string>
#include <vector>



int main(int argc, char* argv[]) {
    const char* fontPath = (argc > 1) ? argv[1] : "";

    Renderer renderer;
    if (!renderer.init(fontPath)) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Init: %s | %s", SDL_GetError(), TTF_GetError());
        return 1;
    }

    file_explorer file_ex;
	file_ex.F_X = 0; file_ex.F_Y = 20;
    file_ex.F_W = 200;file_ex.F_H = WIN_H - 20;
    workspace ws;
    ws.init(renderer);
    /*
        "SDL2 テキストエディタ  (差分方式 Undo/Redo)\n"
        "IME入力（日本語・中国語・韓国語）対応\n"
        "\n"
        "ショートカット:\n"
        "  Ctrl+A            全選択\n"
        "  Ctrl+C            コピー\n"
        "  Ctrl+X            カット\n"
        "  Ctrl+V            ペースト\n"
        "  Ctrl+Z            アンドゥ\n"
        "  Ctrl+Y / Ctrl+Shift+Z  リドゥ\n"
        "  Shift+矢印        選択\n"
        "  Ctrl+矢印         単語単位移動\n"
        "  Home/End          行頭/行末\n"
        "  Ctrl+Home/End     文書頭/末尾\n"
        "  ダブルクリック    単語選択\n"
    */
    file_ex.init(renderer.lineH);
    UI ui;
	UI_CFG ui_cfg;
	ui_cfg.init(ui);
    int mx = 0;
    int my = 0;
	int mousex = 0, mousey = 0;
    bool running = true, mouseDown = false;
	bool bef_mousebtn = false, now_mousebtn = false;
    auto imitate_btn = [&renderer, &ui](std::string but_key) {
		renderer.btn_draw(ui, but_key);
		return ui.button(but_key);
    };
    while (running) {
        SDL_Event e;
        Editor& ed = ws.work_s[ws.active].edits;
        while (SDL_PollEvent(&e)) {
            mousex = e.button.x;
            mousey = e.button.y;
            switch (e.type) {
            case SDL_QUIT: running = false; break;
            }
			SDL_Point mouse_P = { mx, my };
            ws.search_box_event(e,mouse_P);
            textEditEvent(e, ed, renderer, mouseDown, mx, my, !ws.search_mode);
            textEditEvent_sh(e, ws.search_box, renderer, mouseDown, mx, my, ws.search_mode);
            textEditEvent_sh(e, file_ex.ed, renderer, mouseDown, mx, my, true);
            file_explorer_event(e,file_ex,renderer,true);
            if (e.type == SDL_MOUSEBUTTONDOWN) {
                mx = e.button.x;
                my = e.button.y;
            }
            /*
            if (buttonClicked(e, {0,0,70,20}, {e.button.x,e.button.y})) {
                printf("Click!\n");
                ed.buf.setAllText(file_ex.get_str);
            }
            */
			renderer.mouse_logical_pos(mousex, mousey);
			ui.mousePos = { mousex, mousey };
			now_mousebtn = e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT;
			ui.Left_click = ui.pulse_click(bef_mousebtn, now_mousebtn);
            bef_mousebtn = now_mousebtn;
        }
        renderer.draw_bg({250,250,250,255});
        renderer.TextBox(ed);
        renderer.update_fs_explorer(file_ex);
		renderer.search_box(ws.search_box, ws.search_results, ws.search_index, ws.search_mode);
        if (imitate_btn("File")) {
            ws.search_str(ws.search_box.buf.line(0));
        }
        if (imitate_btn("Edit")) {
            ws.search_box_cursor_move();
        }
        
        renderer.rend();
    }
    renderer.destroy();
    return 0;
}

