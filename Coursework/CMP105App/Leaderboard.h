#pragma once

#include <algorithm>
#include <fstream>
#include <vector>
#include <iostream>

class Leaderboard
{
public:
	Leaderboard();
	void loadeFromFile(const std::string& filename);
	void saveToFile(const std::string& filename);
	void addScore(float time);

	std::vector<float>& getScore() { return m_score; };
private:
	std::vector<float> m_score;
};

