#include "state_machine.hpp"

using StateRef = std::unique_ptr<State>;

StateMachine::StateMachine()
{  
}
StateMachine::~StateMachine()
{   
}
void StateMachine::add_state(StateRef state, bool replace)
{   
    if(replace and !m_states.empty())
        m_states.pop();
    m_states.push(std::move(state));
}
void StateMachine::remove_state()
{
    if(m_states.empty())
        return;
    m_states.pop();
}
StateRef& StateMachine::get_active_state()
{
    return m_states.top();
}
bool StateMachine::empty()
{
    return m_states.empty();
    
}
