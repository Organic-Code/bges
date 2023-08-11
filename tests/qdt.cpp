#include <catch2/catch.hpp>

#include <bges/bges.hpp>
#include <bges/colors.hpp>
#include <bges/containers/hbox.hpp>
#include <bges/containers/vbox.hpp>
#include <bges/end_nodes/button.hpp>
#include <bges/scene.hpp>
#include <bges/shapes.hpp>
#include <bges/viewport.hpp>
#include <bges/window.hpp>

#include <atomic>
#include <iostream>
#include <thread>

namespace {
void close_window(bges::Window &window, const bges::event::CloseRequest& /* ignored */) {
	window.close();
}
} // namespace

#pragma clang diagnostic push
#pragma ide diagnostic ignored "altera-unroll-loops"
#pragma ide diagnostic ignored "cppcoreguidelines-avoid-magic-numbers"
#pragma ide diagnostic ignored "concurrency-mt-unsafe"
#pragma ide diagnostic ignored "cert-msc30-c"
SCENARIO("drawing a single rectangle") {

#if BGES_STATIC_BACKEND == 0
#ifdef OS_LINUX
#ifdef DEBUG
	const auto library_file = std::filesystem::current_path() / "libbges_sfml-backenddbg.so";
#elif defined NDEBUG
	const auto library_file = std::filesystem::current_path() / "libbges_sfml-backend.so";
#endif
#elif defined OS_WINDOWS
#ifdef DEBUG
	const auto library_file = std::filesystem::current_path() / "bges_sfml-backenddbg.dll";
#elif defined NDEBUG
	const auto library_file = std::filesystem::current_path() / "bges_sfml-backend.dll";
#endif
#endif
#else
	const auto library_file = "";
#endif
	bges::init(library_file);

	bges::Window window{};
	window.on_close_request(close_window);

	bges::Rectangle rect{};
	rect.rect.x                 = 0;
	rect.rect.y                 = 0;
	rect.rect.width             = 250;
	rect.rect.height            = 400;
	rect.rect.outline_thickness = 0;
	rect.fill_color        = bges::IColor{200, 0, 200};
	REQUIRE(window.open("akekoukou", 1920, 1080));
	window.set_viewport(bges::Viewport{0, 0, 1920, 1080});


	auto scene = bges::Scene::create();

	auto buttons = std::make_shared<bges::container::VBox>();
	buttons->set_margins({5.f, 5.f});
	buttons->set_spacing(10.f);

    auto first_rect = std::make_shared<bges::Rectangle>(rect);
	scene->get_root()->add_child(first_rect);

	rect.rect.x += 15;
	rect.rect.y += 15;
	rect.fill_color = bges::IColor{200, 200, 200};
	rect.rect.outline_thickness = 0;
    scene->get_root()->add_child(std::make_shared<bges::Rectangle>(rect));

    rect.rect.x += 15;
    rect.rect.y += 15;
    rect.fill_color = bges::IColor{200, 0, 0};
    scene->get_root()->add_child(std::make_shared<bges::Rectangle>(rect));

    rect.rect.x += 15;
    rect.rect.y += 15;
    rect.fill_color = bges::IColor{0, 200, 0};
    scene->get_root()->add_child(std::make_shared<bges::Rectangle>(rect));

    rect.rect.x += 15;
    rect.rect.y += 15;
    rect.fill_color = bges::IColor{0, 0, 255};
    auto last_rect = std::make_shared<bges::Rectangle>(rect);
    scene->get_root()->add_child(last_rect);

	auto button = std::make_shared<bges::Button>("Click 1");
	button->on_click([last_rect](bges::Button&  /*btn*/, const bges::event::Click&  /*unused*/) {
		last_rect->to_front();
		last_rect->fill_color = bges::IColor{static_cast<std::uint8_t>(rand() % 255), static_cast<std::uint8_t>(rand() % 255), static_cast<std::uint8_t>(rand() % 255), static_cast<std::uint8_t>(rand() % 200 + 55)};
	});

	auto button2 = std::make_shared<bges::Button>(*button);
	button2->set_text("Click 2");
	auto button3 = std::make_shared<bges::Button>(*button);
	button3->set_text("Click 3");
	auto button4 = std::make_shared<bges::Button>(*button);
	button4->set_text("Click 4");

	buttons->add_child(button);
	buttons->add_child(button4);
	buttons->add_child(button3);
	buttons->add_child(button2);

	button2->to_front();

	scene->get_root()->add_child(buttons);

	srand(std::random_device{}()+time(nullptr));
	for (int count = 0 ; count < 100 ; ++count) {
		if (count % 50 < 25) {
            rect.rect.y += 15;
		} else {
			rect.rect.y -= 15;
		}
		rect.rect.x += 15;
		rect.fill_color = bges::IColor{static_cast<std::uint8_t>(rand() % 255), static_cast<std::uint8_t>(rand() % 255), static_cast<std::uint8_t>(rand() % 255)};
		scene->get_root()->add_child(std::make_shared<bges::Rectangle>(rect));
	}

	window.add_scene(std::move(scene));

	buttons->to_front();
	while (window.is_open()) {

		window.clear();
		window.render();
		std::this_thread::sleep_for(std::chrono::milliseconds(20));
	}
}
#pragma clang diagnostic pop