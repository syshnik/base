/*Сайт "Заводила" © Сафаров Олег Айратович 2014 г. инн 027304982940*/
#pragma once
#ifndef	_pragma_once_579071854455
#define	_pragma_once_579071854455
#ifdef VNET_COMPIL936
#ifdef MACROS_MSSQL_BD
namespace NSMY {
namespace NSBase {

class    		EXPORT_OR_IMPPORT			ABase
{
	static void WriteTable_MakeCommand(TableMassiv * tbm, ATable * tb, char * str);
public:
	static void SetConnectString(char * str);
	static void MakeCommand(char * str);
	static void WriteTable(ATable * tb, char * str);
	static void WriteTableMassiv(TableMassiv * tbm, char * str);
	static bool BoolFromString(char * str, char ** errorstr = NULL);
	static cfstr GetOneString(char * str);
	static bool Exists(char * str);
};


}//namespace NSMY {
}//namespace NSBase {
using namespace NSMY::NSBase;

#endif //pragma once
#endif //pragma once
#endif //pragma once
