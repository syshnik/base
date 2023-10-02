#include "stdafx.h"
#include "../cod_base/atable.h"


//#undef new#include <new>
//#define NEWCELL(X) (X)->ACell::ACell()
#define NEWCELL(X) new (X) ACell
#define DELCELL(X) (X)->ACell::~ACell()
#define NEWCOL(X) new (X)  AColumn
#define DELCOL(X) (X)->AColumn::~AColumn()

//namespace NSMY {namespace NSBase {

ATable::ATable(void){
	//NSMY::NSMem::StaticMemPoint::Create((void **)&_yp);
	//NSMY::NSMem::StaticMemPoint::Create((void **)&_sp);
	//TemplateMassiv<AColumn>::Constructor(&_sp);
	_nst=_nstr=0;
}
ATable::~ATable(void){
	Clear();
	//NSMY::NSMem::StaticMemPoint::Destroy((void **)&_yp);
	//NSMY::NSMem::StaticMemPoint::Destroy((void **)&_sp);
	//TemplateMassiv<AColumn>::Destructor(&_sp);
}

USI ATable::CountColumns() {
	TA(_nst == _sm.Count());
	return _nst;
}
USI ATable::CountStrings() {
	if(_nst!=0) TA(_nstr == _ym.Count()/CountColumns());
	return _nstr;
}


AColumn & ATable::GetColumnInfo(int nomer) {
	//TA(nomer < this->CountColumns());	return _sp[nomer];
	return GetColumnInfo((USI) nomer) ;
}
ACell & ATable::GetCell(int stolbik, USI zapis) {
//	TA( stolbik < this->CountColumns() && zapis < this->CountStrings());
	return GetCell((USI) stolbik, zapis) ;
}

AColumn & ATable::GetColumnInfo(USI nomer) {
	//TA(nomer < this->CountColumns());	return _sp[nomer];
	return _sm[nomer];
}

ACell & ATable::GetCell(USI stolbik, USI zapis) {
	TA( stolbik < this->CountColumns() && zapis < this->CountStrings());
	return _ym[CountColumns()*zapis+stolbik];
}

AColumn & ATable::GetColumnInfo(char * name) {
	return this->GetColumnInfo(this->GetColumnNumber(name));
}

ACell & ATable::GetCell(char * name, USI zapis) {
	return this->GetCell(this->GetColumnNumber(name), zapis);
}

USI ATable::GetColumnNumber(char * name) {
	USI n;
	for(n=0; n<this->CountColumns(); n++) if(this->_sm[n].name == name) break;
	return n;
}


void ATable::Clear() {
	this->DeleteStrings(0, this->CountStrings());
	this->DeleteColumns(0, this->CountColumns());
}
void ATable::NewColumns(USI x, USI count) {
	USI h=this->CountStrings(), neww=this->CountColumns()+count, oldw=this->CountColumns();
	USI right=oldw-x, left=x;
	//добавление памяти
//	NSMem::StaticMemPoint::SetSize((void **)&_sp, neww*sizeof(*_sp));
	//NSMem::StaticMemPoint::SetSize((void **)&_yp, neww*h*sizeof(*_yp));
	_ym.New(_ym.Count(), h*count);
	//сдвиг	//конструктор
	USI ot=h*oldw, ku=h*neww;
	for( ; ot; ) {
		USI w;
		for( w=right; w>0; w--, ot--, ku--) NoteCpy(_ym[ku-1], _ym[ot-1]);
		for(w=neww-(left+right); w>0; w--, ku--) NEWCELL(_ym.GetPoint()+ku-1);
		for(w=left; w>0; w--, ot--, ku--) NoteCpy(_ym[ku-1], _ym[ot-1]);
	}
	/*
	
	  
	ot=oldw;
	ku=neww;
	{
		for(USI w=right; w>0; w--, ot--, ku--) NoteCpy(_sp[ku-1], _sp[ot-1]);
		for(w=neww-(left+right); w>0; w--, ku--) NEWCOL(_sp+ku-1);
		for(w=left; w>0; w--, ot--, ku--) NoteCpy(_sp[ku-1], _sp[ot-1]);
	}*/
	//TemplateMassiv<AColumn>::New(&_sp, x, count);
	_sm.New(x, count);
	{
		for(USI n=count, ku=x; n; n--, ku++) NEWCOL(_sm.GetPoint()+ku);
	}
	_nst+=count;
}
void ATable::DeleteColumns(USI x, USI count) {
	USI h=this->CountStrings(), neww=this->CountColumns()-count, oldw=this->CountColumns();
	USI right=neww-x, left=x;
	//сдвиг	//деструктор
	USI ot=0, ku=0;
	for( ; ot<h*oldw; ) {
		USI w;
		for(w=left; w>0; w--, ot++, ku++) NoteCpy(_ym[ku], _ym[ot]);
		for(w=oldw-(left+right); w>0; w--, ot++) DELCELL(_ym.GetPoint()+ot);
		for(w=right; w>0; w--, ot++, ku++) NoteCpy(_ym[ku], _ym[ot]);
	}
	_ym.Delete(neww*h, count*h);
	{
		for(USI n=count, ku=x; n; n--, ku++) DELCOL(_sm.GetPoint()+ku);
	}
	_sm.Delete(x, count);
	_nst-=count;
}
void ATable::NewStrings(USI y, USI count) {
	USI leftsik=y*CountColumns(), rightsik=(CountStrings()-y)*CountColumns(), 
		addsik=count*CountColumns();
	//память	//сдвиг
	_ym.New(leftsik, addsik);
	//USI ku=leftsik+addsik+rightsik, ot=leftsik+rightsik;
	//for(USI n1=rightsik; n1; n1--, ku--, ot--) NoteCpy(_yp[ku-1], _yp[ot-1]);
	//конструктор
	for(USI n1=0; n1<addsik; n1++) NEWCELL(_ym.GetPoint()+leftsik+n1);
	_nstr+=count;
}
void ATable::DeleteStrings(USI y, USI count) {
	USI leftsik=y*CountColumns(), rightsik=(CountStrings()-y-count)*CountColumns(), 
		delsik=count*CountColumns(), ot, ku, n1;
	//деструктор
	for(n1=delsik, ot=leftsik; n1; n1--, ot++) DELCELL(_ym.GetPoint()+ot);
	//ku=leftsik, ot=leftsik+delsik;
	//for(n1=rightsik; n1; n1--, ku++, ot++) NoteCpy(_yp[ku], _yp[ot]);
	//NSMem::StaticMemPoint::SetSize((void **)&_yp, (leftsik+rightsik)*sizeof(*_yp));
	//память	//сдвиг
	_ym.Delete(leftsik, delsik);
	_nstr-=count;
}

