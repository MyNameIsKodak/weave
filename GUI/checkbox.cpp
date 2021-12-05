#include "checkbox.h"
#include "window.h"
#include "child.h"

bool c_checkbox::update()
{
	if (should_render)
		if (!should_render())
			return false;

	c_child* c = (c_child*)child;
	if (!c) return false;
	auto wnd = (c_window*)c->get_parent();
	if (!wnd) return false;
	if (wnd->g_active_element != this && wnd->g_active_element != nullptr) return true;
	auto pos = c->get_cursor_position();
	bool h = hovered();

	if (wnd->get_active_tab_index() != this->tab && wnd->get_tabs().size() > 0)
		return false;
	if (h) wnd->g_hovered_element = this;

	// bullshit animations
	if (h) {
		if (animation < 1.f) animation += animation_speed;
	}
	else {
		if (animation > 0.f) animation -= animation_speed;
	}
	animation = std::clamp(animation, 0.f, 1.f);

	if (h && c->hovered() && wnd->is_click()) {
		*(bool*)value = !(*(bool*)value);
		return true;
	}

	if (*(bool*)value == true) {
		if (press_animation < 1.f)
			press_animation += animation_speed;
	}
	else {
		if (press_animation > 0.f)
			press_animation -= animation_speed;
	}
	
	press_animation = std::clamp(press_animation, 0.f, 1.f);
	return true;
}

bool c_checkbox::hovered()
{
	if (should_render)
		if (!should_render())
			return false;
	c_child* c = (c_child*)child;
	if (!c->hovered())
		return false;
	auto pos = c->get_cursor_position();
	ImGui::PushFont(fonts::menu_desc);
	auto size = ImGui::CalcTextSize(label.c_str());
	ImGui::PopFont();
	return g_mouse.x > pos.x - 30 && g_mouse.y > pos.y - 2
		&& g_mouse.x < pos.x + size.x && g_mouse.y < pos.y + size.y + 2;
}

void c_checkbox::render() {
	if (should_render)
		if (!should_render())
			return;
	c_child* c = (c_child*)child;
	auto pos = c->get_cursor_position();

	auto wnd = (c_window*)c->get_parent();
	auto size = ImGui::CalcTextSize(label.c_str());
	if (!wnd) return;
	if (wnd->get_active_tab_index() != this->tab
		&& wnd->get_tabs().size() > 0) return;
	auto alpha = (int)(wnd->get_transparency() * 2.55f);
	//g_Render->DrawString(pos.x, pos.y, 
	//	style.get_color(c_style::text_color).transition(style.get_color(c_style::text_color_hovered), animation).manage_alpha(alpha),
	//	render::none, fonts::menu_desc, label.c_str());

	g_Render->DrawString(pos.x, pos.y - 3, color_t(200 + 55.f * animation, 200 + 55.f * animation, 200 + 55.f * animation, alpha), render::outline, fonts::menu_main, label.c_str());
	//pos -= Vector2D(36, 0);


	g_Render->FilledRect(pos.x - 20, pos.y + 2, 8, 8, !(*(bool*)value) ? color_t(72, 72, 72, alpha) : color_t(110, 184, 13,255));


	g_Render->Rect(pos.x - 20, pos.y + 2, 8, 8, color_t(17, 17, 17, alpha));
}

