#ifndef BGES_COMMON_EXCHANGED_TYPES_H
#define BGES_COMMON_EXCHANGED_TYPES_H

#define BGES_TMP_ACTUALLY_CONCAT(x, y) x##y
#define BGES_TMP_CONCAT(x, y)          BGES_TMP_ACTUALLY_CONCAT(x, y)

#if defined __cplusplus
#	include <cstdint>
#	define BGES_NAMESPACE(x)     namespace x {
#	define BGES_INL_NAMESPACE(x) inline namespace x {
#	define BGES_END_NAMESPACE    }
#	define BGES_NAME(x)          x
#	define BGES_ENUMNAME(x)      x
#else
#	include <stdint.h>
#	include <bool.h>
#	define BGES_NAMESPACE(x)
#	define BGES_INL_NAMESPACE(x)
#	define BGES_END_NAMESPACE
#	define BGES_NAME(x)     bges_##x
#	define BGES_ENUMNAME(x) BGES_TMP_CONCAT(BGES_TMP_CONCAT(BGES_, BGES_TMP_ENAME), x)
#endif

BGES_NAMESPACE(bges_ffi)
BGES_INL_NAMESPACE(version_0)

typedef struct bges_version {
	uint8_t major; // any source changes introducing  breaking changes to the API
	uint8_t minor; // any source changes that modify the API in a backward-compatible way
	uint8_t patch; // any source changes that do not modify the API
} BGES_NAME(version);

typedef struct bges_point {
	int32_t x;
	int32_t y;
	uint32_t resolution; // float_pos = int32_pos / resolution
} BGES_NAME(point);

typedef struct bges_size {
	uint32_t width;
	uint32_t height;
} BGES_NAME(size);

typedef struct bges_color {
	float red;
	float green;
	float blue;
	float alpha;
} BGES_NAME(color);

typedef struct bges_viewport {
	float x; // left x
	float y; // top y
	float width;
	float height;
} BGES_NAME(viewport);

#define BGES_TMP_ENAME EVTT_
BGES_NAMESPACE(event_type)
typedef enum {
	BGES_ENUMNAME(KEY_PRESS),
	BGES_ENUMNAME(KEY_RELEASE),
	BGES_ENUMNAME(MOUSE_PRESS),
	BGES_ENUMNAME(MOUSE_RELEASE),
	BGES_ENUMNAME(MOUSE_MOVE),
	BGES_ENUMNAME(MOUSE_SCROLL),
	BGES_ENUMNAME(RESIZE),
	BGES_ENUMNAME(FOCUS_LOSE),
	BGES_ENUMNAME(FOCUS_GAIN),
	BGES_ENUMNAME(MINIMIZE),
	BGES_ENUMNAME(CLOSE),

	BGES_ENUMNAME(MAX_EVENT_TYPE)
} BGES_NAME(event_type);
BGES_END_NAMESPACE
#undef BGES_TMP_ENAME

