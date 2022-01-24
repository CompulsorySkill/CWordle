#include "WordList.h"
#include <fmt/core.h>
#include <fmt/color.h>
#include <iostream>

int main()
{
	fmt::print("Loading words.\n");
	WordList<5> wl("5w.csv");
	if (wl.getCount() > 0) {
		fmt::print("Load words successfully.\n");
	} else {
		fmt::print("Load words failed.\n");
		return 0;
	}
	
	Wordle<5> wd = wl.generateWordle();

	char guess[6]{};
	std::vector<Status> out;
	while (true) {
		std::cin >> guess;
		bool success = wd.askForGuess(guess, out);
		for (int i = 0; i < 5; i++) {
			switch (out.at(i))
			{
			case Status::CR:
				fmt::print(fg(fmt::color::green), "{}", guess[i]);
				break;
			case Status::WR:
				fmt::print(fg(fmt::color::white_smoke), "{}", guess[i]);
				break;
			case Status::PR:
				fmt::print(fg(fmt::color::yellow), "{}", guess[i]);
				break;
			default:
				break;
			}
		}
		fmt::print("\n");
		if (success) break;
	}
	
	fmt::print(fg(fmt::color::crimson), wd.getAnswer());

	return 0;
}