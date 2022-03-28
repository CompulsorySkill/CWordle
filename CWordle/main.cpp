#include "WordList.h"
#include <fmt/core.h>
#include <fmt/color.h>
#include <iostream>

// define length of word = 5
const int WL_LENGTH = 5;

int main()
{
	fmt::print("Loading words.\n");
	WordList<WL_LENGTH> wlst("5w.csv");
	if (wlst.getCount() > 0) {
		fmt::print("Load words successfully.\n");
	} else {
		fmt::print("Load words failed.\n");
		return 0;
	}
	
	Wordle<WL_LENGTH> wd = wlst.generateWordle();

	char guess[WL_LENGTH + 1]{};
	std::vector<Status> out{};
	int cnt{ 0 };
	while (true) {
		std::cin >> guess;
		bool success = wd.askForGuess(guess, out);
		for (int i = 0; i < WL_LENGTH; i++) {
			switch (out.at(i))
			{
			case Status::CR:
				fmt::print(fg(fmt::color::green), "{}", guess[i]);
				break;
			case Status::WR:
				fmt::print(fg(fmt::color::white), "{}", guess[i]);
				break;
			case Status::PR:
				fmt::print(fg(fmt::color::yellow), "{}", guess[i]);
				break;
			default:
				fmt::print("?");
				break;
			}
		}
		cnt++;
		fmt::print("\n");
		if (success) break;
	}
	
	fmt::print(
		fg(fmt::color::forest_green),
		"You get the answer '{}' in {} tries!",
		wd.getAnswer(),
		cnt
	);

	return 0;
}
