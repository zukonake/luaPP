/**
 * @file luna/rawStack.hpp
 * @copyright Copyleft zukonake
 * @license Distributed under GNU General Public License Version 3
 */

#pragma once

#include <cstddef>
#include <string>
//
#include <luna/typedef.hpp>

namespace Luna
{

/**
 * Represents the Lua C API stack.
 */
class RawStack
{
public:
	
	/**
	 * Construct a new RawStack, from an existing LuaState.
	 */
	RawStack( LuaState const &luaState ) noexcept;
	
	virtual ~RawStack() = default;
	
	
	
	/**
	 * Loads file.
	 *
	 * The file is loaded and pushed as a function to the stack.
	 *
	 * @param path Path to the file.
	 */
	void loadFile( std::string const &path );
	
	/**
	 * Loads a script as a std::string.
	 *
	 * The script is loaded and pushed as a function to the stack.
	 *
	 * @param value The Lua script to load.
	 */
	void loadString( std::string const &value );
	
	
	
	/**
	 * Loads a file and calls it.
	 *
	 * The file is loaded and pushed as a function to the stack.
	 * The Lua function may return return multiple values,
	 * as defined by the returnNumber, if LuaMultiReturn is used,
	 * all of the return values will be pushed to the stack.
	 * The Lua function may pop multiple values,
	 * as defined by the arguments.
	 *
	 * @param path Path to the file.
	 * @param returnNumber Number of returned values to push to the stack.
	 * @param arguments Number of values to pop from the stack and pass to the function.
	 * @see LuaMultiReturn
	 * @return Returns the number of returnedValues.
	 */
	Size doFile( std::string const &path, Size const &returnNumber = LuaMultiReturn, Size const &arguments = 0 );
	
	/**
	 * Loads a script as a std::string and calls it.
	 *
	 * The string is loaded and pushed as a function to the stack.
	 * The Lua function may return return multiple values,
	 * as defined by the returnNumber, if LuaMultiReturn is used,
	 * all of the return values will be pushed to the stack.
	 * The Lua function may pop multiple values,
	 * as defined by the arguments.
	 *
	 * @param value The Lua script to load.
	 * @param returnNumber Number of returned values to push to the stack.
	 * @param arguments Number of values to pop from the stack and pass to the function.
	 * @see LuaMultiReturn
	 * @return Returns the number of returnedValues.
	 */
	Size doString( std::string const &value, Size const &returnNumber = LuaMultiReturn, Size const &arguments = 0 );
	
	
	
	/**
	 * Calls a function on the stack.
	 *
	 * The Lua function may return return multiple values,
	 * as defined by the returnNumber, if LuaMultiReturn is used,
	 * all of the return values will be pushed to the stack.
	 * The Lua function may pop multiple values,
	 * as defined by the arguments.
	 *
	 * @param index Index to the function.
	 * @param returnNumber Number of returned values to push to the stack.
	 * @param arguments Number of values to pop from the stack and pass to the function.
	 * @see LuaMultiReturn
	 * @return Returns the number of returnedValues.
	 */
	Size call( Index const &index = -1, Size const &returnNumber = LuaMultiReturn, Size const &arguments = 0 );
	
	/**
	 * Calls a meta method of a value.
	 *
	 * The target value is passed as meta method's only argument.
	 * The meta method may return value onto the stack.
	 *
	 * @param index Index of target value.
	 * @param name Name of the meta method to call.
	 */
	void callMetaMethod( Index const &index, std::string const &name );
	
	
	
	//TODO Replace with template< typename T > void pushValue( T const &value ) const;?
	/**
	 * Pushes a nil value onto the stack.
	 */
	void pushNil();
	
	/**
	 * Pushes a boolean onto the stack.
	 */
	void pushBoolean( BooleanValue const &value );
	
	/**
	 * Pushes a number onto the stack.
	 */
	void pushNumber( NumberValue const &value );
	
	/**
	 * Pushes a string onto the stack.
	 */
	void pushString( StringValue const &value );
	
	/**
	 * Pushes a table onto the stack.
	 */
	void pushTable( TableValue const &value );
	
	/**
	 * Pushes a LightUserData onto the stack.
	 */
	void pushLightUserData( LightUserDataValue const &value );
	
	/** 
	 * Pushes a UserData onto the stack.
	 */
	void pushUserData( UserDataValue const &value );
	
	/**
	 * Pushes a function onto the stack.
	 */
	void pushFunction( FunctionValue const &value );
	
