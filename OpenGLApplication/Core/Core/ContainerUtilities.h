#pragma once



namespace Algorithms
{
	namespace Vector
	{
		template<class C, class T>
		auto contains(const C& container, const T& value)
			-> decltype(std::end(container), true)
		{
			return std::end(container) != std::find(std::begin(container), std::end(container), value);
		}
	}

	namespace Map
	{
		template<class C, class T>
		auto contains(const C& container, const T& value)
			-> decltype(std::end(container), true)
		{
			return container.find(value) != container.end();
		}
	}
}