#include "stdafx.h"
#include "../cod_base/stdafx.h"
#include "../cod_base/atable.h"
#include "../cod_base/abasemysql.h"
#define USE_OLD_FUNCTIONS 1

#ifdef  WIN_OPERACION_SYSTEM 
#include <windows.h>
//#include "c:/Program Files/MySQL/MySQL Server 5.5/include/mysql.h"
//#pragma comment(lib, "C:/Program Files/MySQL/MySQL Server 5.5/lib/debug/mysqlclient.lib")
//#pragma comment(lib, "C:/Program Files/MySQL/MySQL Server 5.5/lib/mysqlclient.lib")
#include "C:/Program Files/MySQL/MySQL Server 5.7/include/mysql.h"
#if _DEBUG
                      //C:\Program Files\MySQL\MySQL Server 5.7\lib
#pragma comment(lib, "C:/Program Files/MySQL/MySQL Server 5.7/lib/libmysql.lib")
#pragma comment(lib, "C:/Program Files/MySQL/MySQL Server 5.7/lib/mysqlclient.lib")
//#pragma comment(lib, "D:/MYSQL55/lib/debug/mysqlclient.lib")
//					  c:\Program Files\MySQL\MySQL Server 5.7\lib\libmysql.dll
#else
                      //C:\Program Files\MySQL\MySQL Server 5.7\lib
#pragma comment(lib, "C:/Program Files/MySQL/MySQL Server 5.7/lib/libmysql.lib")
#pragma comment(lib, "C:/Program Files/MySQL/MySQL Server 5.7/lib/mysqlclient.lib")
//#pragma comment(lib, "D:/MYSQL55/lib/debug/mysqlclient.lib")
//					  c:\Program Files\MySQL\MySQL Server 5.7\lib\libmysql.dll
#endif
//#pragma comment(lib, "C:/Program Files (x86)/MySQL/MySQL Server 5.5/lib/mysqlclient.lib")
#endif

//#define CCPP  (const char *(__cdecl *)(anyp)) (char*) 
//#define CCPP  (const char *((__cdecl *)(anyp))) (char*) 
#define CCPP  
	 


#ifdef  SSS_ruau_offis_unix_SSS
#error nado raskommentirovat stroki
//#include "//root/Install/mysql-5.0.18/include/mysql.h"
//#pragma comment(lib, "/usr/local/mysql/lib/mysql/libmysqlclient.so.15.0.0")
#endif


#ifdef  SSS_krolik_offis_unix_SSS
#error nado raskommentirovat stroki
//#include "/usr/include/mysql/mysql.h"
//#pragma comment(lib, "/usr/lib/mysql/libmysqlclient.so.18.0.0")
#endif

#ifdef  SSS_ruau_inet_unix_on_spaceweb_server_SSS
#error nado raskommentirovat stroki
//#include "//usr/include/mysql/mysql.h"
//#pragma comment(lib, "/usr/lib/mysql/libmysqlclient.so.15.0.0")

#endif




//#include <mysql++.h>
#include <stdio.h>
#include <stdlib.h>


//drweb в брендмаэере добавить приложение и установить разрешения
//a@mail.ru
//static cfstr StaticConnectString("Provider=SQLOLEDB.1;Integrated Security=SSPI;Persist Security Info=False;Initial Catalog=b200;Data Source=HOME-CM7903IS97;Use Procedure for Prepare=1;Auto Translate=True;Packet Size=4096;Workstation ID=HOME-CM7903IS97;Use Encryption for Data=False;Tag with column collation when possible=False");
static ABaseMYSQLConnect * StaticConnectClass=NULL;
char *ABaseMYSQLConnect::host() { return NULL; }
char *ABaseMYSQLConnect::user() { return "root"; }
char *ABaseMYSQLConnect::passwd() { return "823945"; }
char *ABaseMYSQLConnect::db() { return NULL; }
char *ABaseMYSQLConnect::unix_socket() { return NULL; }
unsigned int ABaseMYSQLConnect::port() { return MYSQL_PORT; }

