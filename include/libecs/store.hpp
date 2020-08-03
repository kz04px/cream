#ifndef LIBECS_STORE_HPP
#define LIBECS_STORE_HPP

#include <cassert>
#include <vector>
#include "entity.hpp"

namespace libecs {

class StoreBase {
   public:
    // virtual ~StoreBase() = default;
    virtual bool has(const Entity e) const = 0;
    virtual void remove(const Entity e) = 0;
    virtual int size() const = 0;
};

template <typename T>
class Store : public StoreBase {
   public:
    // Add an entity to the store
    void add(const Entity e, T t) {
        components_.push_back(std::pair<Entity, T>(e, t));
    }

    // Count the number of entities
    int size() const {
        return components_.size();
    }

    // Remove an entity from the store
    void remove(const Entity e) {
        for (unsigned int i = 0; i < components_.size(); ++i) {
            if (components_[i].first == e) {
                components_[i] = components_[components_.size() - 1];
                components_.pop_back();
                return;
            }
        }
    }

    // Has entity
    bool has(const Entity e) const {
        for (const auto &[ent, cmp] : components_) {
            if (ent == e) {
                return true;
            }
        }
        return false;
    }

    // Get an entity's component
    T &get(const Entity e) {
        assert(has(e));
        for (auto &[ent, cmp] : components_) {
            if (ent == e) {
                return cmp;
            }
        }
    }

    // Data
    std::vector<std::pair<Entity, T>> &data() {
        return components_;
    }

   private:
    std::vector<std::pair<Entity, T>> components_;
};

}  // namespace libecs

#endif
