#ifndef LAYERS_HPP_INCLUDED
#define LAYERS_HPP_INCLUDED

namespace cream {

class Event;

class Layer {
   public:
    Layer() {
    }
    virtual ~Layer() {
    }
    virtual void on_attach() {
    }
    virtual void on_detach() {
    }
    virtual void on_update() {
    }
    virtual void on_event(Event &event) {
    }
    void enable() {
        enabled_ = true;
    }
    void disable() {
        enabled_ = false;
    }
    bool enabled() {
        return enabled_;
    }

   private:
    bool enabled_ = true;
};

}  // namespace cream

#endif
