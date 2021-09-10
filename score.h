class Score
{
public:
	void AddScore(int score) { currentScore += score; highScore += score; }
	int GetCurrentScore() const { return currentScore; }
	int GetHighScore() const { return highScore; }
	static Score& GetReference() { return score; }
private:
	int currentScore;
	int highScore;
	static Score score;
private:
	Score() : currentScore(0), highScore(0)
	{}
};

Score Score::score;
