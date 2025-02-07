#include <iostream>
#include <variant>

template<typename FsmType, typename... States>
class fsm {
private:
    using state_variant_t = std::variant<States...>;
    state_variant_t _state;
public:
    template<typename Event>
    void dispatch(Event&& event) {
        auto& child = static_cast<FsmType&>(*this);
        const auto& visitor =
                [&](auto& state) -> std::optional<state_variant_t> {
            return child.on_event(state, std::forward(event));
        };
        const auto& next_state = std::visit(visitor, _state);
        if (next_state.has_value()) {
            _state = next_state.value();
        }
    }
};

[[gnu::weak]] int main() { return 0; }
