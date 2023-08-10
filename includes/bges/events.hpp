#ifndef BGES_EVENTS_HPP
#define BGES_EVENTS_HPP

#include <cstdint>
#include <cstddef>

namespace bges {
enum class MouseButton {
	left,
	right,
	middle,
	prev,
	next,

	unlisted,

	MAX_BTN_VALUE
};

enum class ScrollDirection {
	up,
	down,
	left,
	right,

	MAX_DIR_VALUE
};

enum class Key {
	keyboard0,
	keyboard1,
	keyboard2,
	keyboard3,
	keyboard4,
	keyboard5,
	keyboard6,
	keyboard7,
	keyboard8,
	keyboard9,
	numpad0,
	numpad1,
	numpad2,
	numpad3,
	numpad4,
	numpad5,
	numpad6,
	numpad7,
	numpad8,
	numpad9,
	numpad_decimal_separator,
	star,
	slash,
	minus,
	plus,
	percent,
	a,
	b,
	c,
	d,
	e,
	f,
	g,
	h,
	i,
	j,
	k,
	l,
	m,
	n,
	o,
	p,
	q,
	r,
	s,
	t,
	u,
	v,
	w,
	x,
	y,
	z,
	F1,
	F2,
	F3,
	F4,
	F5,
	F6,
	F7,
	F8,
	F9,
	F10,
	F11,
	F12,
	F13,
	F14,
	F15,
	space,
	enter,
	del,
	backspace,
	up,
	down,
	left,
	right,
	page_up,
	page_down,
	tab,
	end,
	escape,
	insert,
	pause,
	playpause,
	play,
	right_ctrl,
	left_ctrl,
	right_caps,
	left_caps,
	right_shift,
	left_shift,
	right_alt,
	left_alt,
	meta,
	right_system,
	left_system,
	menu,

	unlisted,

	MAX_KEY_CODE,
};
} // namespace bges

namespace bges::event {
namespace details {
	struct MouseBaseEv {
		float x; // <! x coordinate relative to child
		float y; // <! y coordinate relative to child
	};
	struct KeyboardBaseEv {
		std::uint16_t backend_key_code;
		Key key;
		bool is_meta_pressed;
		bool is_shift_pressed;
		bool is_caps_pressed; // or on
		bool is_alt_pressed;
		bool is_ctrl_pressed;
	};
} // namespace details

struct MouseMove: details::MouseBaseEv { };

struct MousePress: details::MouseBaseEv {
	MouseButton button;
	std::uint8_t backend_code;
};

struct MouseRelease: details::MouseBaseEv {
	MouseButton button;
	std::uint8_t backend_code;
};

struct MouseScroll: details::MouseBaseEv {
	std::uint8_t delta;
	std::uint8_t backend_wheel_id;
	ScrollDirection direction;
};

struct KeyPress: details::KeyboardBaseEv { };

struct KeyRelease: details::KeyboardBaseEv { };

struct Resize {
	unsigned int width;
	unsigned int height;
};

struct CloseRequest { };

struct FocusLose { };

struct FocusGain { };

struct Click {
	MouseButton button;
};

struct DataUpdate { };

struct AtomicTextUpdate {
	std::size_t update_index; // index at which the text has been updated
};
} // namespace bges::event

#endif //BGES_EVENTS_HPP
