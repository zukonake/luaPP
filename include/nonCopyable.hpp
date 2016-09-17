//2016-nonCopyable zukonake

#ifndef NONCOPYABLE_HPP
#define NONCOPYABLE_HPP

class NonCopyable
{
protected:
	NonCopyable() = default;

	virtual ~NonCopyable() = default;

	NonCopyable( const NonCopyable& that ) = delete;
	NonCopyable& operator=( const NonCopyable& that ) = delete;
};

#endif
