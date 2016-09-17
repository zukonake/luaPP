#ifndef TABLE_HPP
#define TABLE_HPP

#include <unordered_map>
#include <string>
//
#include <typedef.hpp>
#include <element/stackElement.hpp>

namespace LW
{

class LuaState;

class Table : public StackElement
{
public:
	typedef std::unordered_map< std::string, StackElement* > Value;

	Table() = delete;
	Table( LuaState& luaState, const Index& index = -1 );

	virtual ~Table();

	StackElement* operator[]( const std::string& key );
private:
	Value mValue;
};

}

#endif