#define BGES_TMP_ENAME KEY_
BGES_NAMESPACE(key)
typedef enum {
	BGES_ENUMNAME(KB_0),
	BGES_ENUMNAME(KB_1),
	BGES_ENUMNAME(KB_2),
	BGES_ENUMNAME(KB_3),
	BGES_ENUMNAME(KB_4),
	BGES_ENUMNAME(KB_5),
	BGES_ENUMNAME(KB_6),
	BGES_ENUMNAME(KB_7),
	BGES_ENUMNAME(KB_8),
	BGES_ENUMNAME(KB_9),
	BGES_ENUMNAME(NUM_0),
	BGES_ENUMNAME(NUM_1),
	BGES_ENUMNAME(NUM_2),
	BGES_ENUMNAME(NUM_3),
	BGES_ENUMNAME(NUM_4),
	BGES_ENUMNAME(NUM_5),
	BGES_ENUMNAME(NUM_6),
	BGES_ENUMNAME(NUM_7),
	BGES_ENUMNAME(NUM_8),
	BGES_ENUMNAME(NUM_9),
	BGES_ENUMNAME(NUM_DECIMAL_SEPARATOR),
	BGES_ENUMNAME(STAR),
	BGES_ENUMNAME(SLASH),
	BGES_ENUMNAME(MINUS),
	BGES_ENUMNAME(PLUS),
	BGES_ENUMNAME(PERCENT),
	BGES_ENUMNAME(A),
	BGES_ENUMNAME(B),
	BGES_ENUMNAME(C),
	BGES_ENUMNAME(D),
	BGES_ENUMNAME(E),
	BGES_ENUMNAME(F),
	BGES_ENUMNAME(G),
	BGES_ENUMNAME(H),
	BGES_ENUMNAME(I),
	BGES_ENUMNAME(J),
	BGES_ENUMNAME(K),
	BGES_ENUMNAME(L),
	BGES_ENUMNAME(M),
	BGES_ENUMNAME(N),
	BGES_ENUMNAME(O),
	BGES_ENUMNAME(P),
	BGES_ENUMNAME(Q),
	BGES_ENUMNAME(R),
	BGES_ENUMNAME(S),
	BGES_ENUMNAME(T),
	BGES_ENUMNAME(U),
	BGES_ENUMNAME(V),
	BGES_ENUMNAME(W),
	BGES_ENUMNAME(X),
	BGES_ENUMNAME(Y),
	BGES_ENUMNAME(Z),
	BGES_ENUMNAME(F1),
	BGES_ENUMNAME(F2),
	BGES_ENUMNAME(F3),
	BGES_ENUMNAME(F4),
	BGES_ENUMNAME(F5),
	BGES_ENUMNAME(F6),
	BGES_ENUMNAME(F7),
	BGES_ENUMNAME(F8),
	BGES_ENUMNAME(F9),
	BGES_ENUMNAME(F10),
	BGES_ENUMNAME(F11),
	BGES_ENUMNAME(F12),
	BGES_ENUMNAME(F13),
	BGES_ENUMNAME(F14),
	BGES_ENUMNAME(F15),
	BGES_ENUMNAME(SPACE),
	BGES_ENUMNAME(ENTER),
	BGES_ENUMNAME(DEL),
	BGES_ENUMNAME(BACKSPACE),
	BGES_ENUMNAME(UP),
	BGES_ENUMNAME(DOWN),
	BGES_ENUMNAME(LEFT),
	BGES_ENUMNAME(RIGHT),
	BGES_ENUMNAME(PAGE_UP),
	BGES_ENUMNAME(PAGE_DOWN),
	BGES_ENUMNAME(TAB),
	BGES_ENUMNAME(END),
	BGES_ENUMNAME(ESCAPE),
	BGES_ENUMNAME(INSERT),
	BGES_ENUMNAME(PAUSE),
	BGES_ENUMNAME(PLAYPAUSE),
	BGES_ENUMNAME(PLAY),
	BGES_ENUMNAME(RCTRL),
	BGES_ENUMNAME(LCTRL),
	BGES_ENUMNAME(RCAPS),
	BGES_ENUMNAME(LCAPS),
	BGES_ENUMNAME(RSHIFT),
	BGES_ENUMNAME(LSHIFT),
	BGES_ENUMNAME(RALT),
	BGES_ENUMNAME(LALT),
	BGES_ENUMNAME(META),
	BGES_ENUMNAME(RSYSTEM),
	BGES_ENUMNAME(LSYSTEM),
	BGES_ENUMNAME(MENU),

	BGES_ENUMNAME(UNLISTED_KEY_CODE),

	BGES_ENUMNAME(MAX_KEY_CODE)
} BGES_NAME(key);
BGES_END_NAMESPACE
#undef BGES_TMP_ENAME

#define BGES_TMP_ENAME MOUSE_BUTTON_
BGES_NAMESPACE(mouse_button)
typedef enum {
	BGES_ENUMNAME(LEFT),
	BGES_ENUMNAME(RIGHT),
	BGES_ENUMNAME(MIDDLE),
	BGES_ENUMNAME(PREVIOUS),
	BGES_ENUMNAME(NEXT),

	BGES_ENUMNAME(UNLISTED_BUTTON_CODE),

	BGES_ENUMNAME(MAX_BUTTON_CODE)
} BGES_NAME(mouse_button);
#undef BGES_TMP_ENAME
BGES_END_NAMESPACE