	/**
	 * Pushes a function as a closure onto the stack.
	 *
	 * Captured values are popped from the stack.
	 * Values are pushed by their absolute index order.
	 *
	 * @param capture Number of values to capture.
	 */
	void pushClosure( FunctionValue const &closure, CaptureSize const &capture = 0 );
	
	/**
	 * Pushes a thread onto the stack.
	 */
	void pushThread( ThreadValue const &value );
	
	/**
	 * Pushes a library on the stack.
	 *
	 * Library will be pushed as a table.
	 */
	void pushLibrary( Library const &library );
	
	/**
	 * Pushes the global table onto the stack.
	 */
	void pushGlobalTable();
	
	
	
	/**
	 * Creates a new empty meta table in the Lua registry.
	 *
	 * @param name Name to map the meta table.
	 */
	void newMetaTable( std::string const &name );
	
	/**
	 * Creates a new empty table onto the stack.
	 *
	 * Can allocate space for better performance.
	 *
	 * @param arrayLength Hint for number of index mapped elements.
	 * @param mapLength Hint for number of key mapped elements.
	 */
	void newTable( Size const &arrayLength = 0, Size const &mapLength = 0 );
	
	/**
	 * Creates a new memory block onto the stack to use as user data.
	 *
	 * @param size Desired size of the block.
	 * @return The new user data.
	 */
	UserDataValue newUserData( const std::size_t &size );
	
	/**
	 * Creates a new thread on the stack.
	 *
	 * @return The new thread.
	 */
	ThreadValue newThread();
	
	/**
	 * Creates a new reference to a value.
	 *
	 * The target value is popped from the stack.
	 *
	 * @param value Index of the value to create reference to.
	 * @param table Index of the table to create reference in. By default Lua registry.
	 *
	 * @return The new reference.
	 */
	LuaReference newReference( Index const &value, Index const &table = LuaRegistryIndex );
	
	/**
	 * Dereferences a reference.
	 *
	 * The target value is pushed to the stack.
	 *
	 * @param reference Target reference.
	 * @param table Index of the table containing the reference. By default Lua registry.
	 */
	void dereference( LuaReference const &reference, Index const &table = LuaRegistryIndex );
	
	
	
	/**
	 * Register a value as a global.
	 *
	 * The value will be registered to be used by Lua.
	 *
	 * @param index Index to the value to register.
	 * @param name Name to register the value as.
	 */
	void registerValue( Index const &index, std::string const &name );
	
	
	
	//TODO Replace with template< typename T > T toValue( Index const &index = 0 ) const;?
	/**
	 * Get the value of a number on the stack.
	 *
	 * @param index Index to the number.
	 *
	 * @return Value of the number.
	 */
	NumberValue toNumber( Index const &index = -1 ) const;
	
	/**
	 * Get the value of a boolean on the stack.
	 *
	 * @param index Index to the boolean.
	 *
	 * @return Value of the boolean.
	 */
	BooleanValue toBoolean( Index const &index = -1 ) const;
	
	/**
	 * Get the value of a string on the stack.
	 *
	 * @param index Index to the string.
	 *
	 * @return Value of the string.
	 */
	StringValue toString( Index const &index = -1 ) const;
	
	/**
	 * Get the value of a table on the stack.
	 *
	 * @param index Index to the table.
	 *
	 * @return Value of the table.
	 */
	TableValue toTable( Index const &index = -1 ) const;
	
	/**
	 * Get the value of a light user data on the stack.
	 *
	 * @param index Index to the light user data.
	 *
	 * @return Value of the light user data.
	 */
	LightUserDataValue toLightUserData( Index const &index = -1 ) const;
	
	/**
	 * Get the value of a user data on the stack.
	 *
	 * @param index Index to the user data.
	 *
	 * @return Value of the user data.
	 */
	UserDataValue toUserData( Index const &index = -1 ) const;
	
	/**
	 * Get the value of a function on the stack.
	 *
	 * @param index Index to the function.
	 *
	 * @return Value of the function.
	 */
	FunctionValue toFunction( Index const &index = -1 ) const;
	
	/**
	 * Get the value of a thread on the stack.
	 *
	 * @param index Index to the thread.
	 *
	 * @return Value of the thread.
	 */
	ThreadValue toThread( Index const &index = -1 ) const;
	
	
	
	/**
	 * Returns the length of a value (as in '#' operator in Lua).
	 *
	 * @param index Index to the value.
	 *
	 * @return Returned length.
	 */
	Size getLength( Index const &index = -1 ) const;
	
