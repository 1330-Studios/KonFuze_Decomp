#pragma once
#include <vector>
#include <ctime>
#include <xstring>

// ReSharper disable CppInconsistentNaming
class KonFuze {
public:
	explicit KonFuze(double v);

	void Write(double v);
	void WriteRemoved(double v);
	std::string ToString() const;
	double ReadValue() const;
	double Read() const	{
		return ReadValue();
	}
	void Add(double v);

	double get_Value() const {
		return Read();
	}
	float get_ValueFloat() const {
		return static_cast<float>(Read());
	}
	long long get_ValueLong() const {
		return static_cast<unsigned int>(static_cast<int>(Read()));
	}
	bool get_ValueBool() const {
		return static_cast<int>(Read()) != 0;
	}

	static void StaticConstructor();
	static void ReplenishPool();
	
	double* buffer;
	double pot;
	double honey;
	unsigned long long seedAtLastSet{};
	
	static std::vector<double*> bufferPool;
};

class KonFuze_NoShuffle : public KonFuze {
public:
	explicit KonFuze_NoShuffle(const double v) : KonFuze(v){}

	double Read();
};

// Only here for example, NK uses SeededRandom
class URandom {
public:
	static unsigned long long lastRand;

	static int GetNextInt(int max = 0);
};