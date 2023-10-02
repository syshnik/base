#include "stdafx.h"

#ifdef VNET_COMPIL936
#ifdef MACROS_MSSQL_BD
#define INITGUID
#define DBINITCONSTANTS
#include "../cod_base/oledb.h" // OLE DB файлы
#include "../cod_base/Sqloledb.h"
#include "../cod_base/oledberr.h" 
#include "../cod_base/afxoledb.h"
#include "../cod_base/afxdb.h"
#define RSTYPE 	CCommand<CDynamicStringAccessor, CRowset, CMultipleResults>
#define SS CSession

char * vremsdghkjhdresesdrkjljeshjk = "___time257988664434365808987653435465___";
#if TEST_V
#if TEST
#endif
#endif
//DataBase
void TestABase() {
	NSMY::NSBase::ATable tb;
	NSMY::NSDebug::RunTime rt;
	rt.init();
	for (int n1 = 0; n1<100; n1++) {
		NSBase::ABase::MakeCommand("delete from dbo.t2");
		NSBase::ABase::MakeCommand("insert into t2 (c1, c2) values ('', 'ppp')");
		NSBase::ABase::WriteTable(&tb, "select *  from t2");
	}
	rt.srez();
	rt.srez();
}

static void order(HRESULT par) {
	if (par != S_OK) {
		int nnnnnnn;
		nnnnnnn = 0;
		RELIZ	//ПРОСЛЕДИТЬ
				//NSMY::NSSmall::iskluchilka("Ошибка работы \"COM\" объекта");
	}
}
static void StaticMakeCommand(char * str, CDataSource & ds, SS & session) {
	CCommand<CNoAccessor, CNoRowset> cmd;
	order(cmd.Open(session, str));
	cmd.Close();

}
static void StaticWriteTable(NSBase::ATable * tb, RSTYPE & Rs, CDataSource & ds, SS & session)
{
	//делаем столбики
	tb->NewColumns(0, Rs.GetColumnCount());
	for (DBORDINAL nst = 1; nst <= Rs.GetColumnCount(); nst++) {
		NSBase::AColumn & st = tb->GetColumnInfo(nst - 1);
		CString str;
		str = Rs.GetColumnName(nst);
		st.name = str.GetBuffer();
	}

	//делаем записи
	if (Rs.MoveFirst() == S_OK) {
		USI nzap = 0;
		for (HRESULT hr = S_OK; hr == S_OK; hr = Rs.MoveNext(), nzap++) {
			tb->NewStrings(tb->CountStrings(), 1);
			for (DBORDINAL nst = 1; nst <= Rs.GetColumnCount(); nst++) {

				cfstr str = Rs.GetString(nst);;
				tb->GetCell(nst - 1, nzap).str = str;
			}
		}//for(HRESULT hr=S_OK; hr == S_OK; hr = Rs.MoveNext(), nzap++) {
	}
}
static void StaticWriteOneTable(NSBase::ATable * tb, char * str, CDataSource & ds, SS & session)
{
	RSTYPE Rs;
	void* pDummy;
	order(Rs.Open(session, str));
	StaticWriteTable(tb, Rs, ds, session);
	Rs.Close();
}

static void StaticWriteTableMassiv(TableMassiv * tbm, char * str, CDataSource & ds, SS & session)
{
	RSTYPE Rs;
	void* pDummy;
	order(Rs.Open(session, str));//, 0, 0, DBGUID_DEFAULT, true, 1));
	if (Rs.m_spRowset) {
		for (USI ntb = 0; ; ntb++) {
			tbm->New(ntb, 1);
			StaticWriteTable(&(*tbm)[ntb], Rs, ds, session);
			if (Rs.GetNextResult(NULL) != S_OK) break;
		}
	}
	Rs.Close();
}

//static cfstr StaticConnectString("Provider=SQLOLEDB.1;Integrated Security=SSPI;Persist Security Info=False;Initial Catalog=b100;Use Procedure for Prepare=1;Auto Translate=True;Packet Size=4096;Workstation ID=SPACE-GWS60LELS;Use Encryption for Data=False;Tag with column collation when possible=False");
RELIZ//сделать char * 
static cfstr StaticConnectString("Provider=SQLOLEDB.1;Integrated Security=SSPI;Persist Security Info=False;Initial Catalog=b200;Data Source=HOME-CM7903IS97;Use Procedure for Prepare=1;Auto Translate=True;Packet Size=4096;Workstation ID=HOME-CM7903IS97;Use Encryption for Data=False;Tag with column collation when possible=False");

void ABase::SetConnectString(char * str) {
	StaticConnectString = str;
}

