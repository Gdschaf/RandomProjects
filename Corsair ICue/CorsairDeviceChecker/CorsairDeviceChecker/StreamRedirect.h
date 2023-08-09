#pragma once

#include <iostream>

class StreamRedirect
{
public:
	StreamRedirect(std::ostream& inOriginal, std::ostream& inRedirect) :
		mOriginal(inOriginal),
		mOldBuffer(inOriginal.rdbuf(inRedirect.rdbuf()))
	{ }

	~StreamRedirect()
	{
		mOriginal.rdbuf(mOldBuffer);
	}
private:
	StreamRedirect(const StreamRedirect&);
	StreamRedirect& operator=(const StreamRedirect&);

	std::ostream& mOriginal;
	std::streambuf* mOldBuffer;
};