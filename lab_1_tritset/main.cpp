/*!
	The class implements a vector of trits that grows as needed. Each element of the TritSet occupies 2 bits
	and has three possible values: FALSE, UNKNOWN or TRUE.
	Individual indexed trits can be examined, set, or cleared.
	One TritSet may be used to modify the contents of another TritSet through logical AND and logical OR.
*/

#include "TritSet.h"
#include "gtest/gtest.h"

using namespace std;

TEST(MemoryAllocation, InitTest) 
{
	TritSet set(100);
	EXPECT_EQ(100, set.get_capacity());
	EXPECT_EQ(100 * 2 / 8 / sizeof(unsigned int) + 1, set.get_uint_capacity());
}

TEST(MemoryAllocation, AllocationTest)
{
	TritSet set(100);
	ASSERT_NO_THROW(set[101] = TRUE, bad_alloc);
	EXPECT_LT(100, set.get_capacity());
}

TEST(MemoryAllocation, NoAllocationTest)
{
	TritSet set(100);
	ASSERT_NO_THROW(set[101] = UNKNOWN, bad_alloc);
	EXPECT_EQ(100, set.get_capacity());
	ASSERT_NO_THROW(set[101] == UNKNOWN, bad_alloc);
	EXPECT_EQ(100, set.get_capacity());
	ASSERT_NO_THROW(set[101] == TRUE, bad_alloc);
	EXPECT_EQ(100, set.get_capacity());
}

TEST(MemoryAllocation, ShrinkTest)
{
	TritSet set(100);
	set[98] = TRUE;
	set.shrink();
	EXPECT_EQ(99, set.get_capacity());
}

TEST(MemoryAllocation, TrimTest)
{
	TritSet set(100);
	set.trim(50);
	EXPECT_EQ(50, set.get_capacity());
}

TEST(OperatorOverload, OperatorEqEqTest)
{
	TritSet set(3);
	TritSet set_similar(3);
	TritSet set_different(3);
	TritSet set_diff_size(2);
	for (int i = 0; i < set.get_capacity(); i++) {
		set[i] = set_similar[i] = TRUE;
		set_different[i] = FALSE;
	}
	for (int i = 0; i < set_diff_size.get_capacity(); i++)
		set_diff_size[i] = TRUE;
	bool result = set == set_similar;
	EXPECT_EQ(result, true);
	result = set == set_different;
	EXPECT_EQ(result, false);
	result = set == set_diff_size;
	EXPECT_EQ(result, false);

}

TEST(OperatorOverload, OperatorNotEqTest)
{
	TritSet set(3);
	TritSet set_similar(3);
	TritSet set_different(3);
	TritSet set_diff_size(2);
	for (int i = 0; i < set.get_capacity(); i++) {
		set[i] = set_similar[i] = TRUE;
		set_different[i] = FALSE;
	}
	for (int i = 0; i < set_diff_size.get_capacity(); i++)
		set_diff_size[i] = TRUE;
	bool result = set != set_similar;
	EXPECT_EQ(result, false);
	result = set != set_different;
	EXPECT_EQ(result, true);
	result = set != set_diff_size;
	EXPECT_EQ(result, true);

}

TEST(OperatorOverload, OperatorNotTableTest)
{
	TritSet set(3);
	set[0] = TRUE;
	set[1] = UNKNOWN;
	set[2] = FALSE;
	EXPECT_EQ(~set[0], FALSE);
	EXPECT_EQ(~set[1], UNKNOWN);
	EXPECT_EQ(~set[2], TRUE);
}

TEST(OperatorOverload, OperatorNotTest)
{
	TritSet set(3);
	set[0] = TRUE;
	set[1] = UNKNOWN;
	set[2] = FALSE;
	TritSet expected_result_set(3);
	expected_result_set[0] = FALSE;
	expected_result_set[1] = UNKNOWN;
	expected_result_set[2] = TRUE;
	bool result = expected_result_set == ~set;
	EXPECT_EQ(result, true);
}

TEST(OperatorOverload, OperatorAndTableTest)
{
	TritSet set(3);
	set[0] = TRUE;
	set[1] = UNKNOWN;
	set[2] = FALSE;
	EXPECT_EQ(set[0] & set[0], TRUE);
	EXPECT_EQ(set[0] & set[1], TRUE);
	EXPECT_EQ(set[0] & set[2], FALSE);
	EXPECT_EQ(set[1] & set[1], UNKNOWN);
	EXPECT_EQ(set[1] & set[2], FALSE);
	EXPECT_EQ(set[2] & set[2], FALSE);
}

TEST(OperatorOverload, OperatorAndTest)
{
	TritSet set_1(3);
	set_1[0] = TRUE;
	set_1[1] = UNKNOWN;
	set_1[2] = FALSE;
	TritSet set_2(3);
	set_2[0] = UNKNOWN;
	set_2[1] = FALSE;
	set_2[2] = TRUE;
	TritSet expected_result_set(3);
	expected_result_set[0] = TRUE;
	expected_result_set[1] = FALSE;
	expected_result_set[2] = FALSE;
	bool result = expected_result_set == (set_1 & set_2);
	EXPECT_EQ(result, true);
}

TEST(OperatorOverload, OperatorOrTableTest)
{
	TritSet set(3);
	set[0] = TRUE;
	set[1] = UNKNOWN;
	set[2] = FALSE;
	EXPECT_EQ(set[0] | set[0], TRUE);
	EXPECT_EQ(set[0] | set[1], TRUE);
	EXPECT_EQ(set[0] | set[2], TRUE);
	EXPECT_EQ(set[1] | set[1], UNKNOWN);
	EXPECT_EQ(set[1] | set[2], UNKNOWN);
	EXPECT_EQ(set[2] | set[2], FALSE);
}

TEST(OperatorOverload, OperatorOrTest)
{
	TritSet set_1(3);
	set_1[0] = TRUE;
	set_1[1] = UNKNOWN;
	set_1[2] = FALSE;
	TritSet set_2(3);
	set_2[0] = UNKNOWN;
	set_2[1] = FALSE;
	set_2[2] = TRUE;
	TritSet expected_result_set(3);
	expected_result_set[0] = TRUE;
	expected_result_set[1] = UNKNOWN;
	expected_result_set[2] = TRUE;
	bool result = expected_result_set == (set_1 | set_2);
	EXPECT_EQ(result, true);
}

int main(int argc, char *argv[]) {
	::testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
	return 0;
}
