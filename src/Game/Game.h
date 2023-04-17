#pragma once

#include <glm/vec2.hpp>
#include <array>
#include <memory>

class IGameState;

namespace RenderEngine {
	class ShaderProgram;
}

class Game {
public:
	Game(const glm::uvec2& windowSize);
	~Game();

	void render();
	void update(const double delta);
	void setKey(const int key, const int action);
	bool init();
	unsigned int getCurrentWidth() const;
	unsigned int getCurrentHeight() const;
	void startNewLevel(const size_t level);
	void updateViewport();
	void setWindowSize(const glm::uvec2& windowSize);

	bool getClose() { return m_closeWindow; }
	void setClose(bool closeWindow) { m_closeWindow = closeWindow; }

private:
	std::array<bool, 349> m_keys;

	enum class EGameState {
		StartScreen,
		Level,
		Pause
	};

	glm::ivec2 m_windowSize;
	bool m_closeWindow;
	EGameState m_eCurrentGameState;

	std::shared_ptr<IGameState> m_pCurrentGameState;
	std::shared_ptr<RenderEngine::ShaderProgram> m_pSpriteShaderProgram;
};