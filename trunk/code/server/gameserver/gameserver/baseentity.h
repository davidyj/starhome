#include "utldict.h"

typedef CUtlDict<char*,byte>	stringlist;
typedef CUtlDict<int,byte>		intlist;
typedef CUtlDict<int64,byte>	int64list;

class CBaseEntity
{
public:
	CBaseEntity();
	~CBaseEntity();

public:
	void	setInt(const char* k,int v);
	int		getInt(const char* k);

	void	setInt64(const char* k,int64 v);
	int64	getint64(const char* k);

	void	setString(const char* k,char* v);
	const char*	getString(const char* k);

protected:
	intlist		m_intlist;
	int64list	m_int64list;
	stringlist	m_stringlist;
};