void ATable::CreateCopyFromTable(ATable * tb, USI FirstString, USI CountString) {
	if(CountString == MAXUSI) CountString=tb->CountStrings()-FirstString;
	Clear();
	this->NewColumns(0, tb->CountColumns());
	this->NewStrings(0, CountString);
	for(USI nst=0; nst<tb->CountColumns(); nst++) {
		this->GetColumnInfo(nst)=tb->GetColumnInfo(nst);
		for(USI nstr=0; nstr<CountString; nstr++) {
			this->GetCell(nst, nstr)=tb->GetCell(nst, nstr+FirstString);
		}
	}
}

USI ATable::FindInColumn(char * string, USI column, USI Adress, USI Count) {
	if(Count  == MAXUSI) Count=this->CountStrings()-Adress;
	USI nstr;
	for(nstr=Adress; nstr < Adress+Count; nstr++) 
		if(this->GetCell(column, nstr).str == string) break;
	return nstr;
}
USI ATable::FindInColumn(char * string, char * column, USI Adress, USI Count) {
	return FindInColumn(string, this->GetColumnNumber(column), Adress, Count);
}
ATable & ATable::operator =(ATable & tb) {
	this->CreateCopyFromTable(&tb);
	return *this;
}

void ATable::Sort(USI NumberColumn, USI FirstRow, USI CountRows) 
{
	TA(0);//сравнение ячеек н реализовано
/*	USI n;
	//сортировка
	for(n=FirstRow+1; n < FirstRow+CountRows; n++) {
		bool find=false;
		if(GetCell(NumberColumn, n-1).str < GetCell(NumberColumn, n).str) {
			find=true;
			for(USI nst=0; nst<this->CountColumns(); nst++) 
				obmen(GetCell(NumberColumn, n-1), GetCell(NumberColumn, n));
		}
	}
	//ныряем
	USI border=FirstRow;
	for(n=FirstRow+1; n < FirstRow+CountRows; n++) {
		if(GetCell(NumberColumn, n-1).str != GetCell(NumberColumn, n).str) {
			Sort(NumberColumn, border, n-border);
			border=n;
		}
	}*/
}
void ATable::TestOrder(USI NumberColumn, USI FirstRow, USI CountRows) 
{
	TA(0);//сравнение ячеек н реализовано
/*	USI n;
	//проверка
	for(n=FirstRow+1; n < FirstRow+CountRows; n++) {
		TA(GetCell(NumberColumn, n-1).str >= GetCell(NumberColumn, n).str);
	}
	//ныряем
	for(n=FirstRow+1, border=FirstRow; n < FirstRow+CountRows; n++) {
		if(GetCell(NumberColumn, n-1).str != GetCell(NumberColumn, n).str) {
			TestOrder(NumberColumn, border, n-border);
			border=n;
		}
	}*/
}

S1 ACell::s1() { return NSMY::NSStr::strtoi1((char *)str, NULL); }
S2 ACell::s2() { return NSMY::NSStr::strtoi2((char *)str, NULL); }
S4 ACell::s4() { return NSMY::NSStr::strtoi4((char *)str, NULL); }
S8 ACell::s8() { return NSMY::NSStr::strtoi8((char *)str, NULL); }
F4 ACell::f4() { return NSMY::NSStr::strtof4((char *)str, NULL); }
F8 ACell::f8() { return NSMY::NSStr::strtof8((char *)str, NULL); }
