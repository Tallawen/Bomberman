#include "UI.h"

UI::UI() {
	queue.clear();
}

void UI::show(float dt) {
	FOREACH(queue, it) {
		(*it)->update(dt);
		(*it)->draw(dt);
	}
}

void UI::add(UIElement *element) {
	if(element == nullptr) return;

	queue.push_back(element);
}

UIElement* UI::getLast() {
	if(queue.empty()) return nullptr;

  return queue.back();
}
