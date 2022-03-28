#pragma once
#include <vector>
#include <string>

enum class Status {
	CR,	//[CoRrect] true letter
	WR,	//[WRong]	false letter
	PR	//[Position wRong]	false letter but exists in word
};

template<int N>
class Wordle {
public:
	Wordle(char* answer)
	{
		for (int i = 0; i < N; i++) {
			this->answer[i] = answer[i];
		}
	}
	bool askForGuess(const char *input, std::vector<Status> &out) const
	{
		out.clear();
		bool success = true;

		for (int i = 0; i < N; i++) {
			if (input[i] == answer[i]) {
				out.push_back(Status::CR);
				out[i] = Status::CR;
			} else {
				bool set = false;
				for (int j = 0; j < N; j++) {
					if (j != i && answer[j] == input[i]) {
						out.push_back(Status::PR);
						set = true;
						break;
					}
				}
				if (!set) {
					out.push_back(Status::WR);
				}
				if (success) {
					success = false;
				}
			}
		}

		for (int i = 0; i < N; i++) {
			if (out.at(i) == Status::PR) {
				bool realPR = false;
				for (int j = 0; j < N; j++) {
					if (answer[j] == input[i] && out.at(j) != Status::CR) {
						realPR = true;
					}
				}
				if (!realPR) {
					out[i] = Status::WR;
				}
			}
		}

		return success;
	}
	std::string getAnswer() const
	{
		return std::string(answer).substr(0, N);
	}
	const char* getCStrAnswer() const
	{
		return answer;
	}
protected:

private:
	char answer[N];
};
