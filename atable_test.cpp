#include "stdafx.h"
#include "../cod_base/atable.h"


#ifdef TEST_D






static cfstr GetTestColumnText(USI nst) {
	cfstr ret("Column ");
	ret << (S4)nst;
	return ret;
}
static cfstr GetTestStringText(USI nst, USI nzap) {
	cfstr ret("Column ");
	ret << nst << "String" << (S4)nzap;
	return ret;
}
static void TestTable(ATable & tb, USI xmove, USI ymove, TRect<USI> r) {
	for(USI x=r.x; x<r.x+r.xm; x++) {
		A(tb.GetColumnInfo(x).name == GetTestColumnText(x+xmove));
		for(USI y=r.y; y<r.y+r.ym; y++) {
			A(tb.GetCell(x, y).str == GetTestStringText(x+xmove, y+ymove));
		}
	}
}
static void AddColumn(ATable & tb, USI nst, USI sik) {
	tb.NewColumns(nst, sik);
	TestTable(tb, 0, 0, TRect<USI>(0, 0, nst, tb.CountStrings()));
	TestTable(tb, -sik, 0, TRect<USI>(nst+sik, 0, tb.CountColumns()-(nst+sik), tb.CountStrings()));
	tb.FillDebugWriteTable();
}
static void DelColumn(ATable & tb, USI nst, USI sik) {
	tb.DeleteColumns(nst, sik);
	TestTable(tb, 0, 0, TRect<USI>(0, 0, nst, tb.CountStrings()));
	TestTable(tb, sik, 0, TRect<USI>(nst, 0, tb.CountColumns()-nst, tb.CountStrings()));
	tb.FillDebugWriteTable();
}
static void AddString(ATable & tb, USI nstr, USI sik) {
	tb.NewStrings(nstr, sik);
	TestTable(tb, 0, 0, TRect<USI>(0, 0, tb.CountColumns(), nstr));
	TestTable(tb, 0, -sik, TRect<USI>(0, nstr+sik, tb.CountColumns(), tb.CountStrings()-(nstr+sik)));
	tb.FillDebugWriteTable();
}
static void DelString(ATable & tb, USI nstr, USI sik) {
	tb.DeleteStrings(nstr, sik);
	TestTable(tb, 0, 0, TRect<USI>(0, 0, tb.CountColumns(), nstr));
	TestTable(tb, 0, sik, TRect<USI>(0, nstr, tb.CountColumns(), tb.CountStrings()-nstr));
	tb.FillDebugWriteTable();
}

//--------------------------------------------------------------------------------------------------

void ATable::FillDebugWriteTable() {
	for(USI x=0; x<CountColumns(); x++) {
		GetColumnInfo(x).name = GetTestColumnText(x);
		for(USI y=0; y<CountStrings(); y++) {
			GetCell(x, y).str = GetTestStringText(x, y);
		}
	}
}
static ATable * stp;
static USI next=0;
void ATable::FillTestATable() {
	const USI maxnst=20, maxnstr=20, siktest=100;
	for(;;) {
		ATable tb;

		stp=&tb;
		for(USI n=0; n<siktest; n++, next++) {
			USI nst=Rand()%(tb.CountColumns()+1),
				nstr=Rand()%(tb.CountStrings()+1),
				addnst=Rand()%(maxnst+1), 
				delnst=Rand()%(tb.CountColumns()-nst+1),
				addnstr=Rand()%(maxnstr+1),
				delnstr=Rand()%(tb.CountStrings()-nstr+1);
			if(next==9) {
				USI hhh=0;
			}
			if(tb.CountColumns() < maxnst && Rand()%2) {
				AddColumn(tb, nst, addnst);
				continue;
			}
			if(tb.CountColumns() > 0 && Rand()%2) {
				DelColumn(tb, nst, delnst);
				continue;
			}
			if(tb.CountStrings() < maxnstr && Rand()%2) {
				AddString(tb, nstr, addnstr);
				continue;
			}
			if(tb.CountStrings() > 0 && Rand()%2) {
				DelString(tb, nstr, delnstr);
				continue;
			}
		}
	}
}


#endif
