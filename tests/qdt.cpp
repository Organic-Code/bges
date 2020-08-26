#include <catch2/catch.hpp>

#include <bges/window.hpp>
#include <bges/shapes.hpp>
#include <bges/colors.hpp>

#include <iostream>
#include <thread>
#include <atomic>

SCENARIO("drawing a single rectangle") {
    bges::Window window{};
	window.on_close_request([](auto&){
		return true;
	});

    bges::Rectangle rect{};
	rect.x = 0;
	rect.y = 0;
	rect.width = 250;
	rect.height = 400;
	rect.outline_thickness = 10;
	rect.fill_color = bges::IColor{127, 0, 255};
	rect.outline_color = bges::IColor{0, 255, 127};
	REQUIRE(window.open("akekoukou", 1920, 1080));
	window.set_viewport(bges::Viewport{-15, -15, 1920-15, 1080-15});

	while (window.is_open()) {
		window.clear();
		window.draw(rect);
		window.render();
		std::this_thread::sleep_for(std::chrono::milliseconds(20));
	}
}