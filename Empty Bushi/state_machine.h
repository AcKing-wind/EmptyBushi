#pragma once

#include"state_node.h"

#include<string>
#include<unordered_map>
#include<memory>

class StateMachine
{
public:
	StateMachine();
	~StateMachine();

	void on_update(float delta);

	void set_entry(const std::string& id);
	void switch_to(const std::string& id);
	void register_state(
		const std::string& id,
	    std::unique_ptr<StateNode> state_node
	);

private:
	bool need_init = true;
	StateNode* current_state = nullptr;
	std::unordered_map<std::string, std::unique_ptr<StateNode>> state_pool;


};