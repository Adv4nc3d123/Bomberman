#pragma once
#include "Singleton.h"

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Rect;

namespace dae
{
	class Texture2D;
	class Renderer final : public Singleton<Renderer>
	{
		SDL_Renderer* m_Renderer = nullptr;

	public:
		void Init(SDL_Window* window);
		void Render();
		void Destroy();

		//void RenderTexture(const Texture2D& texture, float x, float y) const;
		//void RenderTexture(const Texture2D& texture, float x, float y, float width, float height) const;
		void RenderTexture(const Texture2D& texture, float x, float y, float angle = 0.0f) const;
		void RenderTexture(const Texture2D& texture, float x, float y, const SDL_Rect& clip, float angle = 0.0f) const;
		void RenderTexture(const Texture2D& texture, float x, float y, float width, float height, float angle = 0.0f) const;
		void RenderTexture(const Texture2D& texture, float x, float y, float width, float height, const SDL_Rect& clip, float angle = 0.0f) const;


		SDL_Renderer* GetSDLRenderer() const { return m_Renderer; }
	};
}

