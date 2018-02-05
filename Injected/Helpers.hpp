//Fuck boost!!!

#pragma once
#include <sstream>
#include <vector>
#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>
#include <iterator>
using string = std::string;

template<typename K, typename V>
inline auto display(const K key, const V value)
{
	texts.push_back(typetostring(key, value));
}

template<typename I>
auto tohex(I i)
{
	std::stringstream stream;
	stream << std::hex << i;
	string result(stream.str());
	return result;
}

auto tofloat(const string& f) { return (float)std::atof(f.c_str()); }
auto toint(const string& f) { return std::stoi(f.c_str()); }

template<typename Cont, typename Pred>
std::vector<typename Cont::value_type> find_all(Cont& c, Pred p)
{
	std::vector<typename Cont::value_type> res;
	for (auto* x : c)
		if (p(x)) res.push_back(x);
	return res;
}

template<typename Cont, typename Pred>
typename Cont::value_type min_by(Cont& c, Pred p)
{
	if (c.size() == 0)
		return nullptr;
	return *std::min_element(c.begin(), c.end(), p);
}

template<typename Cont, typename Pred>
typename Cont::value_type max_by(Cont c, Pred p)
{
	if (c.size() == 0)
		return nullptr;
	return *std::max_element(c.begin(), c.end(), p);
}

inline const char * const BoolToString(bool b)
{
	return b ? "true" : "false";
}

template<typename ... Args>
string string_format(const string& format, Args ... args)
{
	size_t size = snprintf(nullptr, 0, format.c_str(), args ...) + 1; // Extra space for '\0'
	std::unique_ptr<char[]> buf(new char[size]);
	snprintf(buf.get(), size, format.c_str(), args ...);
	return string(buf.get(), buf.get() + size - 1); // We don't want the '\0' inside
}

// trim helpers
// trim from start (in place)
inline auto ltrim(string &s)
{
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {return !std::isspace(ch); }));
}

// trim from end (in place)
inline void rtrim(string &s)
{
	s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {	return !std::isspace(ch); }).base(), s.end());
}

// trim from both ends (in place)
inline void trim(string &s)
{
	ltrim(s);
	rtrim(s);
}

// trim from start (copying)
inline string ltrimmed(string s)
{
	ltrim(s);
	return s;
}

// trim from end (copying)
inline string rtrimmed(string s)
{
	rtrim(s);
	return s;
}

// trim from both ends (copying)
inline string trimmed(string s)
{
	trim(s);
	return s;
}

inline auto to_lower(string &s)
{
	std::transform(s.begin(), s.end(), s.begin(), ::tolower);
}

template<typename Out>
auto split(const string &s, char delim, Out result)
{
	std::stringstream ss;
	ss.str(s);
	string item;
	while (std::getline(ss, item, delim))
	{
		*(result++) = item;
	}
}

auto split(const string &s, char delim)
{
	std::vector<string> elems;
	split(s, delim, std::back_inserter(elems));
	return elems;
}

template<typename K, typename V>
inline auto typetostring(const K key, const V value)
{
	std::ostringstream sskey;
	std::ostringstream ssvalue;
	sskey << key;
	ssvalue << value;
	return sskey.str() + " = " + ssvalue.str();
}

inline auto strcontains(const string& container, const string& tofind)
{
	return container.find(tofind) != string::npos;
}

//auto str2ll(int &i, char const *s, int base = 0)
//{
//	char *end;
//	errno = 0;
//	auto l = strtoll(s, &end, 10);
//
//	if (errno == ERANGE)
//		return false;
//
//	if (*s == '\0' || *end != '\0')
//		return false;
//
//	i = l;
//	return true;
//}