void ABaseMYSQLConnect::CoutAllToConsol() {
	if(host()) cout << "host=" << host() << "\n";
	if(user()) cout << "user=" << user() << "\n";
	
	if(passwd()) {
		cfstr p1;
		p1.Insert(passwd(), 0, 1);
		cout << "passwd=" << (char *)p1 << "\n";
	}
	if(db()) cout << "db=" << db() << "\n";
	if(unix_socket()) cout << "unix_socket=" << unix_socket() << "\n";
	if(port()) cout << "port=" << port() << "\n";
}

unsigned int ABaseMYSQLConnect::client_flag() { return 0; }
ABaseMYSQLConnect::ABaseMYSQLConnect() {
	_myData=NULL;
}
ABaseMYSQLConnect::~ABaseMYSQLConnect() {
	//TA(!_myData);
}


#define myData ((MYSQL *)StaticConnectClass->_myData)

void TestABase() {
	NSMY::NSBase::ATable tb;
	NSMY::NSDebug::RunTime rt;
	rt.init();
	for(int n1=0; n1<100; n1++) {
		NSBase::ABaseMYSQL::MakeCommand("delete from dbo.t2");
		NSBase::ABaseMYSQL::MakeCommand("insert into t2 (c1, c2) values ('', 'ppp')");
		NSBase::ABaseMYSQL::WriteTable(&tb, "select *  from t2");
	}
	rt.srez();
	rt.srez();
}

void ABaseMYSQL::SetConnectClass(ABaseMYSQLConnect * p) {
	StaticConnectClass=p;
}


void ABaseMYSQL::MakeCommand(char * str, cfstr * RetErrorStr, cfstr * RetId) {
	WriteTable_MakeCommand(NULL, NULL, str, RetErrorStr, RetId);
}
void ABaseMYSQL::WriteTable(ATable * tb, char * str, cfstr * RetErrorStr) {
	WriteTable_MakeCommand(NULL, tb, str, RetErrorStr);
}
void ABaseMYSQL::WriteTableMassiv(TableMassiv * tbm, char * str, cfstr * RetErrorStr) {
	WriteTable_MakeCommand(tbm, NULL, str, RetErrorStr);
}

//DEFAULT CHARSET=utf8 COLLATE utf8_general_ci
//дописывать COLLATION И CHARACTER SET ко всем создаваемым таблицам вручную.


