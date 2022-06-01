#include "pch.h"
#include "../PolinomLab/Polynom.h"

TEST(Monom, can_create_empty_Monom)
{
	ASSERT_NO_THROW(Monom m);
}
TEST(Monom, can_create_Monom)
{
	ASSERT_NO_THROW(Monom m(2, 47));
}
TEST(Monom, can_not_create_Monom_degree_more_999)
{
	ASSERT_ANY_THROW(Monom m(7, 2311));
}


TEST(Polynom, Can_create_empty_Polynom)
{
	ASSERT_NO_THROW(Polynom p);
}
TEST(Polynom, Can_create_Polynom_from_string)
{
	ASSERT_NO_THROW(Polynom p("24x^2+12xyz-5"));
}
TEST(Polynom, Can_create_Polynom_copy)
{
	Polynom p1("24x^2+12xyz-5");
	ASSERT_NO_THROW(Polynom p2 = p1);
}
TEST(Polynom, Add_polynom_and_monom1)
{
	Monom m(18, 127);
	Polynom P("-40xy^2z^7");
	P = P + m;

	Polynom B("-22xy^2z^7");
	EXPECT_EQ(B, P);
}
TEST(Polynom, Add_polynom_and_monom2)
{
	Monom m(2, 470);
	Polynom P("y^2+9");
	P = P + m;

	Polynom B("2x^4y^7+y^2+9");
	EXPECT_EQ(B, P);
}
TEST(Polynom, Can_create_Polynom_from_string2)
{
	Polynom P("y^2+9y^2");
	Polynom B("10y^2");
	EXPECT_EQ(B, P);
}
TEST(Polynom, Can_create_Polynom_from_string3)
{
	Polynom P("y^2z^3x");
	Polynom B("xy^2z^3");
	EXPECT_EQ(B, P);
}
TEST(Polynom, Can_create_Polynom_from_string4)
{
	Polynom P("12+x+y^2z^3x");
	Polynom B("xy^2z^3+x+12");
	EXPECT_EQ(B, P);
}
TEST(Polynom, Can_create_Polynom_from_string5)
{
	Polynom P("-x^2+x^3");
	Polynom B("x^3-x^2");
	EXPECT_EQ(B, P);
}
TEST(Polynom, Add_polynom11)
{
	Polynom P1("3x^5y^2z^5-5x^4y^3z^3+7x^3y^5z");
	Polynom P2("4x^3y^2z^6-6x^2yz^8");
	Polynom R("3x^5y^2z^5-5x^4y^3z^3+7x^3y^5z+4x^3y^2z^6-6x^2yz^8");

	EXPECT_EQ(R, P1 + P2);
}
TEST(Polynom, Add_polynom12)
{
	Polynom P1("3x^5y^2z^5-5x^4y^3z^3+7x^7y^5z");
	Polynom P2("-3x^5y^2z^5+5x^4y^3z^3-7x^7y^5z");
	Polynom R;                                      

	EXPECT_EQ(R, P1 + P2);
}
TEST(Polynom, Add_polynom13)
{
	Polynom P1("3x^5y^2z^5-5x^4y^3z^3+7x^3y^5z");
	Polynom P2("4x^7y^2z^6-6x^6yz^8");
	Polynom R("4x^7y^2z^6-6x^6yz^8+3x^5y^2z^5-5x^4y^3z^3+7x^3y^5z");

	EXPECT_EQ(R, P1 + P2);
}
TEST(Polynom, Add_polynom14)
{
	Polynom P1("3x^5y^2z^5-5x^4y^3z^3+7x^3y^5z");
	Polynom P2("4x^5y^2z^5+5x^4y^3z^3");
	Polynom R("7x^5y^2z^5+7x^3y^5z");

	EXPECT_EQ(R, P1 + P2);
}
TEST(Polynom, Add_polynom15)
{
	Polynom P1("3x^5y^2z^5-5x^4y^3z^3+7x^7y^5z");
	Polynom P2("4x^6y^2z^6-6x^2yz^8");
	Polynom R("7x^7y^5z+4x^6y^2z^6+3x^5y^2z^5-5x^4y^3z^3-6x^2yz^8");

	EXPECT_EQ(R, P1 + P2);
}
TEST(Polynom, Add_polynom_and_monom3)
{
	Monom m(23, 000);
	Polynom P("y^2+x");
	P = P + m;

	Polynom B("y^2+x+23");
	EXPECT_EQ(B, P);
}
TEST(Polynom, Add_polynom1)
{
	Polynom P1("141.59x^2y^6z^5+35.89x^7y^9z^3-23.8z^4-1");
	Polynom P2("64x^2y^6z^5+338x^7y^9z^3-3.27z^3-95");
	Polynom R("373.89x^7y^9z^3+205.59x^2y^6z^5-23.8z^4-3.27z^3-96");

	EXPECT_EQ(R, P1 + P2);
}
TEST(Polynom, Add_polynom2)
{
	Polynom P1("141.59x^2y^6z^5+35.89x^7y^9z^3-23.8z^4-1");
	Polynom P2("64x^2y^8z^8-3.27z^4");
	Polynom R("35.89x^7y^9z^3+64x^2y^8z^8+141.59x^2y^6z^5-27.07z^4-1");

	EXPECT_EQ(R, P1 + P2);
}
TEST(Polynom, Sub_polynom1)
{
	Polynom P1("141.59x^2y^6z^5+35.89x^7y^9z^3-23.8z^4-1");
	Polynom P2("64x^2y^6z^5+338x^7y^9z^3-3.27z^3-95");
	Polynom R("-302.11x^7y^9z^3+77.59x^2y^6z^5-23.8z^4+3.27z^3+94");

	EXPECT_EQ(R, P1 - P2);
}
TEST(Polynom, Sub_polynom2)
{
	Polynom P1("141.59x^2y^6z^5+35.89x^7y^9z^3-23.8z^4-1");
	Polynom P2("64x^2y^8z^8-3.27z^4");
	Polynom R("35.89x^7y^9z^3-64x^2y^8z^8+141.59x^2y^6z^5-20.53z^4-1");

	EXPECT_EQ(R, P1 - P2);
}
TEST(Polynom, Mult_polynom_and_zero_monom)
{
	Polynom A("64x^2y^8z^8-3.27z^4");
	Monom m = 0;

	Polynom B;
	EXPECT_EQ(B, A * m);
}
TEST(Polynom, Can_not_mult_polynom_and_monom_digree_more_10)
{
	Polynom A("64x^2y^6z^5+338x^7y^9z^3-3.27z^3-95");
	Monom m(67, 999);

	ASSERT_ANY_THROW(A * m);
}
TEST(Polynom, Mult_polynom_and_monom)
{
	Polynom A("2x^4y^7+y^2+9");
	Monom m(4, 123);

	Polynom B("8x^5y^9z^3+4xy^4z^3+36xy^2z^3");

	EXPECT_EQ(B, A * m);
}
TEST(Polynom, Can_not_mult_digree_more_10)
{
	Polynom A("64x^2y^6z^5+338x^7y^9z^3-3.27z^3-95");
	Polynom B("24x^2+12x^9y^9z^9-5");

	ASSERT_ANY_THROW(A * B);
}
TEST(Polynom, Mult_polynom)
{
	Polynom A("2x^4y^7+y^2+9");
	Polynom B("24x^2+12x-5");

	Polynom C("48x^6y^7+24x^5y^7-10x^4y^7+24x^2y^2+216x^2+12xy^2+108x-5y^2-45");

	EXPECT_EQ(C, A * B);
}