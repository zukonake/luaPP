# Luna API
Simple library that wraps the Lua C API into C++, ensuring proper exception system and memory management, the library is designed for reading Lua files with ease and without memory leaks.
# Installing
`make` to compile
`sudo make install` to install the library in /lib/
# Example usage
```cpp
Stack stack;
stack.doFile( "example.lua" );
stack.loadGlobal( "luna" );
std::cout << **stack.at< Number >( "var" ) << std::endl;
std::cout << **stack.at< String >( 2 ) << std::endl;
stack.pushNil();
```
# License
Luna API is distributed under GNU General Public License Version 3
