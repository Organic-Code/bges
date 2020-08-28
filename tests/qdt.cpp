#include <catch2/catch.hpp>

#include <bges/colors.hpp>
#include <bges/shapes.hpp>
#include <bges/viewport.hpp>
#include <bges/window.hpp>
#include <bges/scene.hpp>
#include <bges/end_nodes/button.hpp>

#include <atomic>
#include <iostream>
#include <thread>

namespace {
void close_window(bges::Window &window, const bges::event::CloseRequest&) {
	window.close();
}
} // namespace

SCENARIO("drawing a single rectangle") {
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

    auto scene = std::make_shared<bges::Scene>();
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

	auto button = std::make_shared<bges::Button>();
	button->on_click([&](bges::Button& btn, const bges::event::Click& a) {
		last_rect->to_front();
		last_rect->fill_color = bges::IColor{static_cast<std::uint8_t>(rand() % 255), static_cast<std::uint8_t>(rand() % 255), static_cast<std::uint8_t>(rand() % 255), static_cast<std::uint8_t>(rand() % 200 + 55)};
	});
	scene->get_root()->add_child(std::move(button));


	srand(time(0));
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


//	scene->bring_to_front(first_rect.get());
//	scene->bring_to_back(last_rect.get());


	window.add_scene(std::move(scene));

	while (window.is_open()) {

		window.clear();
		window.render();
		std::this_thread::sleep_for(std::chrono::milliseconds(20));
	}
}