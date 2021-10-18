#pragma once

class Score
{
public:
	Score() : currentScore(0), highScore(0)
	{}
	void AddScore(int score) 
	{
		currentScore += score;

		if(currentScore > highScore)
		{
			highScore += score; 
		}
	}
	int GetCurrentScore() const { return currentScore; }
	int GetHighScore() const { return highScore; }
	void ResetScore()  { currentScore = 0; }
private:
	int currentScore;
	int highScore;
};