	/**
	 * Returns the Type of a value.
	 *
	 * @param index Index to the value.
	 *
	 * @return Returned Type.
	 */
	Type getType( Index const &index = -1 ) const; 
	
	
	
	/**
	 * Pushes a table's field onto the stack.
	 *
	 * Top value is used as an index or key.
	 * Key is popped.
	 *
	 * @param table Index to the table.
	 *
	 * @return Type of the pushed value.
	 */
	Type getTableField( Index const &table );
	
	/**
	 * Pushes a table's field onto the stack.
	 *
	 * @param table Index to the table.
	 * @param index %Index of the field.
	 *
	 * @return Type of the pushed value.
	 */
	Type getTableField( Index const &table, Index const &index );
	
	/**
	 * Pushes a table's field onto the stack.
	 *
	 * @param table Index to the table.
	 * @param key Key of the field.
	 *
	 * @return Type of the pushed value.
	 */
	Type getTableField( Index const &table, std::string const &key );
	
	
	
	/**
	 * Pushes a table's field onto the stack, without invoking any meta methods.
	 *
	 * Top value is used as an index or key.
	 * Key is popped.
	 *
	 * @param table Index to the table.
	 *
	 * @return Type of the pushed value.
	 */
	Type getRawTableField( Index const &table = -1 );
	
	/**
	 * Pushes a table's field onto the stack, without invoking any meta methods.
	 *
	 * @param table Index to the table.
	 * @param index %Index of the field.
	 *
	 * @return Type of the pushed value.
	 */
	Type getRawTableField( Index const &table, Index const &index );
	
	/**
	 * Pushes a table's field onto the stack, without invoking any meta methods.
	 *
	 * @param table Index to the table.
	 * @param key Key of the field.
	 *
	 * @return Type of the pushed value.
	 */
	Type getRawTableField( Index const &table, std::string const &key );
	
	
	
	//TODO add more variations of getMetaField
	/**
	 * Pushes a value's meta table's field onto the stack.
	 *
	 * @param index Value with the meta table.
	 * @param name Name of the field.
	 *
	 * @return Type of the pushed value.
	 */
	Type getMetaField( Index const &index, std::string const &name );
	
	/**
	 * Pushes a meta table onto the stack.
	 *
	 * @param name Name of the meta table.
	 *
	 * @return Type of the pushed value.
	 */
	Type getMetaTable( std::string const &name );
	
	
	
	/**
	 * Pushes a value associated with user data on the stack.
	 *
	 * @param userData Index to the user data.
	 *
	 * @return Type of the pushed value.
	 */
	Type getUserValue( Index const &userData );

	/**
	 * Pushes a value associated with user data.
	 *
	 * @param userData User data value.
	 *
	 * @return Type of the pushed value.
	 */
	Type getUserValue( UserDataValue const &userData );
	
	/**
	 * Pushes a global variable onto the stack.
	 *
	 * @param name Name of the variable.
	 *
	 * @return Type of the pushed value.
	 */
	Type getGlobal( std::string const &name );
	
	
	
	/**
	 * Sets a table's field.
	 *
	 * Desired value is the value on the top of the stack.
	 * %Index/key of the field is the value one Index below the value.
	 * Value and key will be popped.
	 *
	 * @param table Index to the table.
	 */
	void setTableField( Index const &table );
	
	/**
	 * Sets a table's field.
	 *
	 * @param table Index to the table.
	 * @param index %Index of the field.
	 * @param value Index to the desired value.
	 */
	void setTableField( Index const &table, Index const &index, Index const &value = -1 );
	
	/**
	 * Sets a table's field.
	 *
	 * @param table Index to the table.
	 * @param key Key of the field.
	 * @param value Index to the desired value.
	 */
	void setTableField( Index const &table, std::string const &key, Index const &value = -1 );
	
	
	
	/**
	 * Sets a table's field, without invoking any meta methods.
	 *
	 * Desired value is the value on the top of the stack.
	 * %Index/key of the field is the value one Index below the value.
	 * Value and key will be popped.
	 *
	 * @param table Index to the table.
	 */
	void setRawTableField( Index const &table );
	
	/**
	 * Sets a table's field, without invoking any meta methods.
	 *
	 * @param table Index to the table.
	 * @param index %Index of the field.
	 * @param value Index to the desired value.
	 */
	void setRawTableField( Index const &table, Index const &index, Index const &value = -1 );
	
