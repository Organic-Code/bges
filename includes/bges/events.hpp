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
	struct EventBase {
		void consume() const noexcept { consumed = true; }
		bool is_consumed() const noexcept { return consumed; }
	private:
		mutable bool consumed{false};
	};
	struct MouseBaseEv : EventBase {
		MouseBaseEv(float x, float y) noexcept : x{x}, y{y} { }

		float x; // <! x coordinate relative to child
		float y; // <! y coordinate relative to child
	};
	struct KeyboardBaseEv : EventBase {
		KeyboardBaseEv(std::uint16_t backend_key_code, Key key,	bool is_meta_pressed, bool is_shift_pressed, bool is_caps_pressed, bool is_alt_pressed, bool is_ctrl_pressed) noexcept
		    : backend_key_code{backend_key_code}, key{key}, is_meta_pressed{is_meta_pressed}, is_shift_pressed{is_shift_pressed}, is_caps_pressed{is_caps_pressed}, is_alt_pressed{is_alt_pressed}, is_ctrl_pressed{is_ctrl_pressed} { }
		std::uint16_t backend_key_code;
		Key key;
		bool is_meta_pressed;
		bool is_shift_pressed;
		bool is_caps_pressed; // or on
		bool is_alt_pressed;
		bool is_ctrl_pressed;
	};
} // namespace details

struct MouseMove: details::MouseBaseEv {
	MouseMove(float x, float y) noexcept : details::MouseBaseEv{x, y} { }
};

struct MousePress: details::MouseBaseEv {
	MousePress(float x, float y, MouseButton button, std::uint8_t code) noexcept
	    : details::MouseBaseEv{x, y}, button{button}, backend_code{code} { }

	MouseButton button;
	std::uint8_t backend_code;
};

struct MouseRelease: details::MouseBaseEv {
	MouseRelease(float x, float y, MouseButton button, std::uint8_t code) noexcept
	    : details::MouseBaseEv{x, y}, button{button}, backend_code{code} { }

	MouseButton button;
	std::uint8_t backend_code;
};

struct MouseScroll: details::MouseBaseEv {
	MouseScroll(float x, float y, std::uint8_t delta, std::uint8_t wheel, ScrollDirection dir) noexcept
	    : details::MouseBaseEv{x, y}, delta{delta}, backend_wheel_id{wheel}, direction{dir} { }

	std::uint8_t delta;
	std::uint8_t backend_wheel_id;
	ScrollDirection direction;
};

struct MouseEnter: details::MouseBaseEv {
	MouseEnter(float x, float y) noexcept : details::MouseBaseEv{x, y} { }
};

struct MouseExit: details::MouseBaseEv {
	MouseExit(float x, float y) noexcept : details::MouseBaseEv{x, y} { }
};

struct KeyPress: details::KeyboardBaseEv {
	KeyPress(std::uint16_t backend_key_code, Key key,	bool is_meta_pressed, bool is_shift_pressed, bool is_caps_pressed, bool is_alt_pressed, bool is_ctrl_pressed) noexcept
			: details::KeyboardBaseEv{backend_key_code, key, is_meta_pressed, is_shift_pressed, is_caps_pressed, is_alt_pressed, is_ctrl_pressed} { }
};

struct KeyRelease: details::KeyboardBaseEv {
	KeyRelease(std::uint16_t backend_key_code, Key key,	bool is_meta_pressed, bool is_shift_pressed, bool is_caps_pressed, bool is_alt_pressed, bool is_ctrl_pressed) noexcept
		: details::KeyboardBaseEv{backend_key_code, key, is_meta_pressed, is_shift_pressed, is_caps_pressed, is_alt_pressed, is_ctrl_pressed} { }
};

struct Resize : details::EventBase {
	Resize(unsigned int width, unsigned int height) noexcept : width{width}, height{height} { }

	unsigned int width;
	unsigned int height;
};

struct CloseRequest : details::EventBase {
	CloseRequest() noexcept = default;
};

struct FocusLose : details::EventBase {
	FocusLose() noexcept = default;
};

struct FocusGain : details::EventBase {
	FocusGain() noexcept = default;
};

struct Click : details::EventBase {
	Click(MouseButton button) noexcept : button{button} { }
	MouseButton button;
};

struct DataUpdate : details::EventBase {
	DataUpdate() noexcept = default;
};

struct AtomicTextUpdate : details::EventBase {
	AtomicTextUpdate(std::size_t update_index) noexcept : update_index{update_index} { }

	std::size_t update_index; // index at which the text has been updated
};
} // namespace bges::event

#endif //BGES_EVENTS_HPP
