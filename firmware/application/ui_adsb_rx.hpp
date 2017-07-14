/*
 * Copyright (C) 2015 Jared Boone, ShareBrained Technology, Inc.
 * Copyright (C) 2017 Furrtek
 * 
 * This file is part of PortaPack.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#include "ui.hpp"
#include "file.hpp"
//#include "ui_textentry.hpp"
//#include "ui_widget.hpp"
#include "ui_navigation.hpp"
#include "ui_font_fixed_8x16.hpp"

#include "message.hpp"
#include "portapack.hpp"

namespace ui {

class ADSBRxView : public View {
public:
	ADSBRxView(NavigationView& nav);
	~ADSBRxView();
	
	void focus() override;
	
	std::string title() const override { return "ADS-B debug"; };

private:
	static constexpr float k = 1.0f / 128.0f;
	
	File iq_file { };
	
	void analyze(uint64_t offset);
	
	Labels labels {
		{ { 0 * 8, 0 * 8 }, "Test", Color::light_grey() }
	};
	
	NumberField offset_field {
		{ 0, 0 },
		6,
		{ 0, 819200 },	// * 256 -> file offset
		1,
		'0'
	};
	Text text_debug_e {
		{ 7 * 8, 0 * 16, 14 * 8, 16 },
		"-"
	};
	
	Text text_debug_a {
		{ 0 * 8, 1 * 16, 30 * 8, 16 },
		"-"
	};
	Text text_debug_b {
		{ 0 * 8, 2 * 16, 30 * 8, 16 },
		"-"
	};
	Text text_debug_c {
		{ 0 * 8, 3 * 16, 30 * 8, 16 },
		"-"
	};
	Text text_debug_d {
		{ 0 * 8, 4 * 16, 30 * 8, 16 },
		"-"
	};
	
	Button button_ffw {
		{ 176, 0 * 16, 64, 16 },
		"+50ms"
	};
	
	/*
	MessageHandlerRegistration message_handler_tx_done {
		Message::ID::TXDone,
		[this](const Message* const p) {
			const auto message = *reinterpret_cast<const TXDoneMessage*>(p);
			this->on_txdone(message.done);
		}
	};*/
};

} /* namespace ui */
