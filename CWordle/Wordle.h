#pragma once
#include <vector>
#include <string>

enum class Status {
	CR,	//��ȷ
	WR,	//����
	PR	//λ�ô���
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
	bool askForGuess(char* input, std::vector<Status> &out) const
	{
		out.clear();
		bool success = true;
		for (int i = 0; i < N; i++) {
			Status res = askForStatus(i, input[i]);
			out.push_back(res);
			if (success && res != Status::CR) {
				success = false;
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
	Status askForStatus(size_t pos, char input) const
	{
		if (answer[pos] == input) {
			return Status::CR;
		}
		else
		{
			for (int i = 0; i < N; i++) {
				if (answer[i] == input) {
					return Status::PR;
				}
			}
			return Status::WR;
		}
	}
private:
	char answer[N];
};