#include <gtest/gtest.h>
#include "main.hpp"
#include <algorithm>

TEST(InfLineTest, MutualPositionTest1) {
	InfLine il1(Point(2.f, 3.f), Point(8.f, 6.f));
	InfLine il2(Point(3.f, 1.f), Point(9.f, 4.f));
	auto mPos = il1.mutualPosition(il2);
	EXPECT_EQ(mPos, InfLine::posType::disjoint);
}

TEST(InfLineTest, MutualPositionTest2) {
	InfLine il1(Point(2.f, 3.f), Point(8.f, 6.f));
	InfLine il2(Point(3.f, 1.f), Point(9.f, 1.f));
	auto mPos = il1.mutualPosition(il2);
	EXPECT_EQ(mPos, InfLine::posType::intersect);
}

TEST(InfLineTest, MutualPositionTest3) {
	InfLine il1(Point(2.f, 3.f), Point(8.f, 6.f));
	InfLine il2(Point(2.f, 3.f), Point(14.f, 9.f));
	auto mPos = il1.mutualPosition(il2);
	EXPECT_EQ(mPos, InfLine::posType::overlap);
}

TEST(InfLineTest, MutualPositionTest4) {
	InfLine il1(Point(2.f, 3.f), Point(2.f, -5.f));
	InfLine il2(Point(-6.f, 1.f), Point(5.f, 1.f));
	auto mPos = il1.mutualPosition(il2);
	EXPECT_EQ(mPos, InfLine::posType::intersect);
}

TEST(InfLineTest, MutualPositionTest5) {
	InfLine il1(Point(2.f, 3.f), Point(2.f, -5.f));
	InfLine il2(Point(0.f, 8.f), Point(0.f, -2.f));
	auto mPos = il1.mutualPosition(il2);
	EXPECT_EQ(mPos, InfLine::posType::disjoint);
}

TEST(InfLineTest, IntersectionTest1) {
	InfLine il1(Point(2.f, 3.f), Point(8.f, 6.f));
	InfLine il2(Point(3.f, 1.f), Point(9.f, 1.f));
	EXPECT_TRUE(il1.intersection(il2) == Point(-2.f, 1.f));
}

TEST(stdAlgorithmTest, max_elementTest) {
	std::vector<Line> lines;
	lines.push_back(Line(0.f, 0.f, 3.f, 2.f));
	lines.push_back(Line(0.f, 0.f, 5.f, 3.f));
	lines.push_back(Line(0.f, 0.f, 0.f, 3.f));
	lines.push_back(Line(0.f, 0.f, 5.f, 0.f));
	auto maxLine = std::max_element(lines.begin(), lines.end(),
		[](Line l1, Line l2) {return l1.len() < l2.len(); });
	EXPECT_TRUE((*maxLine) == Line(0.f, 0.f, 5.f, 3.f));
}

TEST(LineTest, Intersection1){
	Line l1(0.f, 0.f, 2.f, 2.f);
	Line l2(2.f, 0.f, 0.f, 2.f);
	Line intrsct = l1.intersection(l2);
	EXPECT_TRUE(intrsct.is_point());
	EXPECT_TRUE(intrsct == Line(1.f, 1.f, 1.f, 1.f));
}

TEST(LineTest, Intersection2) {
	Line l1(0.f, 0.f, 6.f, 3.f);
	Line l2(4.f, 2.f, 8.f, 4.f);
	Line intrsct = l1.intersection(l2);
	EXPECT_FALSE(intrsct.is_point());
	EXPECT_TRUE(intrsct == Line(4.f, 2.f, 6.f, 3.f));
}

TEST(LineTest, Intersection3) {
	Line l1(-1.f, 0.f, 2.f, 2.f);
	Line l2(1.f, 1.f, 3.f, -1.f);
	EXPECT_THROW(l1.intersection(l2), NoIntersectionException);
}

TEST(LineTest, Intersection4) {
	Line l1(0.f, 0.f, 3.f, 2.f);
	Line l2(1.f, 0.f, 4.f, 2.f);
	EXPECT_THROW(l1.intersection(l2), NoIntersectionException);
}

TEST(LineTest, Intersection5) {
	Line l1(0.f, 0.f, 3.f, 2.f);
	Line l2(3.f, 2.f, 5.f, 0.f);
	Line intrsct = l1.intersection(l2);
	EXPECT_TRUE(intrsct.is_point());
	EXPECT_TRUE(intrsct == Line(3.f, 2.f, 3.f, 2.f));
}

TEST(LineTest, Intersection6) {
	Line l1(0.f, 0.f, 4.f, 2.f);
	Line l2(6.f, 3.f, 4.f, 2.f);
	Line intrsct = l1.intersection(l2);
	EXPECT_TRUE(intrsct.is_point());
	EXPECT_TRUE(intrsct == Line(4.f, 2.f, 4.f, 2.f));
}
TEST(LineTest, Intersection7) {
	Line l1(1.f, 0.f, 1.f, 3.f);
	Line l2(l1);
	Line intrsct = l1.intersection(l2);
	EXPECT_TRUE(intrsct == l1);
}
