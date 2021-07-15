#pragma once

#include <chrono>
#include <string>
#include <sstream>

#include "GL/Logger.h"
#include "Types.h"

namespace engine {

	namespace time {
		constexpr u64 SecondNan = 1000000000;
		constexpr u32 SecondMic = 1000000;
		constexpr u16 SecondMil = 1000;
		constexpr u8  Second    = 1;
	}

template<u64 time_unit>
class TimePoint
{
public:
	TimePoint(const char* msg)
		: _switch{ true }
		, _time{ 0 }
		, _name{ msg }
	{
	}

	TimePoint(const TimePoint&) = delete;
	TimePoint(const TimePoint&&) = delete;

public:
	void time_point()
	{
		using namespace std::chrono;
		if ((_switch = !_switch))
		{
			_tp2 = hr_clock::now();
			_time = duration_cast<decltype(_unit)>(_tp2 - _tp1).count();
		}
		else
		{
			_tp1 = hr_clock::now();
		}
	}

	inline const char* get_name() const { return _name; }
	inline u64 get_time() const { return _time; }

	std::string str(const char* timeunit) const
	{
		std::stringstream ss;
		ss << _name << " finished in " << _time << timeunit;
		return ss.str();
	}

public:
	operator const char* () const { return _name; }
	operator u64() const { return _time; }

private:
    using hr_clock = std::chrono::high_resolution_clock;

    hr_clock::time_point _tp1;
    hr_clock::time_point _tp2;

    bool _switch;
	u64 _time;
	const char* _name;
	std::chrono::duration<u64, std::ratio<1, time_unit>> _unit;
};

using TimePointNan = TimePoint<time::SecondNan>;
using TimePointMic = TimePoint<time::SecondMic>;
using TimePointMil = TimePoint<time::SecondMil>;
using TimePointSec = TimePoint<time::Second>;

}
