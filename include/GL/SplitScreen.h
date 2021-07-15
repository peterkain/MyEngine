#pragma once

#include "GL/Window.h"
#include "GL/Renderer.h"
#include "GL/Camera.h"
#include "Types.h"
#include "ResourceManager.h"

#include <map>
#include <vector>
#include <memory>
#include <utility>
#include <GL/glew.h>

namespace engine {

enum class SplitType
{
    Horizontal,
    Vertical
};

template<u8 n>
class SplitScreen
{
public:
    SplitScreen(Window* const window, Renderer* const renderer, SplitType stype);

    void add(u8 section, const char* lookupstr, CameraType type = CameraType::Orthographic);
    void remove(u8 section);
    void resize();
    void render();

	Camera* const camera(u8 section) { return _cameras[section].first.get(); }

	void on_mousescroll(std::function<void(double, double)> f) {
		_window->on_mousescroll(f);
	}

    inline void reset()
    {
        _sections.clear();
        _data.clear();
		_cameras.clear();
    }
private:
	void init(u8 n, bool reset = true);
	void calculate_cameras(u8 section, CameraType type);

private:
    std::map<u8, std::vector<StoredRender*>> _data;
	std::map<u8, std::pair<std::shared_ptr<Camera>, CameraType>> _cameras;

    Window* _window;
	Renderer* _renderer;
    std::vector<glm::vec4> _sections;
    SplitType _stype;
    u8 _n;
};


template<u8 n>
SplitScreen<n>::SplitScreen(Window* const window, Renderer* const renderer, SplitType stype)
    : _window {window}
	, _renderer {renderer}
    , _stype {stype}
    , _n {n}
{
    init(n);
	_window->on_resize([&]
		{
			resize();
		}
	);
}


template <u8 n>
void SplitScreen<n>::init(u8 n, bool reset)
{
	_n = n;
	if (reset) this->reset();

	_sections.resize(n);

	float area{ 1.f / n };
	if (_stype == SplitType::Horizontal)
	{
		float height{ _window->height() * area };
		for (u8 i{ n }; i != 0; i--)
		{
			_sections[n - (i - 1) - 1] = glm::vec4{ 0.f, height * (i - 1), static_cast<float>(_window->width()), height };
		}
	}
	else if (_stype == SplitType::Vertical)
	{
		float width{ _window->width() * area };
		for (u8 i{ 0 }; i != n; i++)
		{
			_sections[i] = glm::vec4{ width * (i - 1) + width, 0.f, width, static_cast<float>(_window->height()) };
		}
	}
}


template <u8 n>
void SplitScreen<n>::calculate_cameras(u8 section, CameraType type)
{
	glm::vec4 area{ _sections[section] };

	auto& camera{ _cameras[section] };
	camera.first = std::make_shared<Camera>();
	if (type == CameraType::Orthographic)
		if (_stype == SplitType::Horizontal)
			camera.first->setup(area.x, 0.f, area.z, area.w, -1.f, 1.f, type);
		else if (_stype == SplitType::Vertical)
			camera.first->setup(0.f, area.y, area.z, area.w, -1.f, 1.f, type);
	else if (type == CameraType::Perspective)
		camera.first->setup(area.x, area.y, area.z, area.w, .1f, 100.f, type);

	camera.second = type;
}


template <u8 n>
void SplitScreen<n>::add(u8 section, const char* lookupstr, CameraType type)
{
    if (section < _n)
    {
        remove(section);
		_data[section] = RM::stored_renders(lookupstr);
		calculate_cameras(section, type);
    }
}

template <u8 n>
void SplitScreen<n>::remove(u8 section)
{
	if (_data.find(section) != _data.end())
	{
		_data.erase(section);
		_cameras.erase(section);
	}
}

template <u8 n>
void SplitScreen<n>::resize()
{
    init(n, false);
	for (u8 i{}; i != n; i++)
	{
		calculate_cameras(i, _cameras[i].second);
	}
}

template <u8 n>
void SplitScreen<n>::render()
{
	for (u8 i{}; i != n; ++i)
    {
		glm::vec4 section{ _sections[i] };
        _window->viewport(static_cast<GLint>(section.x), static_cast<GLint>(section.y),
			static_cast<GLsizei>(section.z), static_cast<GLsizei>(section.w));
		if (_data.find(i) != _data.end())
		{
			for (const auto& e : _data[i])
				e->render(*_renderer, *_cameras[i].first);
		}
    }
}

}