#pragma once
#ifndef STORAGE_HPP
#define STORAGE_HPP

#include "SystemManager.hpp"

class Storage : public WriteMessenger {
public:
	Storage(string);
};

#endif