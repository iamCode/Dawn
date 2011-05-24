#include "random.h"

#include "gtest/gtest.h"

#include <ctime>

#include <limits>
#include <map>
using std::map;

class RandomSizeTGenerationTest : public ::testing::Test
{
	public:
	size_t numValuesGenerated;
	size_t minValue;
	size_t maxValue;
	map<size_t,size_t> occuranceCounter;

	RandomSizeTGenerationTest( size_t numValues, size_t minValue, size_t maxValue )
	{
		this->numValuesGenerated = numValues;
		this->minValue = minValue;
		this->maxValue = maxValue;

		generateSizeTValuesAndStoreInMap();
	}

	// generates a number of random size_t values and stores in a map how many of each value were generated
	void generateSizeTValuesAndStoreInMap()
	{
		occuranceCounter.clear();

		for ( size_t count=0; count<numValuesGenerated; ++count ) {
			size_t randomValue = RNG::randomSizeT( minValue, maxValue );
			occuranceCounter[randomValue]++;
		}
	}

	void testCompleteRangeIsGenerated()
	{
		for ( size_t curValue=minValue; curValue>=minValue && curValue<=maxValue; ++curValue ) {
			// check that the value was generated
			size_t curCount = occuranceCounter[curValue];
			EXPECT_GT( curCount, 0u );
			EXPECT_LE( curCount, numValuesGenerated );
		}
	}

	void testNoValuesOutOfRangeAreGenerated()
	{
		size_t inRangeCount = 0;
		for ( size_t curValue=minValue; curValue>=minValue && curValue<=maxValue; ++curValue ) {
			// check that the value was generated
			size_t curCount = occuranceCounter[curValue];
			inRangeCount += curCount;
		}
		EXPECT_EQ( numValuesGenerated, inRangeCount );
	}

	void testEqualGenerationOfValues( double allowedDeviation )
	{
		double expectedCountPerKey = static_cast<double>(numValuesGenerated) / (maxValue - minValue + 1);
		for ( size_t curValue = minValue; curValue >= minValue && curValue <= maxValue; ++curValue ) {
			size_t curCount = occuranceCounter[curValue];
			double curRatio = static_cast<double>(curCount)/expectedCountPerKey;
			EXPECT_GE( curRatio, (1.0-allowedDeviation) );
			EXPECT_LE( curRatio, (1.0+allowedDeviation) );
		}
	}
};

class RandomSizeTGenerationTest_10000_valuesBetween_6_and_10 : public RandomSizeTGenerationTest
{
public:
	RandomSizeTGenerationTest_10000_valuesBetween_6_and_10()
		: RandomSizeTGenerationTest( 10000, 6, 10 )
	{}
};

TEST_F( RandomSizeTGenerationTest_10000_valuesBetween_6_and_10, completeRangeIsGenerated )
{
	testCompleteRangeIsGenerated();
}

TEST_F( RandomSizeTGenerationTest_10000_valuesBetween_6_and_10, noValuesOutOfRangeAreGenerated )
{
	testNoValuesOutOfRangeAreGenerated();
}

TEST_F( RandomSizeTGenerationTest_10000_valuesBetween_6_and_10, similarAmountOfValuesIsGeneratedForEachKey )
{
	// 10% deviation should not be exceeded.
	testEqualGenerationOfValues( 0.1f );
}

class RandomSizeTGenerationTest_10000_valuesBetweenMaxSizeTMinus5AndMaxSizeT : public RandomSizeTGenerationTest
{
public:
	RandomSizeTGenerationTest_10000_valuesBetweenMaxSizeTMinus5AndMaxSizeT()
		: RandomSizeTGenerationTest( 10000, std::numeric_limits<size_t>::max()-5, std::numeric_limits<size_t>::max() )
	{}
};

TEST_F( RandomSizeTGenerationTest_10000_valuesBetweenMaxSizeTMinus5AndMaxSizeT, completeRangeIsGenerated )
{
	testCompleteRangeIsGenerated();
}

TEST_F( RandomSizeTGenerationTest_10000_valuesBetweenMaxSizeTMinus5AndMaxSizeT, noValuesOutOfRangeAreGenerated )
{
	testNoValuesOutOfRangeAreGenerated();
}

