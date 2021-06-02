#ifndef CREAM_LAYERS_HPP
#define CREAM_LAYERS_HPP

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
    virtual void on_event(Event &) {
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
