#include "tab.h"
#include "child.h"
#include "../Variables.h"
void c_tab::draw(Vector2D pos, Vector2D size) {
	c_child* c = (c_child*)child;
	auto alpha = (int)(c->get_transparency() * 2.55f);
	bool hovered = g_mouse.x > pos.x && g_mouse.y > pos.y
		&& g_mouse.x < pos.x + size.x && g_mouse.y < pos.y + size.y;
	if (hovered && !c->g_active_element && !c->is_holding_menu()) {
		c->g_hovered_element = this;
		if (c->is_click()) {
			c->set_active_tab_index(this->index);
			c->reset_mouse();

		}

		if (animation < 1.f) animation += animation_speed;

	}
	else {
		if (animation > 0.f) animation -= animation_speed;
	}

	animation = clamp(animation, 0.f, 1.f);

	auto clr = color_t(18 + animation * 20.f, 18 + animation * 20.f, 18 + animation * 20.f, alpha);
	auto clr2 = color_t(18 - animation * 20.f, 18 - animation * 20.f, 18 - animation * 20.f, alpha);

	//g_Render->FilledRect(pos.x + 1, pos.y + 1, size.x - 2, size.y - 2, clr);

	auto t_clr = color_t(150 + animation * 20.f, 150 + animation * 20.f, 150 + animation * 20.f, alpha);
	if (c->get_active_tab_index() == this->index)
	{
		//g_Render->DrawString(pos.x + 40 + size.x / 2, pos.y + size.y / 2, t_clr, render::centered_y , fonts::menu_main, get_title().c_str());
		
		//g_Render->Rect(pos.x + 34, pos.y- 1, size.x - 21, size.y - 3, color_t(7, 7, 7, alpha));// linha72,72,72
		//g_Render->Rect(pos.x + 34, pos.y, size.x - 21, size.y - 1, color_t(34, 34, 34, alpha));// linh1
		g_Render->FilledRect(pos.x + 32, pos.y -2.5, size.x - 12, size.y +5, color_t(07, 7,7, alpha));
		g_Render->FilledRect(pos.x + 32, pos.y - 1.5, size.x -11, size.y +3, color_t(34, 34, 34, alpha));
		g_Render->FilledRect(pos.x + 32, pos.y , size.x-10, size.y -1, color_t(16, 16, 16, alpha));
		t_clr = color_t(175, 175, 175, alpha);
	}
	else
	{
		t_clr = color_t(100 + animation * 20.f, 100 + animation * 20.f, 100 + animation * 20.f, alpha);
	}
	//auto t_clr = color_t(255, 255, 255, alpha);

	g_Render->DrawString(pos.x + 25 + size.x / 2, pos.y -1+ size.y / 2, color_t(0, 0, 0, alpha), render::centered_y | render::centered_x, fonts::menu_tab, get_title().c_str());
	g_Render->DrawString(pos.x + 26 + size.x / 2, pos.y + size.y / 2, t_clr, render::centered_y | render::centered_x, fonts::menu_tab, get_title().c_str());

}
void c_tab::special_render() {

}
void c_tab::render() {

}