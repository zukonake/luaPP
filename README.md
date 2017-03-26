# Luna API
Simple library that wraps the Lua C API into C++, ensuring proper exception system and memory management, the library is designed for reading Lua files with ease and without memory leaks.
# Installing
`make` to compile
`sudo make install` to install the library in /lib/
# Example usage
```cpp
Luna::Stack stack;
stack.doFile( "example.lua" );
Luna::Table luna = stack.loadGlobal( "luna" );               //get local variable to table
std::cout << stack.at< Luna::String >( "var" ) << std::endl; //get global from stack
std::cout << luna.at< Luna::Number >( "var" ) << std::endl;  //get variable from luna table
std::cout << luna.at< Luna::String >( 2 ) << std::endl;
stack.pushNil();
```
# License
Luna API is distributed under GNU General Public License Version 3
