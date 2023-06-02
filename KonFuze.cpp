// ReSharper disable CppInconsistentNaming
#include "KonFuze.h"

#include <sstream>

std::vector<double*> KonFuze::bufferPool;

unsigned long long URandom::lastRand = 0ul;


KonFuze::KonFuze(const double v) : honey(0) {
	this->buffer = static_cast<double*>(malloc(sizeof(double)*10));
	WriteRemoved(v);
	const double honeyVal = this->honey;
	this->honey = v;
	this->pot = honeyVal;
}

void KonFuze::Write(const double v) {
	WriteRemoved(v);
	const double honeyVal = this->honey;
	this->honey = v;
	this->pot = honeyVal;
}


void KonFuze::WriteRemoved(const double v) {
	const int idx = URandom::GetNextInt(static_cast<int>(bufferPool.size() % INT32_MAX));
	
	double* oldBuffer = bufferPool.at(idx);
	bufferPool.at(idx) = buffer;

	this->buffer = oldBuffer;

	this->seedAtLastSet = URandom::lastRand;

	const int realNumber = URandom::GetNextInt(10);

	const double base = URandom::GetNextInt(999999) + 99999;

	for (int i = 0; i < 10; i++) {
		double newDoubleAtI;
		if (i == realNumber) [[unlikely]] {  // NOLINT(clang-diagnostic-c++20-attribute-extensions)
			newDoubleAtI = base + v;
		} else {
			const double fillerBase = URandom::GetNextInt(999999);
			newDoubleAtI = fillerBase + 99999;
		}

		buffer[i] = newDoubleAtI;
	}
}

std::string KonFuze::ToString() const {
	std::ostringstream oss;
	oss << Read();
	const std::string string = oss.str();

	return "KonFuze: {" + string + "}";
}

double KonFuze::ReadValue() const {
	URandom::lastRand = this->seedAtLastSet;

	const int realNumber = URandom::GetNextInt(10);
	const double base = URandom::GetNextInt(999999) + 99999;

	return buffer[realNumber] - base;
}

void KonFuze::Add(const double v) {
	const double newHoney = Read() + v;
	WriteRemoved(newHoney);
	const double honeyVal = this->honey;
	this->honey = newHoney;
	this->pot = honeyVal;
}

void KonFuze::StaticConstructor() {
	bufferPool = std::vector<double*>();
	ReplenishPool();
}

void KonFuze::ReplenishPool() {
	while (bufferPool.size() < 10) {
		bufferPool.push_back(static_cast<double*>(malloc(sizeof(double) * 10)));
	}
}

int URandom::GetNextInt(const int max)
{
	const unsigned long long key[9] = { lastRand / 2, lastRand / 3, lastRand / 4, lastRand / 5, lastRand / 6, lastRand / 7, lastRand / 8, lastRand / 9, lastRand / 10 };
	const unsigned long long v = lastRand & 0xFFFFFFFFFFFFULL;
	unsigned int v0 = (v >> 24) & 0xFFFFFFU;
	unsigned int v1 = (v & 0xFFFFFFU);
	unsigned int sum = 0U;

	for (int i = 32 - 1; i >= 0; --i) {
		v0 += sum + key[sum & 3] ^ (v1 >> 4 ^ v1 << 3) + v1;
		v0 &= 0xFFFFFFU;
		sum += 0xF1BFCU;
		sum &= 0xFFFFFFU;
		v1 += sum + key[sum >> 8 & 3] ^ (v0 << 3 ^ v0 >> 4) + v0;
		v1 &= 0xFFFFFFU;
	}

	lastRand = ((static_cast<unsigned long long>(v0) << 24) + v1) % static_cast<unsigned long long>((max == 0 ? INT_MAX - 1 : max));
	return static_cast<int>(lastRand);
}
