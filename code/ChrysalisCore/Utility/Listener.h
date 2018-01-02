#pragma once

namespace Chrysalis
{
/**
Implements a simple listener mechanic.

\tparam	T Generic type parameter.
**/
template<typename T>
struct TListener
{
	void AddEventListener(T* pListener)
	{
		assert(pListener);
		stl::push_back_unique(m_listenersList, pListener);
	}

	void RemoveEventListener(T* pListener)
	{
		assert(pListener);
		m_listenersList.remove(pListener);
	}

	std::list<T*> GetListeners() { return m_listenersList; }

private:
	std::list<T*> m_listenersList;
};
}
