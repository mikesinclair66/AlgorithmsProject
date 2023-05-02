#pragma once
#ifndef COMMANDPROCESSOR_HPP
#define COMMANDPROCESSOR_HPP

#include "SysAdmin.hpp"

class CommandProcessor : public ReadMessenger {
public:
	CommandProcessor(string);

	enum class Command {
		WORLD,
		IMPORT,
		QUIT,
		DEBUG,
		WHAT_IS_AT,
		WHAT_IS,
		WHAT_IS_IN
	};
};

#endif