#pragma once

#include <string>

using namespace std;

namespace finalProject {
	class GISRecord {
		string* params;

	public:
		enum class Command {
			WORLD,
			IMPORT,
			QUIT,
			DEBUG,
			WHAT_IS_AT,
			WHAT_IS,
			WHAT_IS_IN
		};

		GISRecord(Command);
		void setParams(string*);

	private:
		Command command;
	};
}