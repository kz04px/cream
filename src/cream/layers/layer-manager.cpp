#include "layer-manager.hpp"

namespace cream {

LayerManager::LayerManager() {
}

LayerManager::~LayerManager() {
    for (auto &layer : layers_) {
        delete layer;
    }
}

void LayerManager::push_layer(Layer *layer) {
    layers_.push_back(layer);
}

void LayerManager::push_overlay(Layer *overlay) {
}

void LayerManager::pop_layer(Layer *layer) {
    auto it = std::find(layers_.begin(), layers_.end(), layer);
    if (it != layers_.end()) {
        layers_.erase(it);
    }
}

void LayerManager::pop_overlay(Layer *layer) {
}

void LayerManager::pass_event(Event &event) {
    for (auto &layer : layers_) {
        layer->on_event(event);

        if (event.handled_) {
            break;
        }
    }
}

void LayerManager::update() {
    for (auto &layer : layers_) {
        layer->on_update();
    }
}

}  // namespace cream
