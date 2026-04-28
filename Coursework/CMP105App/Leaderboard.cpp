#include "Leaderboard.h"

Leaderboard::Leaderboard() {

}

void Leaderboard::loadeFromFile(const std::string& filename) {
	m_score.clear();
	std::ifstream file(filename);

	if (file.is_open())std::cerr << "oops file no find\n";
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