TEST_F( RandomSizeTGenerationTest_10000_valuesBetweenMaxSizeTMinus5AndMaxSizeT, similarAmountOfValuesIsGeneratedForEachKey )
{
	// 10% deviation should not be exceeded.
	testEqualGenerationOfValues( 0.1f );
}

class RandomSizeTGenerationTest_10000_valuesBetweenMinSizeTAnd10 : public RandomSizeTGenerationTest
{
public:
	RandomSizeTGenerationTest_10000_valuesBetweenMinSizeTAnd10()
		: RandomSizeTGenerationTest( 10000, std::numeric_limits<size_t>::min(), 10 )
	{}
};

TEST_F( RandomSizeTGenerationTest_10000_valuesBetweenMinSizeTAnd10, completeRangeIsGenerated )
{
	testCompleteRangeIsGenerated();
}

TEST_F( RandomSizeTGenerationTest_10000_valuesBetweenMinSizeTAnd10, noValuesOutOfRangeAreGenerated )
{
	testNoValuesOutOfRangeAreGenerated();
}

TEST_F( RandomSizeTGenerationTest_10000_valuesBetweenMinSizeTAnd10, similarAmountOfValuesIsGeneratedForEachKey )
{
	// 10% deviation should not be exceeded.
	testEqualGenerationOfValues( 0.1f );
}

/*
// LARGE SCALE TEST. Usually not executed
class RandomSizeTGenerationTest_1000000_valuesBetween0And100 : public RandomSizeTGenerationTest
{
public:
	RandomSizeTGenerationTest_1000000_valuesBetween0And100()
		: RandomSizeTGenerationTest( 1000000, 0, 100 )
	{}
};

TEST_F( RandomSizeTGenerationTest_1000000_valuesBetween0And100, completeRangeIsGenerated )
{
	testCompleteRangeIsGenerated();
}

TEST_F( RandomSizeTGenerationTest_1000000_valuesBetween0And100, noValuesOutOfRangeAreGenerated )
{
	testNoValuesOutOfRangeAreGenerated();
}

TEST_F( RandomSizeTGenerationTest_1000000_valuesBetween0And100, similarAmountOfValuesIsGeneratedForEachKey )
{
	// 10% deviation should not be exceeded.
	testEqualGenerationOfValues( 0.05f );
}
*/

class RandomIntGenerationTest : public ::testing::Test
{
	public:
	size_t numValuesGenerated;
	int minValue;
	int maxValue;
	map<int,size_t> occuranceCounter;

	RandomIntGenerationTest( size_t numValues, int minValue, int maxValue )
	{
		this->numValuesGenerated = numValues;
		this->minValue = minValue;
		this->maxValue = maxValue;

		generateIntValuesAndStoreInMap();
	}

	// generates a number of random int values and stores in a map how many of each value were generated
	void generateIntValuesAndStoreInMap()
	{
		occuranceCounter.clear();

		for ( size_t count=0; count<numValuesGenerated; ++count ) {
			int randomValue = RNG::randomInt( minValue, maxValue );
			occuranceCounter[randomValue]++;
		}
	}

	void testCompleteRangeIsGenerated()
	{
		for ( int curValue=minValue; curValue>=minValue && curValue<=maxValue; ++curValue ) {
			// check that the value was generated
			size_t curCount = occuranceCounter[curValue];
			EXPECT_GT( curCount, 0u );
			EXPECT_LE( curCount, numValuesGenerated );
		}
	}

	void testNoValuesOutOfRangeAreGenerated()
	{
		size_t inRangeCount = 0;
		for ( int curValue=minValue; curValue>=minValue && curValue<=maxValue; ++curValue ) {
			// check that the value was generated
			size_t curCount = occuranceCounter[curValue];
			inRangeCount += curCount;
		}
		EXPECT_EQ( numValuesGenerated, inRangeCount );
	}

	void testEqualGenerationOfValues( double allowedDeviation )
	{
		double expectedCountPerKey = static_cast<double>(numValuesGenerated) / (maxValue - minValue + 1);
		for ( int curValue = minValue; curValue >= minValue && curValue <= maxValue; ++curValue ) {
			size_t curCount = occuranceCounter[curValue];
			double curRatio = static_cast<double>(curCount)/expectedCountPerKey;
			EXPECT_GE( curRatio, (1.0-allowedDeviation) );
			EXPECT_LE( curRatio, (1.0+allowedDeviation) );
		}
	}
};

