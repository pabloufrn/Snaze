#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include <memory>
#include <stack>

#include "state.hpp"

using StateRef = std::unique_ptr<State>;

class StateMachine
{
    public: 
        
        StateMachine();
        ~StateMachine();
        
        void add_state(StateRef state, bool replace = true);
        void remove_state();
        
        bool empty();
        
        StateRef& get_active_state();
        
    private:
        std::stack<StateRef> m_states;
        
};


#endif
