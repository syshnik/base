/*Сайт "Заводила" © Сафаров Олег Айратович 2014 г. инн 027304982940*/
#pragma once
#ifndef	_pragma_once_57907185445588
#define	_pragma_once_57907185445588
#ifdef MACROS_MYSQL_BD
namespace NSMY {
namespace NSBase {
class EXPORT_OR_IMPPORT ABaseMYSQLConnect 
{
public:
	ABaseMYSQLConnect();
	~ABaseMYSQLConnect();
	void CoutAllToConsol();
	void * _myData;
	virtual char *host();// { return NULL; }
	virtual char *user();// { return NULL; }
	virtual char *passwd();// { return NULL; }
	virtual char *db();// { return NULL; }
	virtual char *unix_socket();// { return NULL; }
	virtual unsigned int port();// { return MYSQL_PORT; }
	virtual unsigned int client_flag();// { return 0; }
};

class    		EXPORT_OR_IMPPORT			ABaseMYSQL
{
	static void WriteTable_MakeCommand(TableMassiv * tbm, ATable * tb, char * str, cfstr * RetErrorStr=NULL, cfstr * RetId=NULL);
public:
	static void OtConnectFromBase();
	static bool ConnectToBase();
	static void SetConnectClass(ABaseMYSQLConnect * p);
	//static void SetConnectString(char * str);
	static void MakeCommand(char * str, cfstr * RetErrorStr=NULL, cfstr * RetId=NULL);
	static void WriteTable(ATable * tb, char * str, cfstr * RetErrorStr=NULL);
	static void WriteTableMassiv(TableMassiv * tbm, char * str, cfstr * RetErrorStr=NULL);
	static bool BoolFromString(char * str, char ** errorstr = NULL);
	static cfstr GetOneString(char * str);
	static cfstr GetOneString(char * str, cfstr * RetErrorStr);
	static cfstr GetOneString(char * str, cfstr * RetErrorStr, char * SetIfNoReturn);
	static bool Exists(char * str, cfstr * RetErrorStr=NULL);
	static char * Get_CHARACTER_SET(bool utf8, bool cp1251) ;
};


}//namespace NSMY {
}//namespace NSBase {
using namespace NSMY::NSBase;

#endif //pragma once
#endif //pragma once
