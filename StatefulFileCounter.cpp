#include "StatefulFileCounter.h"

#include <sys/stat.h>

#ifdef TESTCASE //test driven development testing
#undef TESTCASE
#endif

#ifdef TESTCASE
#include <iostream>
#endif

StatefulFileCounter::StatefulFileCounter(const std::string ksFileName, const unsigned int kuiCounter)
{

	const bool kbFileExist = bFileExist(ksFileName);

#ifdef TESTCASE
	if (bFileExist(ksFileName))
		std::cout << "File exists" << std::endl;
	else
		std::cout << "File dont exist" << std::endl;
#endif

	mfsFile.open(ksFileName, std::ios::in | std::ios::out | std::ios::binary | std::ios::ate);

	if (mfsFile.is_open())
	{
#ifdef TESTCASE
		std::cout << "File open successfully!" << std::endl;
#endif
		if (!kbFileExist)
		{
			//write Counter in constructor to file since it is newly opened
			writeNumberToFile(kuiCounter);
		}
		readNumberFromFile();
	}
	else
	{
#ifdef TESTCASE
		std::cout << "Unable to open file or file doesn't exist! Making new one..." << std::endl;
#endif
		mfsFile.open(ksFileName, std::ios::in | std::ios::out | std::ios::binary | std::ios::trunc);
		writeNumberToFile(kuiCounter);
	}

}


StatefulFileCounter::~StatefulFileCounter() {
	if (mfsFile.is_open())
	{
		mfsFile.close();
	}
}


inline bool StatefulFileCounter::bFileExist(const std::string& filename) {
	struct stat buffer;
	return (stat(filename.c_str(), &buffer) == 0);
}

inline void StatefulFileCounter::writeNumberToFile(const unsigned int kuiCounter)
{
	const uint32_t writeNo = (uint32_t)kuiCounter;
#ifdef TESTCASE
	std::cout << "number will write: " << kuiCounter << std::endl;
#endif
	if (mfsFile.is_open())
	{
		mfsFile.seekp(0, std::ios::beg);
		mfsFile.write(reinterpret_cast<const char *>(&writeNo), sizeof(writeNo));
		mfsFile.flush();
	}

}

inline unsigned int StatefulFileCounter::readNumberFromFile()
{
	uint32_t retCounter = 0;

	if (mfsFile.is_open())
	{
		mfsFile.seekg(0, std::ios::beg);
		mfsFile.read(reinterpret_cast<char*>(&retCounter), sizeof(retCounter));
		mfsFile.flush();
	}
	
	
	return (unsigned int)retCounter;
}

inline void StatefulFileCounter::subtractByOne()
{
	unsigned int temp = readNumberFromFile();
#ifdef TESTCASE
	std::cout << "temp in sub by one: " << temp << std::endl;
#endif
	writeNumberToFile(--temp);
}

inline void StatefulFileCounter::addByOne() 
{
	unsigned int temp = readNumberFromFile();
	writeNumberToFile(++temp);
}

unsigned int StatefulFileCounter::operator-- (int)
{
	unsigned int temp = readNumberFromFile();
	subtractByOne();
	return temp;
}

unsigned int StatefulFileCounter::operator-- ()
{
	subtractByOne();
	return *this;
}

unsigned int StatefulFileCounter::operator++ (int)
{
	unsigned int temp = readNumberFromFile();
	addByOne();
	return temp;
}

unsigned int StatefulFileCounter::operator++ ()
{
	addByOne();
	return *this;
}

StatefulFileCounter& StatefulFileCounter::operator=(const unsigned int& rhs)
{
	writeNumberToFile(rhs);
	return *this;
}

CounterError StatefulFileCounter::isWorking() const
{
	if (mfsFile.is_open())
	{
		if (mfsFile.good())
		{
			return CounterError::NO_ERROR;
		}
		else
		{
			if (mfsFile.eof())
			{
				return CounterError::STREAM_EOF;
			}
			else if (mfsFile.fail())
			{
				return CounterError::STREAM_FAIL;
			}
			else if (mfsFile.bad())
			{
				return CounterError::STREAM_BAD;
			}
			return CounterError::STREAM_FAIL;
		}
	}
	else
	{
		return CounterError::STREAM_NOT_OPEN;
	}

}

