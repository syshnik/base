/*Сайт "Заводила" © Сафаров Олег Айратович 2014 г. инн 027304982940*/
#pragma once
#ifndef	_pragma_once_579071854455444
#define	_pragma_once_579071854455444

#ifdef DEF_WND_STDAFX
	#define EXPORT_OR_IMPPORT OK_EXPORT
#else
	#define EXPORT_OR_IMPPORT OK_IMPORT
#endif

#include "../cod_base/atable.h"
#include "../cod_base/abase.h"
#include "../cod_base/abasemysql.h"

#undef EXPORT_OR_IMPPORT
#endif //pragma once