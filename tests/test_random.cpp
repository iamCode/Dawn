#include "random.h"

#include <cassert>
#include <ctime>

#include <limits>
#include <map>
using std::map;

// generates a number of random size_t values and stores in a map how many of each value were generated
void generateSizeTValuesAndStoreInMap( size_t numValues, size_t min, size_t max, map<size_t,size_t> &counter )
{
	for ( size_t count=0; count<numValues; ++count ) {
		size_t randomValue = RNG::randomSizeT( min, max );
		counter[randomValue]++;
	}
}

void testGenerationOfCompleteRange( size_t generateCount, size_t min, size_t max, map<size_t,size_t> &counterMap )
{
	size_t numValuesInRange = 0;
	for ( size_t curValue=min; curValue>=min && curValue<=max; ++curValue ) {
		numValuesInRange += counterMap[curValue];
		// check that the value was generated
		size_t curCount = counterMap[curValue];
		assert( curCount > 0 && curCount <= generateCount );
	}
	// check that all values generated where in the given range
	assert( numValuesInRange == generateCount );
}

void testEqualGenerationOfValues( size_t generateCount, size_t min, size_t max, map<size_t,size_t> &counter, double allowedDeviation )
{
	double expectedCount = static_cast<double>(generateCount) / (max - min + 1);
	for ( size_t curValue = min; curValue >= min && curValue <= max; ++curValue ) {
		size_t curCount = counter[curValue];
		double curRatio = static_cast<double>(curCount)/expectedCount;
		assert( curRatio >= (1.0-allowedDeviation) );
		assert( curRatio <= (1.0+allowedDeviation) );
	}
}

// the the function randomSizeT
void test_randomSizeT()
{
	std::map<size_t,size_t> counterMap;
	// test for small range of values
	// check that we have all values in range [min,max] and that each value occurs about equally
	// We allow a deviation of 5% from total average
	size_t generateCount = 10000;
	size_t minValue = 6;
	size_t maxValue = 10;
	generateSizeTValuesAndStoreInMap( generateCount, minValue, maxValue, counterMap );
	
	// ensure all values where generated
	testGenerationOfCompleteRange( generateCount, minValue, maxValue, counterMap );
	// ensure each value was generated about the expected number
	testEqualGenerationOfValues( generateCount, minValue, maxValue, counterMap, 0.05 );


	// same test, but with range at upper limit
	counterMap.clear();
	maxValue = std::numeric_limits<size_t>::max();
	minValue = maxValue - 4;
	generateSizeTValuesAndStoreInMap( generateCount, minValue, maxValue, counterMap );
	
	// ensure all values where generated
	testGenerationOfCompleteRange( generateCount, minValue, maxValue, counterMap );
	// ensure each value was generated about the expected number
	testEqualGenerationOfValues( generateCount, minValue, maxValue, counterMap, 0.05 );
}

int main()
{
	// init test
	RNG::initRNG( time(0) );
	test_randomSizeT();
}
