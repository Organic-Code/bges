#ifndef BGES_BASE_CLASSES_EVENT_PUBLISHERS_HPP
#define BGES_BASE_CLASSES_EVENT_PUBLISHERS_HPP

#include <cassert>
#include <functional>
#include <unordered_map>

#include <bges/details/export.hpp>

/**
 * Events classes that contain events data when such events are fired.
 */
#include <bges/events.hpp>

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
		std::size_t m_max_id{0};                                                                                                           \
		std::unordered_map<std::size_t, std::function<void(Source &, const ::bges::event::class_name &)>> m_listener_map;                  \
	};                                                                                                                                     \
                                                                                                                                           \
	template <typename Source>                                                                                                             \
	std::size_t class_name<Source>::on_##snake_case(std::function<void(Source &, const ::bges::event::class_name &)> listener) {           \
		m_listener_map.insert({m_max_id, std::move(listener)});                                                                            \
		return m_max_id++;                                                                                                                 \
	}                                                                                                                                      \
                                                                                                                                           \
	template <typename Source>                                                                                                             \
	void class_name<Source>::remove_##snake_case##_listener(std::size_t listener_id) {                                                     \
		m_listener_map.erase(listener_id);                                                                                                 \
	}                                                                                                                                      \
                                                                                                                                           \
	template <typename Source>                                                                                                             \
	void class_name<Source>::fire_##snake_case(Source &source, const ::bges::event::class_name &event) {                                   \
		for (auto &fnct : m_listener_map) {                                                                                                \
			try {                                                                                                                          \
				fnct.second(source, event);                                                                                                \
			}                                                                                                                              \
			catch (const std::exception &e) {                                                                                              \
				/* TODO */                                                                                                                 \
                assert(false && "exception caught during event processing");                                                               \
			}                                                                                                                              \
			catch (const std::exception *e) { /* NOLINT(*-throw-by-value-catch-by-reference) */                                            \
				/* TODO */                                                                                                                 \
				delete e; /* NOLINT(*-owning-memory) */                                                                                    \
                assert(false && "exception caught during event processing");                                                               \
			}                                                                                                                              \
			catch (...) {                                                                                                                  \
				/* TODO */                                                                                                                 \
                assert(false && "exception caught during event processing");                                                               \
			}                                                                                                                              \
			if (event.is_consumed()) {                                                                                                     \
				break;                                                                                                                     \
			}                                                                                                                              \
		}                                                                                                                                  \
	}

namespace bges::event_publisher {

BGES_EVENT_PUBLISHER(MouseMove, mouse_move)                      // Mouse being moved around
BGES_EVENT_PUBLISHER(MousePress, mouse_press)                    // Mouse button being pressed (left, right, middle, others)
template <typename Source>
class MouseRelease {
public:
	std::size_t on_mouse_release(std::function<void(Source &, const ::bges::event::MouseRelease &)> listener);
	void remove_mouse_release_listener(std::size_t listener_id);

protected:
	void fire_mouse_release(Source &source, const ::bges::event::MouseRelease &event);

private:
	std::size_t m_max_id{0};
	std::unordered_map<std::size_t, std::function<void(Source &, const ::bges::event::MouseRelease &)>> m_listener_map;
};
template <typename Source>
std::size_t MouseRelease<Source>::on_mouse_release(std::function<void(Source &, const ::bges::event::MouseRelease &)> listener) {
	m_listener_map.insert({m_max_id, std::move(listener)});
	return m_max_id++;
}
template <typename Source>
void MouseRelease<Source>::remove_mouse_release_listener(std::size_t listener_id) {
	m_listener_map.erase(listener_id);
}
template <typename Source>
void MouseRelease<Source>::fire_mouse_release(Source &source, const ::bges::event::MouseRelease &event) {
	for (auto &fnct : m_listener_map) {
		try {
			fnct.second(source, event);
		}
		catch (const std::exception &e) {
			(static_cast<bool>(false && "exception caught during event processing") ?
			   void(0) :
			   __assert_fail("false && \"exception caught during event processing\"", "_file_name_", 70, "_function_name_"));
		}
		catch (const std::exception *e) {
			delete e;
			(static_cast<bool>(false && "exception caught during event processing") ?
			   void(0) :
			   __assert_fail("false && \"exception caught during event processing\"", "_file_name_", 70, "_function_name_"));
		}
		catch (...) {
			(static_cast<bool>(false && "exception caught during event processing") ?
			   void(0) :
			   __assert_fail("false && \"exception caught during event processing\"", "_file_name_", 70, "_function_name_"));
		}
		if (event.is_consumed()) {
			break;
		}
	}
}                // Mouse button being released
BGES_EVENT_PUBLISHER(MouseScroll, mouse_scroll)                  // Mouse wheel scrolled
BGES_EVENT_PUBLISHER(MouseExit, mouse_exit)                      // Mouse exited Window or GUI element
BGES_EVENT_PUBLISHER(MouseEnter, mouse_enter)                    // Mouse entered Window or GUI element
BGES_EVENT_PUBLISHER(KeyPress, key_press)                        // Keyboard pressed
BGES_EVENT_PUBLISHER(KeyRelease, key_release)                    // Keyboard released
BGES_EVENT_PUBLISHER(CloseRequest, close_request)                // Window close request (eg : click on the top right cross)
BGES_EVENT_PUBLISHER(FocusLose, focus_lose)                      // Window or GUI element focus lost
BGES_EVENT_PUBLISHER(FocusGain, focus_gain)                      // Window or GUI element focus gained
BGES_EVENT_PUBLISHER(Resize, resize)                             // Window resized
BGES_EVENT_PUBLISHER(Click, click)                               // "Click" event (Mouse press + mouse release on the same gui element)
BGES_EVENT_PUBLISHER(DataUpdate, data_update)                    // GUI data element updated (eg : text or color being changed. For text : called when action is completed [eg : text field focus is lost after typing])
BGES_EVENT_PUBLISHER(AtomicTextUpdate, atomic_text_update)       // GUI text updated, called for every letter

template <typename Source>
struct MouseEvents: MouseMove<Source>, MousePress<Source>, MouseRelease<Source>, MouseScroll<Source>, MouseEnter<Source>, MouseExit<Source> { };

template <typename Source>
struct KeyboardEvents: KeyPress<Source>, KeyRelease<Source> { };

template <typename Source>
struct WindowEvents: CloseRequest<Source>, FocusLose<Source>, FocusGain<Source>, Resize<Source> { };

} // namespace bges::event_publisher

#undef BGES_EVENT_PUBLISHER

#endif //BGES_BASE_CLASSES_EVENT_PUBLISHERS_HPP
