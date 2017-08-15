#pragma once

template<typename T>
class singleton_t
{
private:
	static T m_instance;             // ¨º¦Ì¨¤y

public:
	static T* instance();

private:
	singleton_t();
	singleton_t(const singleton_t &);
	singleton_t& operator=(const singleton_t &);
};

template<typename T>
T singleton_t<T>::m_instance;

template<typename T>
singleton_t<T>::singleton_t()
{
}

template<typename T>
T* singleton_t<T>::instance()
{
	return &m_instance;
}
