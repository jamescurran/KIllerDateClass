#include "datecl.h"
#include <malloc.h>
#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::flush;
using std::string;
using std::ostream;


// Note:	Looking for memory leaks in Windows NT cannot be done by
//			checking the available memory.  The of available memory,
//			both the physical and virtual, is shared by all of the
//			running processes.
//			
#if defined (_MSC_VER) && !defined(_WIN32)
	#define MEM_LEFT	_memavl()
#elif defined(__BORLANDC__) || defined(__TURBOC__)
	#define MEM_LEFT	0L //farcoreleft()
#else
	#define MEM_LEFT	0L
#endif

////////////////////////////////////////////////////////////
//	main for testing purposes only...
////////////////////////////////////////////////////////////

void test()
{
	cout << " Date Class 5.0 Demo \n\n";

	// Various versions of the constructors
	// and various output
	Date x(10,20,1962);
	cout << x.formatDate(Date::FULL) << "\n";

	// constructor with a string, just printing the day of the week
	Date y="8/8/1988";
	cout << y.formatDate(Date::DAY) << "\n";

	// constructor with a Julian
	Date z( 2450000L );
	cout << z.formatDate(Date::FULL) << '\n';

	// using date addition and subtraction
	Date a = x + 10;
	cout << a.formatDate(Date::FULL) << '\n';
	a = a - 25;
	cout << a.formatDate(Date::EUROPEAN) << '\n';

	//using subtraction of two date objects
	Date a1 = "7/13/1991";
	Date a2 = a1 + 14;
	cout << (a1-a2) << "\n";
	cout << (a2+=10) << "\n";

	a1++;
	cout << "Tomorrow= " << a1.formatDate(Date::FULL) << "\n";

	cout << "a1 (7-14-91) < a2 ("<< a2<< ")? ==> " << ((a1 < a2) ? "TRUE" : "FALSE") << "\n";
	cout << "a1 (7-14-91) > a2 ("<< a2<< ")? ==> " << ((a1 > a2) ? "TRUE" : "FALSE") << "\n";

	cout << "a1 (7-14-91) < 8-01-91 ? ==> " << ((a1 < (Date)"08/01/1991") ? "TRUE" : "FALSE") << "\n";
	cout << "a1 (7-14-91) > 8-01-91 ? ==> " << ((a1 > (Date)"08/01/1991") ? "TRUE" : "FALSE") << "\n";
	cout << "a1 (7-14-91)== 7-14-91 ? ==> " << ((a1==(Date)"07/14/1991") ? "TRUE" : "FALSE") << "\n";
	Date a3 = a1;
	a1.formatDate(Date::MDY);

	cout << "a1 (" << a1 << ")== a3 (" << a3 << ") ? ==> " << ((a1==a3) ? "TRUE" : "FALSE") << "\n";
	Date a4 = a1;
	++a4;
	cout << "a1 ("<< a1<<")== a4 (" << a4 << ") ? ==> " << ((a1==a4) ? "TRUE" : "FALSE") << "\n";

	Date a5 = "today";
	cout << "Today is: " << a5 << "\n";
	a4 = "Today";
	cout << "Today (a4) is: " << a4 << "\n";

	cout << "Today + 4 is: " << (a4+=4) << "\n";
	a4 = "Today";
	cout << "Today - 4 is: " << (a4-=4) << "\n";
	cout << "=========== Leap Year Test ===========\n";
	a1 = "1/15/1992";
	cout << a1.formatDate(Date::FULL) << "\t" << ((a1.isLeapYear()) ? "Leap" : "non-Leap");
	cout << "\t" << "day of year:  " << a1.DOY() << "\n";

	a1 = "2/16/1993";
	cout << a1.formatDate(Date::FULL) << "\t" << ((a1.isLeapYear()) ? "Leap" : "non-Leap");
	cout << "\t" << "day of year:  " << a1.DOY() << "\n";

	DOSDATE_T b0 = {15,02,1991,1};
	Date b1 = b0;
	cout << "=========== eom test ==============\n";
	cout << "b1.eom() (s/b 2/28/91) ==> " << b1.eom() << "\n";

// #if !defined(_WIN32)	// This really doesn't work on Windows NT.
	cout << "================== getDate test =====================\n";
	DOSDATE_T ds = a1.getDate();
	cout << "a1.getDate()  (s/b 2/16/1993) ==> " << ds << "\n";
// #endif

	cout << "================== string assignment test ====================\n";
	const string date_string = a1;
	cout << "a1 as a string (s/b 2/16/1993) ==> " << date_string << "\n";

	cout << "================== setFormat test ============================\n";
	Date::setFormat(Date::FULL);
	cout << "a1 (s/b FULL format) ==> " << a1 << "\n";
	Date::setFormat(Date::EUROPEAN);
	cout << "a1 (s/b EUROPEAN format) ==> " << a1 << "\n";
	Date::setFormat(Date::COLLATE);
	cout << "a1 (s/b COLLATE format) ==> " << a1 << "\n";


	cout << "================== setOption test ============================\n";
	cout << "Date abbreviation ON\n";
	Date::setOption(Date::DATE_ABBR);
	Date::setFormat(Date::MONTH);
	cout << "a1 (s/b MONTH format) ==> " << a1 << "\n";
	Date::setFormat(Date::DAY);
	cout << "a1 (s/b DAY format) ==> " << a1 << "\n";
	Date::setFormat(Date::FULL);
	cout << "a1 (s/b FULL format) ==> " << a1 << "\n";
	Date::setFormat(Date::EUROPEAN);
	cout << "a1 (s/b EUROPEAN format) ==> " << a1 << "\n";
	cout << "Century suppression ON\n";
	Date::setOption(Date::NO_CENTURY);
	Date::setFormat(Date::MDY);
	cout << "a1 (s/b MDY format) ==> " << a1 << "\n";
	cout << "Century suppression OFF\n";
	Date::setOption(Date::NO_CENTURY,Date::OFF);
	cout << "a1 (s/b MDY format) ==> " << a1 << "\n";
	cout << "Century suppression ON\n";
	Date::setOption(Date::NO_CENTURY);
	cout << "a1 (s/b MDY format) ==> " << a1 << "\n";
	Date::setFormat(Date::FULL);
	cout << "a1 (s/b FULL format) ==> " << a1 << "\n";
	Date::setOption(Date::DATE_ABBR,Date::OFF);
	cout << "Century suppression OFF\n";
	Date::setOption(Date::NO_CENTURY,Date::OFF);

	cout << "\n=============== Version 4.0 Enhancement Test =================\n";
	
	Date v4("11/26/1966");
	cout << "\n---------- Set Stuff -----------\n";
	cout << "First, 'Set' to today..." << "\n";
	cout << "Before 'Set' => " << v4 << "\n";
	cout << "After  'Set' => " << v4.Set() << "\n\n";

	cout << "Set to 11/26/66 => " << v4.Set(11,26,1966) << "\n";
	cout << "Current Julian  => " << v4.julDate() << "\n";
	cout << "Set to Julian 2450000L => " << v4.Set(2450000L) << "\n";
	cout << "See! => " << v4.julDate() << "\n";

	cout << "---------- Add Stuff -----------\n";
	cout << "Start => " << v4.Set() << "\n";
	cout << "Add  4 Weeks  => " << v4.AddWeeks(4)    << "\n";
	cout << "Sub 52 Weeks  => " << v4.AddWeeks(-52)  << "\n";
	cout << "Add 21 Months => " << v4.AddMonths(21)  << "\n";
	cout << "Sub 15 Months => " << v4.AddMonths(-15) << "\n";
	cout << "Add  2 Years  => " << v4.AddYears(2)    << "\n";

	cout << flush;	

// TML
	cout << "Set to 08/31/93 => " << v4.Set(8,31,1993) << endl;
	cout << "Add  6 Months => " << v4.AddMonths(6)  << endl;

	cout << "---------- Misc Stuff -----------\n";
	cout << "The date aboves' day of the month is => " << v4.Day() << endl;
	cout << "There are " << v4.DaysInMonth() << " days in this month.\n";
	cout << "The first day of this month lands on " << v4.FirstDOM() << endl;
	cout << "This day happens to be " << v4.CDOW() << endl;
	cout << "the " << v4.NDOW() << " day of the week," << endl;
	cout << "on the " << v4.WOY() << " week of the year," << endl;
	cout << "on the " << v4.WOM() << " week of the month, " << endl;
	cout << "(which is " << v4.CMonth() << ")\n";
	cout << "the "<< v4.NMonth() << "nth month in the year.\n";
	cout << "The year alone is " << v4.NYear4() << endl;

	cout << "---------- First and Last Stuff -----------\n";
	v4.Set();
	cout << "The first date of this month is " << v4.BOM() << endl;
	cout << "The last date of this month is " << v4.EOM() << endl;
	cout << "The first date of this year is " << v4.BOY() << endl;
	cout << "The last date of this year is " << v4.EOY() << endl;
	cout << endl;

	cout << "\n=============== Version 4.2 Enhancement Test =================\n";
	// TML - Memory test
	cout << "*** Starting Memory " << (unsigned long) MEM_LEFT << "\n";

	Date *d1 = new Date("04/13/1967");
	cout << "*d1  = " << d1->formatDate(Date::FULL) << "\n\n";
	
	Date 	D2 = "7/4/1776";
	int		I1 = 4;

	D2.setFormat(Date::FULL);

	cout << "Before: I1 = " << I1 << ",  D2 = " << D2 << endl;
	cout << "---------- Postfix '++' test -----------\n";
	cout << "Test : I1++ = " << I1++ << ",  D2++ = " << D2++ << endl;
	cout << "After: I1   = " << I1 << ",  D2   = " << D2 << endl;

	cout << "---------- Prefix '++' test -----------\n";
	cout << "Test : ++I1 = " << ++I1 << ",  ++D2 = " << ++D2 << endl;
	cout << "After:   I1 = " << I1 << ",    D2 = " << D2 << endl;

	cout << "---------- Postfix '--' test -----------\n";
	cout << "Test : I1-- = " << I1-- << ",  D2-- = " << D2-- << endl; 
	cout << "After: I1   = " << I1 << ",  D2   = " << D2 << endl;

	cout << "---------- Prefix '--' test -----------\n";
	cout << "Test : --I1 = " << --I1 << ",  --D2 = " << --D2 << endl;
	cout << "After:   I1 = " << I1 << ",    D2 = " << D2 << endl;


	cout << "---------- Testing the () operator -----------\n";
	Date *d2=new Date;
	cout << "d2's initial value: " << *d2 << "\n";
	cout << "d1's current's buf: " << *d1 << "\n";

	d2->Set();
	cout << "d2's value after 'Set()': " << *d2 << "\n";

	delete d2;
	delete d1;

	cout << "\n=============== Version 4.3 Enhancement Test =================\n";
	cout << "-------------- Testing BCE dates -------------\n";
	Date d4="1/1/0";

	cout << "D4 (1/1/0)       = " << d4 << "\n";
	cout << "D4 - 150 years   = " << d4.AddYears(-150) << "\n";
	cout << "D4 + 150 years   = " << d4.AddYears(150) << "\n";

	cout << "--------- Testing String Assignment ----------\n";

	d4 = "23 March 1993";
	d4.setFormat(Date::EUROPEAN);
	cout << "EUROPEAN         : " << d4 << "\n";

	d4 = "3/23/1993";
	d4.setFormat(Date::MDY);
	cout << "MDY              : " << d4 << "\n";

	d4 = "Tuesday, March 23, 1993";
	d4.setFormat(Date::FULL);
	cout << "FULL             : " << d4 << "\n";

	d4 = "Tue, Mar 23, 1993";
	d4.setOption(Date::DATE_ABBR);
	cout << "FULL,ABBR.       : " << d4 << "\n";
	cout << "\n";
	d4.setOption(Date::DATE_ABBR, Date::OFF);

	d4 = "19930323";
	d4.setFormat(Date::COLLATE);
	cout << "COLLATE         : " << d4 << "\n";


	d4 = "23 March 1993 B.C.E.";
	d4.setFormat(Date::EUROPEAN);
	cout << "EUROPEAN   B.C.E.: " << d4 << "\n";

	d4 = "Tuesday, March 23, 1993 B.C.E.";
	d4.setFormat(Date::FULL);
	cout << "FULL       B.C.E.: " << d4 << "\n";

	d4 = "Tue, Mar 23, 1993 B.C.E.";
	d4.setOption(Date::DATE_ABBR);
	cout << "FULL,ABBR. B.C.E.: " << d4 << "\n";
	cout << "\n\n";

	cout << "\n=============== Version 5.0 Enhancement Test =================\n\n";
			   
	cout << "Missing year test : Set d4 = \"7/4\";\n";
	d4 = "7/4";
	cout << "This should be 7/4/1993 ==>" << d4 << endl;
	cout << "The Julian date for that is " << d4.julDate() << endl;
	
			   
	cout << "2-digit year test : Set d4 =\"7/4/76\";\n";
	d4 ="7/4/76";
	cout << "This should be 7/4/1976 ==>" << d4 << endl;

	cout << "Dot-date test : Set d4 =\".\";\n";
	d4 = ".";
	cout << "This should be today ==>" << d4 << endl;
	
	int	nYear = d4.NYear4();
	
	cout << "Holiday tests\n";
	cout << "This year  : \n";
						
	cout << "NewYearsDay(nYear)         == " << Date::NewYearsDay(nYear) << '\n';	
	cout << "PresidentsDay(nYear)       == " << Date::PresidentsDay(nYear) << '\n';
	cout << "ValentinesDay(nYear)       == " << Date::ValentinesDay(nYear)	<< '\n';
	cout << "StPatricksDay(nYear)       == " << Date::StPatricksDay(nYear)	<< '\n';
	cout << "MothersDay(nYear)          == " << Date::MothersDay(nYear)	<< '\n';
	cout << "MemorialDay(nYear)         == " << Date::MemorialDay(nYear)	<< '\n';
	cout << "FlagDay(nYear)             == " << Date::FlagDay(nYear)		<< '\n';
	cout << "FathersDay(nYear)          == " << Date::FathersDay(nYear)	<< '\n';
	cout << "CanadaDay(nYear)           == " << Date::CanadaDay(nYear)		<< '\n';
	cout << "IndependenceDay(nYear)     == " << Date::IndependenceDay(nYear)<< '\n';
	cout << "BastilleDay(nYear)         == " << Date::BastilleDay(nYear)	<< '\n';
	cout << "LaborDay(nYear)            == " << Date::LaborDay(nYear)		<< '\n';
	cout << "VeteranDay(nYear)          == " << Date::VeteransDay(nYear)	<< '\n';
	cout << "ThanksgivingDay(nYear)     == " << Date::ThanksgivingDay(nYear)<< '\n';
	cout << "ChristmasDay(nYear)        == " << Date::ChristmasDay(nYear)	<< '\n';

	Date d5= Date(0,Date::SATURDAY,Date::SEPTEMBER,nYear);
	cout << "\nThe Last Saturday in September is : " << d5 << '\n';

	cout << "\n=============== Wife test. (Just to make her happy) =================\n\n";
	Date bday;
	Date::setOption(Date::DATE_ABBR, Date::OFF);
	cout << "Raymond was born on "   << Date("7/11/1961").formatDate(Date::FULL) << '\n';
	cout << "Catherine was born on " << Date("8/24/63"  ).formatDate(Date::FULL) << '\n';
	cout << "Danielle was born on "  << Date("8/5/1982" ).formatDate(Date::FULL) << '\n';
	cout << "Joseph was born on "    << Date("8/15/1984").formatDate(Date::FULL) << '\n';
	cout << "Nicole was born on "    << Date("9/18/1986").formatDate(Date::FULL) << '\n';
	cout << "Benjamin was born on "  << Date("4/25/1988").formatDate(Date::FULL) << '\n';

#if !defined(_WIN32)
	cout << "*** Ending Memory " << (unsigned long) MEM_LEFT << "\n\n";
#endif
}


int main()
	{

	for (int i = 1; i < 2; i++)
		{
#if !defined(_WIN32)
		unsigned long t1, t2;
		cout << "*** Starting Program Memory " ;
		cout << (t1=(unsigned long) MEM_LEFT) << "\n";
#endif
		test();
#if !defined(_WIN32)
		cout << "*** Ending Program Memory ";
		cout << (t2=(unsigned long) MEM_LEFT) << "\n";

		cout << "\nProgram Memory Difference: " << (long)(t2 - t1) << "\n\n\n\n";
#endif
		}
	return(0);
	};
