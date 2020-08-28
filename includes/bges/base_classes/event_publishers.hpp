#ifndef BGES_BASE_CLASSES_EVENT_PUBLISHERS_HPP
#define BGES_BASE_CLASSES_EVENT_PUBLISHERS_HPP

#include <functional>
#include <unordered_map>

#include <bges/details/export.hpp>

namespace bges::event {
struct MouseMove;
struct MousePress;
struct MouseRelease;
struct MouseScroll;
struct KeyPress;
struct KeyRelease;
struct CloseRequest;
struct FocusLose;
struct FocusGain;
struct Resize;
struct Click;
} // namespace bges::event

#define BGES_EVENT_PUBLISHER(class_name, snake_case)                                                                                       \
	template <typename Source>                                                                                                             \
	class class_name {                                                                                                                     \
	public:                                                                                                                                \
		std::size_t on_##snake_case(std::function<void(Source &, const ::bges::event::class_name &)> listener);                            \
		void remove_##snake_case##_listener(std::size_t listener_id);                                                                      \
                                                                                                                                           \
	protected:                                                                                                                             \
		void fire_##snake_case(Source &source, const ::bges::event::class_name &event);                                                    \
                                                                                                                                           \
	private:                                                                                                                               \
		std::size_t c_max_id{0};                                                                                                           \
		std::unordered_map<std::size_t, std::function<void(Source &, const ::bges::event::class_name &)>> listener_map;                    \
	};                                                                                                                                     \
                                                                                                                                           \
	template <typename Source>                                                                                                             \
	std::size_t class_name<Source>::on_##snake_case(std::function<void(Source &, const ::bges::event::class_name &)> listener) {           \
		listener_map.insert({c_max_id, std::move(listener)});                                                                              \
		return c_max_id++;                                                                                                                 \
	}                                                                                                                                      \
                                                                                                                                           \
	template <typename Source>                                                                                                             \
	void class_name<Source>::remove_##snake_case##_listener(std::size_t listener_id) {                                                     \
		listener_map.erase(listener_id);                                                                                                   \
	}                                                                                                                                      \
                                                                                                                                           \
	template <typename Source>                                                                                                             \
	void class_name<Source>::fire_##snake_case(Source &source, const ::bges::event::class_name &event) {                                   \
		for (auto &fn : listener_map) {                                                                                                    \
			try {                                                                                                                          \
				fn.second(source, event);                                                                                                  \
			}                                                                                                                              \
			catch (const std::exception &e) {                                                                                              \
				/* TODO */                                                                                                                 \
			}                                                                                                                              \
			catch (const std::exception *e) {                                                                                              \
				/* TODO */                                                                                                                 \
				delete e;                                                                                                                  \
			}                                                                                                                              \
			catch (...) {                                                                                                                  \
				/* TODO */                                                                                                                 \
			}                                                                                                                              \
		}                                                                                                                                  \
	}

namespace bges::event_publisher {

BGES_EVENT_PUBLISHER(MouseMove, mouse_move)
BGES_EVENT_PUBLISHER(MousePress, mouse_press)
BGES_EVENT_PUBLISHER(MouseRelease, mouse_release)
BGES_EVENT_PUBLISHER(MouseScroll, mouse_scroll)
BGES_EVENT_PUBLISHER(KeyPress, key_press)
BGES_EVENT_PUBLISHER(KeyRelease, key_release)
BGES_EVENT_PUBLISHER(CloseRequest, close_request)
BGES_EVENT_PUBLISHER(FocusLose, focus_lose)
BGES_EVENT_PUBLISHER(FocusGain, focus_gain)
BGES_EVENT_PUBLISHER(Resize, resize)
BGES_EVENT_PUBLISHER(Click, click)

template <typename T>
class MouseEvents: public MouseMove<T>, public MousePress<T>, public MouseRelease<T>, public MouseScroll<T> { };

template <typename T>
class KeyboardEvents: public KeyPress<T>, public KeyRelease<T> { };

template <typename T>
class WindowEvents: public CloseRequest<T>, public FocusLose<T>, public FocusGain<T>, public Resize<T> { };

} // namespace bges::event_publisher

#undef BGES_EVENT_PUBLISHER

#endif //BGES_BASE_CLASSES_EVENT_PUBLISHERS_HPP