char * ABaseMYSQL::Get_CHARACTER_SET(bool utf8, bool cp1251) {
	//if(utf8) return "CHARACTER SET=utf8 COLLATE utf8_bin";
	if(utf8) return " DEFAULT  CHARACTER SET=utf8 COLLATE utf8_general_ci";
//	if(utf8) return " DEFAULT  CHARACTER SET=utf8 COLLATE utf8_unicode_ci";
	if(cp1251) return " DEFAULT  CHARACTER SET=cp1251 COLLATE cp1251_general_ci";
	return "";
}
bool ABaseMYSQL::ConnectToBase() 
{
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//исключительная ситуация, испоьзуется при отладке. 
	//т. к. нормально закрывать соединение не получается (причем не только у меня)
	RELIZ //для Unix наверное надо будет убрать
	if(StaticConnectClass->_myData!=NULL) return true;
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
																							/*	printf(" %d ", (int)StaticConnectClass);
																								StaticConnectClass->_myData=(void *)99;
																								printf(" %d ", (int)StaticConnectClass);
																								printf(" %d ", (int)StaticConnectClass->_myData);
																								return false;*/
	bool ret=false;
	if(StaticConnectClass->_myData = (void *)mysql_init((MYSQL *)NULL)) {
#if TEST_V
																							  cfstr host100=StaticConnectClass->host(),
																								  user100=StaticConnectClass->user(), 
																								  pass100=StaticConnectClass->passwd(), 
																								  db100=StaticConnectClass->db(),
																								  sock100=StaticConnectClass->unix_socket();
																								  int cf100=StaticConnectClass->client_flag();
																								  int port100=StaticConnectClass->port();
#endif
	//mysql_options(myData, MYSQL_READ_DEFAULT_GROUP, "test2_libmysqld_CLIENT");//88888
	  //								NULL						zavodilasu
	  if(mysql_real_connect(myData, StaticConnectClass->host(), StaticConnectClass->user()
		  //             ok					zavodilasu					3306
		  , StaticConnectClass->passwd(), StaticConnectClass->db(), StaticConnectClass->port(),
		  ///var/run/mysqld/mysqld.sock			NULL
		  StaticConnectClass->unix_socket(), StaticConnectClass->client_flag())) 
	  {
	//	  mysql_options(myData, MYSQL_SET_CHARSET_NAME, "utf8");
	//	  mysql_options(myData,MYSQL_INIT_COMMAND, "SET NAMES utf8");
		  char * kod= (char *) "SET NAMES 'utf8' COLLATE 'utf8_general_ci'";
	//	  char * kod="SET NAMES utf8";
		  if(!mysql_query(myData, CCPP kod)) {
			ret=true;
		  } 
			int nextok=0;
			if(!mysql_query(myData, CCPP  "set session collation_connection=utf8")) nextok++;
			if(!mysql_query(myData, CCPP "set session character_set_database=utf8")) nextok++;
			if(!mysql_query(myData, CCPP "set session character_set_client=utf8")) nextok++;
			if(!mysql_query(myData, CCPP "set session character_set_connection=utf8")) nextok++;
			if(!mysql_query(myData, CCPP "set session character_set_results=utf8")) nextok++;
		/*			//  ret=true;
			//а следующая команда вешает программу, поэтому мы ее не выполняем!!!!!!!!!!!
			ret=true;
		  char * kod="set names 'UTF-8'";
		  if(!mysql_real_query(myData, kod, strlen(kod))) {
		  }mysql_query("set session character_set_client=utf8;")
		  char * kod="set session character_set_client=utf8;";
		  if(!mysql_query(myData, kod)) {
			ret=true;
		  } 
			  */
//		  mysqli_set_charset(
	  } else {
			fprintf(stderr, "Failed to connect to database: Error: %s\n",
				  mysql_error(myData));
			mysql_close( myData ) ;
			StaticConnectClass->_myData=NULL;
			GlobalDebugDraw((char *)"Error 354658789. In mysql_real_connect.");
	  } 
  } else {
		GlobalDebugDraw((char *)"Error 32434345. In mysql_init.");
  } 
  return ret;
}
void ABaseMYSQL::OtConnectFromBase() 
{
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//исключительная ситуация, испоьзуется при отладке. 
	//т. к. нормально закрывать соединение не получается (причем не только у меня)
	RELIZ //для Unix наверное надо будет убрать
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//дибильная ошибка какая-то выскакивает
	//убрал функцию, чтобы тесту не мешала
#ifndef NOT_mysql_close_CALL
	mysql_close(myData ) ;
	/*

	получается так...
	при отладке и в консоли  эта ункция выдает ошибку,
	а в онлайне ... вроде как работает.
	без нее ошибка выскакивает, в отладке, но при завершении программы. 
	а бывает, что и не выскакивает...
	*/
#endif
	StaticConnectClass->_myData = (void *)NULL;
}