class RandomIntGenerationTest_20000_valuesBetween_Minus5_and_5 : public RandomIntGenerationTest
{
public:
	RandomIntGenerationTest_20000_valuesBetween_Minus5_and_5()
		: RandomIntGenerationTest( 20000, -10, 10 )
	{}
};

TEST_F( RandomIntGenerationTest_20000_valuesBetween_Minus5_and_5, completeRangeIsGenerated )
{
	testCompleteRangeIsGenerated();
}

TEST_F( RandomIntGenerationTest_20000_valuesBetween_Minus5_and_5, noValuesOutOfRangeAreGenerated )
{
	testNoValuesOutOfRangeAreGenerated();
}

TEST_F( RandomIntGenerationTest_20000_valuesBetween_Minus5_and_5, similarAmountOfValuesIsGeneratedForEachKey )
{
	// 10% deviation should not be exceeded.
	testEqualGenerationOfValues( 0.1f );
}

class RandomIntGenerationTest_10000_valuesBetweenMaxIntMinus5AndMaxInt : public RandomIntGenerationTest
{
public:
	RandomIntGenerationTest_10000_valuesBetweenMaxIntMinus5AndMaxInt()
		: RandomIntGenerationTest( 10000, std::numeric_limits<int>::max()-5, std::numeric_limits<int>::max() )
	{}
};

TEST_F( RandomIntGenerationTest_10000_valuesBetweenMaxIntMinus5AndMaxInt, completeRangeIsGenerated )
{
	testCompleteRangeIsGenerated();
}

TEST_F( RandomIntGenerationTest_10000_valuesBetweenMaxIntMinus5AndMaxInt, noValuesOutOfRangeAreGenerated )
{
	testNoValuesOutOfRangeAreGenerated();
}

TEST_F( RandomIntGenerationTest_10000_valuesBetweenMaxIntMinus5AndMaxInt, similarAmountOfValuesIsGeneratedForEachKey )
{
	// 10% deviation should not be exceeded.
	testEqualGenerationOfValues( 0.1f );
}

class RandomIntGenerationTest_10000_valuesBetweenMinIntAndMinIntPlus10 : public RandomIntGenerationTest
{
public:
	RandomIntGenerationTest_10000_valuesBetweenMinIntAndMinIntPlus10()
		: RandomIntGenerationTest( 10000, std::numeric_limits<int>::min(), std::numeric_limits<int>::min()+10 )
	{}
};

TEST_F( RandomIntGenerationTest_10000_valuesBetweenMinIntAndMinIntPlus10, completeRangeIsGenerated )
{
	testCompleteRangeIsGenerated();
}

TEST_F( RandomIntGenerationTest_10000_valuesBetweenMinIntAndMinIntPlus10, noValuesOutOfRangeAreGenerated )
{
	testNoValuesOutOfRangeAreGenerated();
}

TEST_F( RandomIntGenerationTest_10000_valuesBetweenMinIntAndMinIntPlus10, similarAmountOfValuesIsGeneratedForEachKey )
{
	// 10% deviation should not be exceeded.
	testEqualGenerationOfValues( 0.1f );
}

/*
// LARGE Scale test. Usually not executed
class RandomIntGenerationTest_2000000_valuesBetweenMinus100And100 : public RandomIntGenerationTest
{
public:
	RandomIntGenerationTest_2000000_valuesBetweenMinus100And100()
		: RandomIntGenerationTest( 2000000, -100, 100 )
	{}
};

TEST_F( RandomIntGenerationTest_2000000_valuesBetweenMinus100And100, completeRangeIsGenerated )
{
	testCompleteRangeIsGenerated();
}

TEST_F( RandomIntGenerationTest_2000000_valuesBetweenMinus100And100, noValuesOutOfRangeAreGenerated )
{
	testNoValuesOutOfRangeAreGenerated();
}

TEST_F( RandomIntGenerationTest_2000000_valuesBetweenMinus100And100, similarAmountOfValuesIsGeneratedForEachKey )
{
	// 10% deviation should not be exceeded.
	testEqualGenerationOfValues( 0.05f );
}
*/


int main( int argc, char **argv )
{
	// init test
	RNG::initRNG( 12345678 );
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
