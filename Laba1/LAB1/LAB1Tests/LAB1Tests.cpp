#include "pch.h"
#include "CppUnitTest.h"
#include "../LAB1/Solver.h"
#include "../LAB1/LexemeString.h"
#include "../LAB1/Lexeme.h"
#include "../LAB1/PolishReverseConverter.h"
#include "../LAB1/Parser.h"
#include "../LAB1/ConsoleManager.h"

#define ACCURACY 4

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace LAB1Tests
{
	double roundTo(double x, int precision)
	{
		int mul = 10;

		for (int i = 0; i < precision; i++)
			mul *= mul;
		if (x > 0)
			return floor(x * mul + .5) / mul;
		else
			return ceil(x * mul - .5) / mul;
	}

	TEST_CLASS(LAB1Tests)
	{
	public:
		
		TEST_METHOD(TestAddingIntegers)
		{
			ConsoleManager manager;

			double res = manager.execute("1+1");
			Assert::IsTrue(double(2) == res);

			res = manager.execute("(1)+(1)");
			Assert::IsTrue(double(2) == res);

			res = manager.execute("(1)+(-1)");
			Assert::IsTrue(double(0) == res);

			res = manager.execute("5+2");
			Assert::IsTrue(double(7) == res);

			res = manager.execute("-1+4");
			Assert::IsTrue(double(3) == res);

			res = manager.execute("+1+4");
			Assert::IsTrue(double(5) == res);

			res = manager.execute("-1+(-5)");
			Assert::IsTrue(double(-6) == res);

			res = manager.execute("(-1)+(-5)");
			Assert::IsTrue(double(-6) == res);

			res = manager.execute("(+1)+(+5)");
			Assert::IsTrue(double(6) == res);

			res = manager.execute("1+(-100)++");
			Assert::IsTrue(NULL == res);

			res = manager.execute("++(+100)+1");
			Assert::IsTrue(NULL == res);

			res = manager.execute("1+(-100)+");
			Assert::IsTrue(NULL == res);

			res = manager.execute("(++100)+1");
			Assert::IsTrue(NULL == res);
		}

		TEST_METHOD(TestSubtractingIntegers)
		{
			ConsoleManager manager;

			double res = manager.execute("1-1");
			Assert::IsTrue(double(0) == res);

			res = manager.execute("(1)-(1)");
			Assert::IsTrue(double(0) == res);

			res = manager.execute("(1)-(-1)");
			Assert::IsTrue(double(2) == res);

			res = manager.execute("5-2");
			Assert::IsTrue(double(3) == res);

			res = manager.execute("-1-4");
			Assert::IsTrue(double(-5) == res);

			res = manager.execute("+1-4");
			Assert::IsTrue(double(-3) == res);

			res = manager.execute("-1-(-5)");
			Assert::IsTrue(double(4) == res);

			res = manager.execute("(-1)-(-5)");
			Assert::IsTrue(double(4) == res);

			res = manager.execute("(+1)-(+5)");
			Assert::IsTrue(double(-4) == res);

			res = manager.execute("1-(-100)--");
			Assert::IsTrue(NULL == res);

			res = manager.execute("--(-100)-1");
			Assert::IsTrue(NULL == res);

			res = manager.execute("1-(-100)-");
			Assert::IsTrue(NULL == res);

			res = manager.execute("(--100)-1");
			Assert::IsTrue(NULL == res);
		}

		TEST_METHOD(TestMultiplyIntegers)
		{
			ConsoleManager manager;

			double res = manager.execute("1*1");
			Assert::IsTrue(double(1) == res);

			res = manager.execute("(1)*(1)");
			Assert::IsTrue(double(1) == res);

			res = manager.execute("(1)*(-1)");
			Assert::IsTrue(double(-1) == res);

			res = manager.execute("5*2");
			Assert::IsTrue(double(10) == res);

			res = manager.execute("-1*4");
			Assert::IsTrue(double(-4) == res);

			res = manager.execute("+1*4");
			Assert::IsTrue(double(4) == res);

			res = manager.execute("-1*(-5)");
			Assert::IsTrue(double(5) == res);

			res = manager.execute("(-1)*(-5)");
			Assert::IsTrue(double(5) == res);

			res = manager.execute("(+1)*(+5)");
			Assert::IsTrue(double(5) == res);

			res = manager.execute("(+10000)*(+10)");
			Assert::IsTrue(double(100000) == res);

			res = manager.execute("1+(-100)*");
			Assert::IsTrue(NULL == res);

			res = manager.execute("*(-100)+1");
			Assert::IsTrue(NULL == res);

			res = manager.execute("1+(-100)**0");
			Assert::IsTrue(NULL == res);
		}

		TEST_METHOD(TestDivisionIntegers)
		{
			ConsoleManager manager;

			double res = manager.execute("1/1");
			Assert::IsTrue(double(1) == res);

			res = manager.execute("(1)/(1)");
			Assert::IsTrue(double(1) == res);

			res = manager.execute("(1)/(-1)");
			Assert::IsTrue(double(-1) == res);

			res = manager.execute("5/2");
			Assert::IsTrue(double(2.5) == res);

			res = manager.execute("-1/4");
			Assert::IsTrue(double(-0.25) == res);

			res = manager.execute("+1/4");
			Assert::IsTrue(double(0.25) == res);

			res = manager.execute("-1/(-5)");
			Assert::IsTrue(double(0.2) == res);

			res = manager.execute("(-1)/(-5)");
			Assert::IsTrue(double(0.2) == res);

			res = manager.execute("(+1)/(+5)");
			Assert::IsTrue(double(0.2) == res);

			res = manager.execute("(+10000)/(+10)");
			Assert::IsTrue(double(1000) == res);

			res = manager.execute("1+(+10000)//(+10)");
			Assert::IsTrue(NULL == res);

			res = manager.execute("1+(-100)/");
			Assert::IsTrue(NULL == res);

			res = manager.execute("/(-100)+1");
			Assert::IsTrue(NULL == res);

			res = manager.execute("1+ (-100)/0");
			Assert::IsTrue(NULL == res);
		}

		TEST_METHOD(TestExponentIntegers)
		{
			ConsoleManager manager;

			double res = manager.execute("1^1");
			Assert::IsTrue(double(1) == res);

			res = manager.execute("(1)^(1)");
			Assert::IsTrue(double(1) == res);

			res = manager.execute("(1)^(-1)");
			Assert::IsTrue(double(1) == res);

			res = manager.execute("5^2");
			Assert::IsTrue(double(25) == res);

			res = manager.execute("-1^4");
			Assert::IsTrue(double(1) == res);

			res = manager.execute("+1^4");
			Assert::IsTrue(double(1) == res);

			res = manager.execute("-1^(-5)");
			Assert::IsTrue(double(-1) == res);

			res = manager.execute("(-1)^(-5)");
			Assert::IsTrue(double(-1) == res);

			res = manager.execute("(+1)^(+5)");
			Assert::IsTrue(double(1) == res);

			res = manager.execute("(+2)^(+10)");
			Assert::IsTrue(double(1024) == res);

			res = manager.execute("(-2)^(+10)");
			Assert::IsTrue(double(1024) == res);

			res = manager.execute("(-2)^(+9)");
			Assert::IsTrue(double(-512) == res);

			res = manager.execute("(-2)^(-1)");
			Assert::IsTrue(double(-0.5) == res);

			res = manager.execute("(100)^(0)");
			Assert::IsTrue(double(1) == res);

			res = manager.execute("(-100)^(0)");
			Assert::IsTrue(double(1) == res);

			res = manager.execute("(-100)^(-0)");
			Assert::IsTrue(double(1) == res);

			res = manager.execute("(-100)^^(-0)");
			Assert::IsTrue(NULL == res);

			res = manager.execute("^(-100)^(-0)");
			Assert::IsTrue(NULL == res);

			res = manager.execute("(-100)^");
			Assert::IsTrue(NULL == res);

			res = manager.execute("()^1");
			Assert::IsTrue(NULL == res);
		}

		TEST_METHOD(TestAddingDoubles)
		{
			ConsoleManager manager;

			double res = manager.execute("0.1+0.2");
			Assert::IsTrue(roundTo(double(0.3),4) == roundTo(res, ACCURACY));

			res = manager.execute("(1.0)+(1.1)");
			Assert::IsTrue(roundTo(double(2.1), ACCURACY) == roundTo(res, ACCURACY));

			res = manager.execute("(1.1)+(-1.2)");
			Assert::IsTrue(roundTo(double(-0.1), ACCURACY) == roundTo(res, ACCURACY));

			res = manager.execute("5.5+2.5");
			Assert::IsTrue(roundTo(double(8), ACCURACY) == roundTo(res, ACCURACY));

			res = manager.execute("-1.1+4");
			Assert::IsTrue(roundTo(double(2.9), ACCURACY) == roundTo(res, ACCURACY));

			res = manager.execute("+1.0+4.5");
			Assert::IsTrue(roundTo(double(5.5), ACCURACY) == roundTo(res, ACCURACY));

			res = manager.execute("-1.000001+(-5.999999)");
			Assert::IsTrue(roundTo(double(-7), ACCURACY) == roundTo(res, ACCURACY));

			res = manager.execute("(-1.11)+(-5.1)");
			Assert::IsTrue(roundTo(double(-6.21), ACCURACY) == roundTo(res, ACCURACY));

			res = manager.execute("(+1.75)+(+5)");
			Assert::IsTrue(roundTo(double(6.75), ACCURACY) == roundTo(res, ACCURACY));
		}

		TEST_METHOD(TestSubtractingDoubles)
		{
			ConsoleManager manager;

			double res = manager.execute("1.1-0.1");
			Assert::IsTrue(roundTo(double(1), ACCURACY) == roundTo(res, ACCURACY));

			res = manager.execute("(1.5)-(1)");
			Assert::IsTrue(roundTo(double(0.5), ACCURACY) == roundTo(res, ACCURACY));

			res = manager.execute("(1.212)-(-1.2)");
			Assert::IsTrue(roundTo(double(2.412), ACCURACY) == roundTo(res, ACCURACY));

			res = manager.execute("5-2.1");
			Assert::IsTrue(roundTo(double(2.9), ACCURACY) == roundTo(res, ACCURACY));

			res = manager.execute("-1-4");
			Assert::IsTrue(roundTo(double(-5), ACCURACY) == roundTo(res, ACCURACY));

			res = manager.execute("+1.9-4");
			Assert::IsTrue(roundTo(double(-2.1), ACCURACY) == roundTo(res, ACCURACY));

			res = manager.execute("-1-(-5.001)");
			Assert::IsTrue(roundTo(double(4.001), ACCURACY) == roundTo(res, ACCURACY));

			res = manager.execute("(-1.25)-(-5.1)");
			Assert::IsTrue(roundTo(double(3.85), ACCURACY) == roundTo(res, ACCURACY));

			res = manager.execute("(+1.3)-(+5)");
			Assert::IsTrue(roundTo(double(-3.7), ACCURACY) == roundTo(res, ACCURACY));
		}

		TEST_METHOD(TestMultiplyDoubles)
		{
			ConsoleManager manager;

			double res = manager.execute("1*1.1");
			Assert::IsTrue(roundTo(double(1.1), ACCURACY) == roundTo(res, ACCURACY));

			res = manager.execute("(1.1)*(1.1)");
			Assert::IsTrue(roundTo(double(1.21), ACCURACY) == roundTo(res, ACCURACY));

			res = manager.execute("(1.5)*(-1.5)");
			Assert::IsTrue(roundTo(double(-2.25), ACCURACY) == roundTo(res, ACCURACY));

			res = manager.execute("5*2.5");
			Assert::IsTrue(roundTo(double(12.5), ACCURACY) == roundTo(res, ACCURACY));

			res = manager.execute("-0.1*4");
			Assert::IsTrue(roundTo(double(-0.4), ACCURACY) == roundTo(res, ACCURACY));

			res = manager.execute("+1.2*4");
			Assert::IsTrue(roundTo(double(4.8), ACCURACY) == roundTo(res, ACCURACY));

			res = manager.execute("-1*(-5.5)");
			Assert::IsTrue(roundTo(double(5.5), ACCURACY) == roundTo(res, ACCURACY));

			res = manager.execute("(-1.01)*(-5)");
			Assert::IsTrue(roundTo(double(5.05), ACCURACY) == roundTo(res, ACCURACY));

			res = manager.execute("(+10.2)*(+5)");
			Assert::IsTrue(roundTo(double(51), ACCURACY) == roundTo(res, ACCURACY));

			res = manager.execute("(+10000)*(+1.0)");
			Assert::IsTrue(roundTo(double(10000), ACCURACY) == roundTo(res, ACCURACY));
		}

		TEST_METHOD(TestDivisionDoubles)
		{
			ConsoleManager manager;

			double res = manager.execute("1.1/1");
			Assert::IsTrue(roundTo(double(1.1), ACCURACY) == roundTo(res, ACCURACY));

			res = manager.execute("(1.2)/(2)");
			Assert::IsTrue(roundTo(double(0.6), ACCURACY) == roundTo(res, ACCURACY));

			res = manager.execute("(2.7)/(-1)");
			Assert::IsTrue(roundTo(double(-2.7), ACCURACY) == roundTo(res, ACCURACY));

			res = manager.execute("5.2/2");
			Assert::IsTrue(roundTo(double(2.6), ACCURACY) == roundTo(res, ACCURACY));

			res = manager.execute("-0.8/0.4");
			Assert::IsTrue(roundTo(double(-2), ACCURACY) == roundTo(res, ACCURACY));

			res = manager.execute("+0.5/4");
			Assert::IsTrue(roundTo(double(0.125), ACCURACY) == roundTo(res, ACCURACY));

			res = manager.execute("-1.1/(-5.5)");
			Assert::IsTrue(roundTo(double(0.2), ACCURACY) == roundTo(res, ACCURACY));

			res = manager.execute("(-11.1)/(-5)");
			Assert::IsTrue(roundTo(double(2.22), ACCURACY) == roundTo(res, ACCURACY));

			res = manager.execute("(+13.5)/(+0.5)");
			Assert::IsTrue(roundTo(double(27), ACCURACY) == roundTo(res, ACCURACY));

			res = manager.execute("(+10000.1)/(+10)");
			Assert::IsTrue(roundTo(double(1000.01), ACCURACY) == roundTo(res, ACCURACY));

			res = manager.execute("(-1.3)//(-0)");
			Assert::IsTrue(NULL == res);

			res = manager.execute("1+(-1.3)/");
			Assert::IsTrue(NULL == res);

			res = manager.execute("(-1.3)^/(-0)");
			Assert::IsTrue(NULL == res);
		}

		TEST_METHOD(TestExponentDoubles)
		{
			ConsoleManager manager;

			double res = manager.execute("0.1^1");
			Assert::IsTrue(roundTo(double(0.1), ACCURACY) == roundTo(res, ACCURACY));

			res = manager.execute("(1)^(0.1)");
			Assert::IsTrue(roundTo(double(1), ACCURACY) == roundTo(res, ACCURACY));

			res = manager.execute("(0.1)^(-0.2)");
			Assert::IsTrue(roundTo(double(1.58489319246), ACCURACY) == roundTo(res, ACCURACY));

			res = manager.execute("5.1^2");
			Assert::IsTrue(roundTo(double(26.01), ACCURACY) == roundTo(res, ACCURACY));

			res = manager.execute("(-1)^(0.4)");
			Assert::IsTrue(NULL == res);

			res = manager.execute("+1.1^4");
			Assert::IsTrue(roundTo(double(1.4641), ACCURACY) == roundTo(res, ACCURACY));

			res = manager.execute("(1.23)^(0)");
			Assert::IsTrue(roundTo(double(1), ACCURACY) == roundTo(res, ACCURACY));

			res = manager.execute("(-1.67457456)^(0)");
			Assert::IsTrue(roundTo(double(1), ACCURACY) == roundTo(res, ACCURACY));

			res = manager.execute("(-1.3)^(-0)");
			Assert::IsTrue(roundTo(double(1), ACCURACY) == roundTo(res, ACCURACY));

			res = manager.execute("(-1.3)^^(-0)");
			Assert::IsTrue(NULL == res);

			res = manager.execute("1+(-1.3)^");
			Assert::IsTrue(NULL == res);

			res = manager.execute("(-1.3)^+(-0)");
			Assert::IsTrue(NULL == res);
		}

		TEST_METHOD(TestParenthesis)
		{
			ConsoleManager manager;

			double res = manager.execute("(1+3)+(4+4)");
			Assert::IsTrue(double(12) == res);

			res = manager.execute("((1-3)*4-(65-(21/5)))");
			Assert::IsTrue(roundTo(double(-68.8), ACCURACY) == roundTo(res, ACCURACY));

			res = manager.execute("((((1-2))))*(1-2)");
			Assert::IsTrue(roundTo(double(1), ACCURACY) == roundTo(res, ACCURACY));

			res = manager.execute("()()()()1+1");
			Assert::IsTrue(roundTo(double(2), ACCURACY) == roundTo(res, ACCURACY));

			res = manager.execute("1+1()()()()");
			Assert::IsTrue(roundTo(double(2), ACCURACY) == roundTo(res, ACCURACY));

			res = manager.execute("()()(1+1)()()");
			Assert::IsTrue(roundTo(double(2), ACCURACY) == roundTo(res, ACCURACY));

			res = manager.execute("(3*3)/(3+3+3)");
			Assert::IsTrue(roundTo(double(1), ACCURACY) == roundTo(res, ACCURACY));

			res = manager.execute("(-3*3)/(3+3+3)");
			Assert::IsTrue(roundTo(double(-1), ACCURACY) == roundTo(res, ACCURACY));

			res = manager.execute("-(-3*3)/(3+3+3)");
			Assert::IsTrue(roundTo(double(1), ACCURACY) == roundTo(res, ACCURACY));

			res = manager.execute("((");
			Assert::IsTrue(NULL == res);

			res = manager.execute("((1+2)");
			Assert::IsTrue(NULL == res);

			res = manager.execute("))(1+45(");
			Assert::IsTrue(NULL == res);
		}

		TEST_METHOD(TestLogFunction)
		{
			ConsoleManager manager;

			double res = manager.execute("log(2,2)");
			Assert::IsTrue(roundTo(double(1), ACCURACY) == roundTo(res, ACCURACY));

			res = manager.execute("log(log(3,27),log(2,512))");
			Assert::IsTrue(roundTo(double(2), ACCURACY) == roundTo(res, ACCURACY));

			res = manager.execute("log(1.1,1.21)*2");
			Assert::IsTrue(roundTo(double(4), ACCURACY) == roundTo(res, ACCURACY));

			res = manager.execute("log(1+1+1*6,8^2)");
			Assert::IsTrue(roundTo(double(2), ACCURACY) == roundTo(res, ACCURACY));

			res = manager.execute("log(9,81)");
			Assert::IsTrue(roundTo(double(2), ACCURACY) == roundTo(res, ACCURACY));

			res = manager.execute("-log(9,81)");
			Assert::IsTrue(roundTo(double(-2), ACCURACY) == roundTo(res, ACCURACY));

			res = manager.execute("-log(9,81)*(-log(9,81))");
			Assert::IsTrue(roundTo(double(4), ACCURACY) == roundTo(res, ACCURACY));

			res = manager.execute("log((3^2)/3+6,121/(11^(1.1/1.1))/11*(9^2))");
			Assert::IsTrue(roundTo(double(2), ACCURACY) == roundTo(res, ACCURACY));

			res = manager.execute("log((3^2)/3+6,121/(11^(1.1/1.1))/11*(9^2)))))");
			Assert::IsTrue(NULL == res);

			res = manager.execute("log(1/3,1/9)");
			Assert::IsTrue(roundTo(double(2), ACCURACY) == roundTo(res, ACCURACY));

			res = manager.execute("log(1/3,1/9)log(1/3,1/9)");
			Assert::IsTrue(roundTo(double(4), ACCURACY) == roundTo(res, ACCURACY));

			res = manager.execute("log(1/3,1/9)-log(1/3,1/9)");
			Assert::IsTrue(roundTo(double(0), ACCURACY) == roundTo(res, ACCURACY));

			res = manager.execute("log(1/3,1/9)/log(1/3,1/9)");
			Assert::IsTrue(roundTo(double(1), ACCURACY) == roundTo(res, ACCURACY));

			res = manager.execute("-log(1/3,1/9)+log(1/3,1/9)");
			Assert::IsTrue(roundTo(double(0), ACCURACY) == roundTo(res, ACCURACY));

			res = manager.execute("log((0.1),(0.01))");
			Assert::IsTrue(roundTo(double(2), ACCURACY) == roundTo(res, ACCURACY));

			res = manager.execute("log((-0.1),(0.01))");
			Assert::IsTrue(NULL == res);

			res = manager.execute("log(1)");
			Assert::IsTrue(NULL == res);

			res = manager.execute("log(1,1)");
			Assert::IsTrue(NULL == res);

			res = manager.execute("log(0,1)");
			Assert::IsTrue(NULL == res);

			res = manager.execute("log(54,-1)");
			Assert::IsTrue(NULL == res);

			res = manager.execute("log(-1,3)");
			Assert::IsTrue(NULL == res);

			res = manager.execute("lgo(1/3,1/9)");
			Assert::IsTrue(NULL == res);
		}

		TEST_METHOD(TestExpForm)
		{
			ConsoleManager manager;

			double res = manager.execute("10E+1-10E+1");
			Assert::IsTrue(double(0) == res);

			res = manager.execute("1E+1 + 1E+2");
			Assert::IsTrue(roundTo(double(110), ACCURACY) == roundTo(res, ACCURACY));

			res = manager.execute("1e+1 + 1E+2");
			Assert::IsTrue(roundTo(double(110), ACCURACY) == roundTo(res, ACCURACY));

			res = manager.execute("1.11E+1-0.1");
			Assert::IsTrue(roundTo(double(11), ACCURACY) == roundTo(res, ACCURACY));

			res = manager.execute("2.21E+1*2");
			Assert::IsTrue(roundTo(double(44.2), ACCURACY) == roundTo(res, ACCURACY));

			res = manager.execute("1.1e+1^2");
			Assert::IsTrue(roundTo(double(121), ACCURACY) == roundTo(res, ACCURACY));

			res = manager.execute("1.1E-1^2");
			Assert::IsTrue(roundTo(double(0.0121), ACCURACY) == roundTo(res, ACCURACY));

			res = manager.execute("1.1E-1^2 - (1^2)");
			Assert::IsTrue(roundTo(double(-0.9879), ACCURACY) == roundTo(res, ACCURACY));

			res = manager.execute("(-1.11E-1)-0.1");
			Assert::IsTrue(roundTo(double(-0.211), ACCURACY) == roundTo(res, ACCURACY));

			res = manager.execute("1+10E1");
			Assert::IsTrue(NULL == res);

			res = manager.execute("1+10E");
			Assert::IsTrue(NULL == res);

		}

		TEST_METHOD(TestUnknownSymbols)
		{
			ConsoleManager manager;

			double res = manager.execute("abcde");
			Assert::IsTrue(NULL == res);

			res = manager.execute("1+10E+1eee");
			Assert::IsTrue(NULL == res);

			res = manager.execute("f1+1");
			Assert::IsTrue(NULL == res);

			res = manager.execute("(f)-432");
			Assert::IsTrue(NULL == res);

			res = manager.execute("45*(2+1)_");
			Assert::IsTrue(NULL == res);
		}

		TEST_METHOD(TestBigNumbers)
		{
			ConsoleManager manager;

			double res = manager.execute("4294967295 + 1");
			Assert::IsTrue(double(4294967296) == res);

			res = manager.execute("9223372036854775807 + 1");
			Assert::IsTrue(double(9223372036854775808) == res);
		}

		TEST_METHOD(TestComplex)
		{
			ConsoleManager manager;

			double res = manager.execute("23.5435   +(43. 21^1.1+(25   /   54   +   5 ) ) + log(log(3,9),8) - 1E-1");
			Assert::IsTrue(roundTo(double(94.877767868377403), ACCURACY) == roundTo(res, ACCURACY));
		}
	};
}