void ABaseMYSQL::WriteTable_MakeCommand(TableMassiv * tbm, ATable * tb, char * str, cfstr * RetErrorStr, cfstr * RetId) 
{
  bool ok=false;

	if(!mysql_real_query(myData, CCPP str, strlen(str))) {
		if(tb) {
			//записываем результат в таблицу
			if(MYSQL_RES * res=mysql_store_result(myData)) {
				//делаем таблицу
				USI ncolumn=mysql_num_fields(res);
				USI nstring=mysql_num_rows(res);
				{
					tb->Clear();
					tb->NewColumns(0, ncolumn);
					tb->NewStrings(0, nstring);
					MYSQL_FIELD *fields = mysql_fetch_fields(res);
					for(USI ncol1=0; ncol1<ncolumn; ncol1++) 
						tb->GetColumnInfo(ncol1).name=fields[ncol1].name;
				}
				//записываем таблицу
				USI nstr1;
				for(nstr1=0; nstr1<nstring; nstr1++) {
					MYSQL_ROW row=mysql_fetch_row(res);
					if(!row) break;
					for(USI ncol1=0; ncol1<ncolumn; ncol1++) {
						tb->GetCell(ncol1, nstr1).str=(row[ncol1] ? row[ncol1] : (char *)"");
					}
				}
				//успешное завершение
				if(nstr1 == nstring) ok=true;
				mysql_free_result(res);
			} else {
				GlobalDebugDraw((char *)"Error 13243457455. mysql_store_result.");
			}
		} else ok=true;
		//возвращение ида
		if(RetId) {
			my_ulonglong id=mysql_insert_id(myData);
			char buf[256];
			itos<my_ulonglong, char*>(id, buf, 256);
			*RetId=buf;
		}
	} else {
		GlobalDebugDraw((char *)"Error 436789789. mysql_real_query.");
	}
	const char * er=mysql_error(myData);
	if(er[0] != '\0')
	{
	// ошибка  возникла
		if(RetErrorStr) *RetErrorStr << "Error in MySQL, bly.\n" << er << "\sql==" << str << "==sql";
		GlobalDebugDraw((char *)"Error 473734587. In Zapros.");
		GlobalDebugDraw((char *)er);
		int gggggggggggg=0;
	}		
  //обработка ошибок
//  if(!ok && !RetErrorStr) A(0);
  if(!ok) TA(0);
}

static bool cmp100(char * str, char * word, char ** er) {
	if(strlen(str) >= strlen(word) && 
		NSMY::NSStr::bazstr::w_lr(str, word)) {
		str+=strlen(word);
		*er=str;
		return true;
	}
	return false;
}
bool ABaseMYSQL::BoolFromString(char * str, char ** errorstr) {
	char * StaticErrorStr=NULL, ** er=(errorstr ? errorstr : &StaticErrorStr);
	*er=str;
	//подведем к букве или сифре
	while(!NSMY::NSStr::class_to_char::simvol(*str) && *str != 0) 
		str++;
	if(*str == 0) return false;
	//а не сифра ли ето?
	if(NSMY::NSStr::class_to_char::cifra(*str)) {
		F8 note=NSMY::NSStr::strtof8(str, er);
		if(*er != str) return (note != 0);
	}
	//значит слово
	if(cmp100(str, "false", er)) return false;
	if(cmp100(str, "true", er)) return true;
	if(cmp100(str, "fa", er)) return false;
	if(cmp100(str, "tr", er)) return true;
	if(cmp100(str, "f", er)) return false;
	if(cmp100(str, "t", er)) return true;

	if(cmp100(str, "нет", er)) return false;
	if(cmp100(str, "да", er)) return true;
	if(cmp100(str, "ложь", er)) return false;
	if(cmp100(str, "истина", er)) return true;
	if(cmp100(str, "правда", er)) return true;
	return true;
}

cfstr ABaseMYSQL::GetOneString(char * str) {
	return GetOneString(str, NULL, NULL);
}

cfstr ABaseMYSQL::GetOneString(char * str, cfstr * RetErrorStr) {
	return GetOneString(str, RetErrorStr, NULL);
}

cfstr ABaseMYSQL::GetOneString(char * str, cfstr * RetErrorStr, char * SetIfNoReturn)
{
	cfstr ret;
	ATable tb;
	WriteTable(&tb, str, RetErrorStr);
	if(tb.CountColumns() > 0 && tb.CountStrings() > 0) ret=tb.GetCell(0, 0).str;
	if(!ret.GetSize() && SetIfNoReturn) ret << SetIfNoReturn;
	return ret;
}

bool ABaseMYSQL::Exists(char * str, cfstr * RetErrorStr)
{
	ATable tb;
	WriteTable(&tb, str, RetErrorStr);
	if (tb.CountStrings() == 0) 
		return false;
	//if (tb.CountStrings() == 1 && tb.CountColumns() == 1 && tb.GetCell(0, 0).str == "")
	//	return false;
	return true;
}



