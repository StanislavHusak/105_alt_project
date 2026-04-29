#include "Leaderboard.h"


Leaderboard::Leaderboard() {

}

void Leaderboard::loadeFromFile(const std::string& filename) {
	m_score.clear();
	std::ifstream file(filename);

	if (!file.is_open())std::cerr << "oops file no find\n";
	float time;
	while (file >> time)
	{
		m_score.push_back(time);
	}
	file.close();

	std::sort(m_score.begin(), m_score.end());
	
}


void Leaderboard::saveToFile(const std::string& filename) {
	std::ofstream file(filename);

	for (auto& score : m_score) {
		file << score << "\n";
	}

	file.close();
}

void Leaderboard::addScore(float time) {
	m_score.push_back(time);
	std::sort(m_score.begin(), m_score.end());
	
	if (m_score.size() > 6) {
		m_score.resize(6);
	}
}

std::string Leaderboard::makeLeaderboard(const std::string& filename) {
	loadeFromFile(filename);
	std::string text = "   LEADERBOARD   \n";
	std::string place;
	int i = 1;
	for (auto& score : m_score) {
		place = std::to_string(i);
		text += place + ". " + formattedTime(score) + "\n";
		i++;
	}
	std::cerr << text;
	return text;
}

std::string Leaderboard::formattedTime(float& time) {
	int totalSeconds = (int)time;
	int minutes = totalSeconds / 60;
	int seconds = totalSeconds % 60;
	int milliseconds = (int)((time - totalSeconds) * 100);
	std::string text = std::to_string(minutes) + ":" + (seconds < 10 ? "0" : "") + std::to_string(seconds) + ":" + (milliseconds < 10 ? "0" : "") + std::to_string(milliseconds);
	return text;
}