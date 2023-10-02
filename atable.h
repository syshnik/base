/*Сайт "Заводила" © Сафаров Олег Айратович 2014 г. инн 027304982940*/
#pragma once
#ifndef	_pragma_once_579071854455000
#define	_pragma_once_579071854455000
namespace NSMY {
namespace NSBase {

class   		EXPORT_OR_IMPPORT			ACell {
public:
	cfstr str;
	S1 s1();
	S2 s2();
	S4 s4();
	S8 s8();
	F4 f4();
	F8 f8();
};
class   		EXPORT_OR_IMPPORT			AColumn {
public:
	NSMY::NSStr::cfstr name;
};
class   		EXPORT_OR_IMPPORT			ATable
{
private:
	USI _nst, _nstr;
	//MemPoint _ym, _sm;
	//ACell *_yp;
	//AColumn * _sp;
	TemplateMassivNotes<ACell> _ym;
	TemplateMassivNotes<AColumn> _sm;
public:
	ATable(void);
	~ATable(void);
	void NewColumns(USI x, USI count);
	void DeleteColumns(USI x, USI count);
	void NewStrings(USI y, USI count);
	void DeleteStrings(USI y, USI count);
	USI CountColumns();
	USI CountStrings();
	AColumn & GetColumnInfo(int nomer);
	AColumn & GetColumnInfo(USI nomer);
	ACell & GetCell(int stolbik, USI zapis);
	ACell & GetCell(USI stolbik, USI zapis);
	AColumn & GetColumnInfo(char * name);
	ACell & GetCell(char * name, USI zapis);
	USI GetColumnNumber(char * name);
	void Clear();
	void CreateCopyFromTable(ATable * tb, USI FirstString=0, USI CountString=MAXUSI);
	ATable & operator =(ATable & tb);
	USI FindInColumn(char * string, USI column, USI Adress=0, USI Count=MAXUSI);
	USI FindInColumn(char * string, char * column, USI Adress=0, USI Count=MAXUSI);
	void Sort(USI NumberColumn, USI FirstRow, USI CountRows);
	void TestOrder(USI NumberColumn, USI FirstRow, USI CountRows);
#ifdef TEST_D
	void FillDebugWriteTable();
	void FillTestATable();
#endif
};

class 	EXPORT_OR_IMPPORT	TableMassiv;
}//namespace NSMY {
}//namespace NSBase {
class 	EXPORT_OR_IMPPORT	NSMY::NSBase::TableMassiv : public NSMY::NSMem::TemplateMassivNotes<ATable> {
public:
	void New(USI adr, USI sik) {
		TemplateMassivNotes<ATable>::New( adr,  sik);
		for(USI n=adr; n<adr+sik; n++) {
			ATable * tbp1=new(&((*this)[n])) ATable;
			//(*this)[n].ATable::ATable();
		}
	};
	void Delete(USI adr, USI sik) {
		for(USI n=adr; n<adr+sik; n++) (*this)[n].~ATable();
		TemplateMassivNotes<ATable>::Delete( adr,  sik);
	};
	~TableMassiv() {
		Delete(0, Count());
	};
};
using namespace NSMY::NSBase;
#endif //pragma once