#include "choose_color.hpp"

ChooseColorView::ChooseColorView(xpcc::gui::ViewStack* stack,
		uint8_t identifier) :
		AbstractView(stack, identifier, xpcc::gui::Dimension(320, 240)),
//		button1("Test", xpcc::gui::Dimension(80, 30)),
		lbl_yellow("YELLOW"),
		lbl_red("RED"),
		yellow(xpcc::gui::Color::YELLOW, xpcc::gui::Dimension(159, 240)),
		red(xpcc::gui::Color::RED, xpcc::gui::Dimension(160, 240))
{
	this->pack(&yellow, xpcc::glcd::Point(0, 0));
	this->pack(&red, xpcc::glcd::Point(160, 0));

	this->pack(&lbl_yellow, xpcc::glcd::Point(20, 40));
	this->pack(&lbl_red, xpcc::glcd::Point(210, 40));

	lbl_yellow.setFont(xpcc::font::Ubuntu_36);
	lbl_red.setFont(xpcc::font::Ubuntu_36);

	yellow.cb_activate = &activate_yellow;
	yellow.cb_deactivate = &deactivate_yellow;

	red.cb_activate = &activate_red;
	red.cb_deactivate = &deactivate_red;

	this->colorpalette[xpcc::gui::Color::TEXT] = xpcc::glcd::Color::blue();
	this->colorpalette[xpcc::gui::Color::ACTIVATED] = xpcc::glcd::Color::green();

}

bool ChooseColorView::hasChanged()
{
	return true;
}

void ChooseColorView::activate_yellow(const InputEvent& ev, Widget* w, void* data)
{
	(void) ev;
	(void) data;

	auto yellow = static_cast<FilledAreaButton*>(w);
	yellow->setColor(xpcc::gui::Color::ACTIVATED);
}

void ChooseColorView::deactivate_yellow(const InputEvent& ev, Widget* w, void* data)
{
	(void) ev;
	(void) data;

	auto yellow = static_cast<FilledAreaButton*>(w);
	yellow->setColor(xpcc::gui::Color::YELLOW);
}

void ChooseColorView::activate_red(const InputEvent& ev, Widget* w, void* data)
{
	(void) ev;
	(void) data;

	auto yellow = static_cast<FilledAreaButton*>(w);
	yellow->setColor(xpcc::gui::Color::ACTIVATED);
}

void ChooseColorView::deactivate_red(const InputEvent& ev, Widget* w, void* data)
{
	(void) ev;
	(void) data;

	auto yellow = static_cast<FilledAreaButton*>(w);
	yellow->setColor(xpcc::gui::Color::RED);
}
