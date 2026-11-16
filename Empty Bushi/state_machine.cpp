#include"state_machine.h"

StateMachine::StateMachine() = default;
StateMachine::~StateMachine() = default;

void StateMachine::on_update(float delta)
{
	if (!current_state) return;       //检测是否存在合法状态

	if (need_init)                    //初始化状态
	{
		current_state->on_enter();
		need_init = false;
	}

	current_state->on_update(delta);
}

void StateMachine::set_entry(const std::string& id)
{
	auto it = state_pool.find(id);

	if (it == state_pool.end())
	{
		current_state = nullptr;
		return;
	}

	current_state = it->second.get();
	need_init = true;
}

void StateMachine::switch_to(const std::string& id)
{
	auto it = state_pool.find(id);

	// 目标状态不存在，不进行切换
	if (it == state_pool.end()) return;

	StateNode* next_state = it->second.get();

	// 已经是当前状态，不重复进入
	if (current_state == next_state) return;

	if (current_state)
		current_state->on_exit();

	current_state = next_state;
	current_state->on_enter();

	need_init = false;
}

void StateMachine::register_state(
	const std::string& id,
	std::unique_ptr<StateNode> state_node)
{
	state_pool.emplace(id, std::move(state_node));
}