void ABase::MakeCommand(char * str) {
	WriteTable_MakeCommand(NULL, NULL, str);
}
void ABase::WriteTable(ATable * tb, char * str) {
	WriteTable_MakeCommand(NULL, tb, str);
}
void ABase::WriteTableMassiv(TableMassiv * tbm, char * str) {
	WriteTable_MakeCommand(tbm, NULL, str);
}

void ABase::WriteTable_MakeCommand(TableMassiv * tbm, ATable * tb, char * str)
{
	CDataSource ds;
	SS session;
	CoInitialize(NULL);		// инициализация COM, 


	if (1) {//есть строка
		CComBSTR b;
		//b=(LPCSTR)"Provider=SQLOLEDB.1;Integrated Security=SSPI;Persist Security Info=False;Initial Catalog=b100;Use Procedure for Prepare=1;Auto Translate=True;Packet Size=4096;Workstation ID=SPACE-GWS60LELS;Use Encryption for Data=False;Tag with column collation when possible=False";
		b = (LPCSTR)StaticConnectString;//"Provider=SQLOLEDB.1;Integrated Security=SSPI;Persist Security Info=False;Initial Catalog=bu100;Data Source=HOME-F3INDR0TUI\SQL100;Use Procedure for Prepare=1;Auto Translate=True;Packet Size=4096;Workstation ID=HOME-F3INDR0TUI;Use Encryption for Data=False;Tag with column collation when possible=False";
										//b=(LPCSTR)"Provider=SQLOLEDB.1;Integrated Security=SSPI;Persist Security Info=False;Initial Catalog=bu100;Data Source=HOME-CM7903IS97;Use Procedure for Prepare=1;Auto Translate=True;Packet Size=4096;Workstation ID=HOME-CM7903IS97;Use Encryption for Data=False;Tag with column collation when possible=False";

		order(ds.OpenFromInitializationString((BSTR)b));
		order(session.Open(ds));
	}
	else {
		BSTR connect;
		order(ds.Open());
		order(ds.GetInitializationString(&connect, true));
		order(session.Open(ds));
		int lllllllll = 0;
	}
	//выполнение запроса
	//	c1 it;
	session.StartTransaction();//ISOLATIONLEVEL_READCOMMITTED, 0, &it);
	if (tbm) StaticWriteTableMassiv(tbm, str, ds, session);
	else if (tb) StaticWriteOneTable(tb, str, ds, session);
	else ::StaticMakeCommand(str, ds, session);
	session.GetTransactionInfo(NULL);
	session.Commit();


	session.Close();
	ds.Close();
	CoUninitialize();
}

static bool cmp100(char * str, char * word, char ** er) {
	if (strlen(str) >= strlen(word) &&
		NSMY::NSStr::bazstr::w_lr(str, word)) {
		str += strlen(word);
		*er = str;
		return true;
	}
	return false;
}
bool ABase::BoolFromString(char * str, char ** errorstr) {
	char * StaticErrorStr = NULL, ** er = (errorstr ? errorstr : &StaticErrorStr);
	*er = str;
	//подведем к букве или сифре
	while (!NSMY::NSStr::class_to_char::simvol(*str) && *str != 0)
		str++;
	if (*str == 0) return false;
	//а не сифра ли ето?
	if (NSMY::NSStr::class_to_char::cifra(*str)) {
		F8 note = NSMY::NSStr::strtof8(str, er);
		if (*er != str) return (note != 0);
	}
	//значит слово
	if (cmp100(str, "false", er)) return false;
	if (cmp100(str, "true", er)) return true;
	if (cmp100(str, "fa", er)) return false;
	if (cmp100(str, "tr", er)) return true;
	if (cmp100(str, "f", er)) return false;
	if (cmp100(str, "t", er)) return true;

	if (cmp100(str, "нет", er)) return false;
	if (cmp100(str, "да", er)) return true;
	if (cmp100(str, "ложь", er)) return false;
	if (cmp100(str, "истина", er)) return true;
	if (cmp100(str, "правда", er)) return true;
	return true;
}

cfstr NSMY::NSBase::ABase::GetOneString(char * str)
{
	ATable tb;
	WriteTable(&tb, str);
	if (tb.CountColumns() > 0 && tb.CountStrings() > 0) return tb.GetCell(0, 0).str;
	return cfstr("");
}

bool NSMY::NSBase::ABase::Exists(char * str)
{
	ATable tb;
	WriteTable(&tb, str);
	return (tb.CountStrings() > 0);
}
#endif //pragma once
#endif //pragma once


