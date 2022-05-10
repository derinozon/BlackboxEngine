#pragma once

#include <vector>

namespace Blackbox {
	class Action {
		public:
			Action () {}

			void Invoke () {
				for (int i = 0; i < functions.size(); i++) {
					functions[i]();
				}
			}

			void Add (void (*func)(void)) {
				functions.push_back(func);
			}

			void operator+=(void (*func)(void)) {
				Add(func);
			}
		private:
			std::vector< void (*)(void) > functions;
	};
}