	/**
	 * Sets a table's field, without invoking any meta methods.
	 *
	 * @param table Index to the table.
	 * @param key Key of the field.
	 * @param value Index to the desired value.
	 */
	void setRawTableField( Index const &table, std::string const &key, Index const &value = -1 );
	
	
	
	/**
	 * Sets a meta table in the Lua register to a given value on the stack.
	 *
	 * @param target Index to the value to set meta table to.
	 * @param metaTable Name of the meta table entry.
	 */
	void setMetaTable( Index const &target, std::string const &metaTable );
	
	/**
	 * Sets a meta table to a given value on the stack.
	 *
	 * @param target Index to the value to set meta table to.
	 * @param metaTable Index to the meta table.
	 */
	void setMetaTable( Index const &target, Index const &metaTable );
	
	
	
	/**
	 * Associates a value to a user data on the stack.
	 *
	 * @param userData Index to the user data.
	 * @param value Index to the value.
	 */
	void setUserValue( Index const &userData, Index const &value );

	/**
	 * Associates a value to a user data.
	 *
	 * @param userData UserData value.
	 * @param value Index to the value.
	 */
	void setUserValue( UserDataValue const &userData, Index const &value );
	
	
	
	/**
	 * Pushes a copy of a given value to the top of the stack.
	 *
	 * @param from Index of the value to copy.
	 */
	void copy( Index const &from  = -1 );
	
	/**
	 * Inserts the value on the top of the stack to given index.
	 *
	 * Elements above, that is elements with higher or equal absolute index,
	 * are given index that is raised by one.
	 *
	 * @param index Index to insert the value into.
	 */
	void insert( Index const &index );
	
	
	
	/**
	 * Removes a value from the stack.
	 *
	 * Elements above, that is elements with higher absolute index,
	 * are given index that is decreased by one.
	 *
	 * @param index Index of the value to remove.
	 */
	void remove( Index const &index );
	
	/**
	 * Removes a value from the stack and replaces it with nil type.
	 *
	 * Elements don't change their index.
	 *
	 * @param index Index of the value to erase.
	 */
	void erase( Index const &index );
	
	/**
	 * Pops a number of values from the top of the stack.
	 *
	 * @param space Number of values to pop.
	 */
	void pop( Size const &space = 1 );
	
	/**
	 * Removes all the elements on the stack.
	 */
	void clear() noexcept;
	
	
	
	/**
	 * Replaces the value with another.
	 *
	 * @param from Value to use.
	 * @param to Value to replace.
	 */
	void replace( Index const &from, Index const &to );
	
	/**
	 * Moves value to another index.
	 *
	 * Target value is replaced with original value.
	 * Original value is removed.
	 * Elements above the target index, but below the original index,
	 * that is elements with higher or equal absolute index and elements
	 * with lower absolute index, are given index that is increased by one.
	 *
	 * @param from Index of the value to move.
	 * @param to Index to move the value to.
	 */
	void move( Index const &from, Index const &to );
	
	/**
	 * Swaps the values.
	 *
	 * @param one Index to the first value.
	 * @param two Index to the second value.
	 */
	void swap( Index const &one, Index const &two );
	
	/**
	 * Iterates over a table.
	 *
	 * Pops the key at the top of the stack to use when iterating.
	 * If table isn't fully iterated, pushes the key to the new
	 * value and the value itself. If the table has been fully iterated,
	 * it pushes no next key or value. %Index/key of type nil
	 * symbolizes beginning of the table.
	 *
	 * @param index Index to the table.
	 *
	 * @return Returns whether the table has not iterated elements left.
	 */
	bool iterate( Index const &index );
	
	
	
	/**
	 * Checks if the given index is valid.
	 */
	bool isValid( Index const &index = -1 ) const noexcept;
	
	
	
	/**
	 * Converts an AbsoluteIndex into Index.
	 */
	Index getRelativeIndex( Index const &index ) const;
	
	/**
	 * Converts an Index into AbsoluteIndex.
	 */
	Index getAbsoluteIndex( Index const &index ) const;
	
	
	
	/**
	 * Returns the number of values on the stack.
	 */
	Size getSize() const noexcept;
	
	/**
	 * Returns the reference to the LuaState.
	 */
	LuaState const &getLuaState() const noexcept;
private:
	void allocate( Size const &size = 1 );
	void validate( Index const &index ) const;
	void validate( Index const &index, Type const &type ) const;
	void checkForError( ReturnCode const &code );
	
	LuaState const &mLuaState;
};

}
