#ifndef LAYER_MANAGER_HPP_INCLUDED
#define LAYER_MANAGER_HPP_INCLUDED

#include "layer.hpp"
#include "../events/event.hpp"

namespace cream
{
    class LayerManager
    {
        public:
            LayerManager();
            ~LayerManager();
            void push_layer(Layer *layer);
            void push_overlay(Layer *overlay);
            void pop_layer(Layer *layer);
            void pop_overlay(Layer *layer);
            // Events
            void pass_event(Event &event);
            // Update
            void update();
        private:
            std::vector<Layer*> layers_;
    };
}

#endif