typedef struct bges_event {
	uint8_t type; // refers to the enum bges_event_type/bges_ffi::event_type::event_type
	union {
		struct {
			uint16_t hw_key_code; // "hardware" code (layout independent)
			uint16_t key; // refers to the enum bges_key/bges_ffi::key::key
			bool is_meta_pressed;
			bool is_shift_pressed;
			bool is_capslock_locked;
			bool is_alt_pressed;
			bool is_ctrl_pressed;
		} key;

		struct {
			uint8_t hw_btn_code; // "hardware" code
			uint8_t kind; // refers to the enum bges_mouse_button/bges_ffi::mouse_button::mouse_button
			struct bges_point pos;
		} mouse_button;

		struct {
			uint8_t delta;
			uint8_t wheel_id;
			bool horizontal_scroll; // (true), or vertical (false)
			bool upwards; // or downwards (horizontal : up = leftwards or down = rightwards)
			struct bges_point pos;
		} mouse_scroll;

		struct {
			struct bges_point pos;
		} mouse_move;

		struct bges_size window_size;
	};
} BGES_NAME(event);

typedef struct bges_event_list { // as an array
	struct bges_event *begin;
	struct bges_event *end;
} BGES_NAME(event_list);

typedef struct bges_backend_win_ctx {

	/** Methods populated by backend **/
	// mandatory methods
	uint8_t (*open)(
	  struct bges_backend_win_ctx *,
	  const char *window_name); // returns true (1) on success. On error, return false (0) and set error_str accordingly (if possible)
	void (*resize)(struct bges_backend_win_ctx *, struct bges_size);
	void (*move)(struct bges_backend_win_ctx *, struct bges_point delta); // TODO: EXPOSE moves the window (esp. usefull for subwindows)
	void (*set_position)(struct bges_backend_win_ctx *, struct bges_point); // TODO: EXPOSE (in frontend)
	void (*get_position)(struct bges_backend_win_ctx *, struct bges_point* out); // TODO: EXPOSE (in frontend)
	void (*close)(struct bges_backend_win_ctx *);
	bool (*is_open)(struct bges_backend_win_ctx *);
	void (*set_viewport)(struct bges_backend_win_ctx *, struct bges_viewport);

	void (*retrieve_events)(struct bges_backend_win_ctx *, struct bges_event_list *out);
	void (*free_events)(struct bges_backend_win_ctx *, struct bges_event_list *list);

	void (*render)(struct bges_backend_win_ctx *);
	void (*clear)(struct bges_backend_win_ctx *);

	void (*draw_line)(struct bges_backend_win_ctx *, struct bges_point begin, struct bges_point end, struct bges_color);

	// optional methods (will be populated by bges if the backend does not populate them)
	void (*draw_rectangle)(struct bges_backend_win_ctx *, struct bges_point, struct bges_size,
	                       struct bges_color); // min corner minimizes x and y
	void (*draw_outlined_rectangle)(struct bges_backend_win_ctx *, struct bges_point, struct bges_size, struct bges_color fill_color,
	                                uint16_t outline_thickness, struct bges_color outline_color); // min corner minimizes x and y

	// text management methods. Populate all or populate none. Used only if no fonts are set.
	void (*draw_text_line)(struct bges_backend_win_ctx *, struct bges_point, const char *text);
    	const char *(*draw_text_lenlim)(
	  struct bges_backend_win_ctx *, struct bges_point, const char *text,
	  uint32_t px_len); // prints at most px_len pixels.
						// Returns a pointer to the first char that was not printed, or to '\0' if all was printed
	uint32_t (*text_px_size)(struct bges_backend_win_ctx *, const char *text); // computes the length of the given string (in pixels)

	/** Stored Data **/
	// data
	void *data; // for sole use of backend ; lifetime managed by backend
	char *error_str; // used to report errors from within backend to bges. lifetime managed by backend
	struct bges_version backend_version;
} BGES_NAME(backend_win_ctx);

BGES_END_NAMESPACE
BGES_END_NAMESPACE

#undef BGES_NAMESPACE
#undef BGES_INL_NAMESPACE
#undef BGES_END_NAMESPACE
#undef BGES_NAME
#undef BGES_ENUMNAME
#undef BGES_TMP_CONCAT
#undef BGES_TMP_ACTUALLY_CONCAT

#endif //BGES_COMMON_EXCHANGED_TYPES_H
