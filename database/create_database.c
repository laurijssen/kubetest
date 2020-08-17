#include <stdio.h>
#include <stdlib.h>
#include <sql.h>
#include <sqlext.h>
#include <string.h>

#define RESULT_LEN  256

#define CHECK_ERROR(e, s, h, t) ({\
            if (e!=SQL_SUCCESS && e != SQL_SUCCESS_WITH_INFO) {extract_error(s, h, t); goto exit;} \
})

void extract_error(char *fn, SQLHANDLE handle, SQLSMALLINT type)
{
	SQLINTEGER i = 0;
	SQLINTEGER NativeError;
	SQLCHAR SQLState[7];
	SQLCHAR MessageText[256];
	SQLSMALLINT TextLength;
	SQLRETURN ret;

	fprintf(stderr, "\nThe driver reported the following error %s\n", fn);
	do
	{
		ret = SQLGetDiagRec(type, handle, ++i, SQLState, &NativeError,
			MessageText, sizeof(MessageText), &TextLength);
		//if (SQL_SUCCEEDED(ret)) {
			printf("%s:%ld:%ld:%s\n",
				SQLState, (long)i, (long)NativeError, MessageText);
		//}
	} while (ret == SQL_SUCCESS);
}

int main()
{
    SQLHENV   henv = SQL_NULL_HENV;   // Environment
	SQLHDBC   hdbc = SQL_NULL_HDBC;   // Connection handle
	SQLHSTMT  hstmt = SQL_NULL_HSTMT;  // Statement handle
	SQLRETURN retcode;
	SQLCHAR strResult[RESULT_LEN];
	SQLCHAR outstr[1024];
	SQLSMALLINT outstrlen;

	int i = 0;    

	retcode = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &henv);
	CHECK_ERROR(retcode, "SQLAllocHandle(SQL_HANDLE_ENV)",
		henv, SQL_HANDLE_ENV);
	retcode = SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION,
		(SQLPOINTER*)SQL_OV_ODBC3, 0);
	CHECK_ERROR(retcode, "SQLSetEnvAttr(SQL_ATTR_ODBC_VERSION)",
		henv, SQL_HANDLE_ENV);
	retcode = SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION,
		(SQLPOINTER*)SQL_OV_ODBC3, 0);
	CHECK_ERROR(retcode, "SQLSetEnvAttr(SQL_ATTR_ODBC_VERSION)",
		henv, SQL_HANDLE_ENV);
	retcode = SQLAllocHandle(SQL_HANDLE_DBC, henv, &hdbc);
	CHECK_ERROR(retcode, "SQLAllocHandle(SQL_HANDLE_DBC)",
		hdbc, SQL_HANDLE_DBC);
	SQLSetConnectAttr(hdbc, SQL_LOGIN_TIMEOUT, (SQLPOINTER)5, 0);
	CHECK_ERROR(retcode, "SQLSetConnectAttr(SQL_LOGIN_TIMEOUT)",
		hdbc, SQL_HANDLE_DBC);

	SQLCHAR *s = getenv("CONNECTION_STRING");

	retcode = SQLDriverConnect(hdbc, NULL, s, 
					SQL_NTS, outstr, sizeof(outstr), &outstrlen, SQL_DRIVER_NOPROMPT);

	retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);
	CHECK_ERROR(retcode, "SQLAllocHandle(SQL_HANDLE_STMT)", hstmt, SQL_HANDLE_STMT);

	SQLCHAR *query = "create table users (id int not null primary key,"
						   "firstname nvarchar(128),"
						   "lastname nvarchar(128),"
						   "loginname nvarchar(32),"
						   "password nvarchar(32))";

	CHECK_ERROR(SQLExecDirect(hstmt, query, SQL_NTS), "SQLExecDirect", hstmt, SQL_HANDLE_STMT);

	printf("users created\n");

	query = "create table login (id int not null primary key, lat float, long float, userid int not null constraint fk_user foreign key(userid) references users(id))";

	CHECK_ERROR(SQLExecDirect(hstmt, query, SQL_NTS), "SQLExecDirect", hstmt, SQL_HANDLE_STMT);

	/*retcode = SQLBindCol(hstmt, 1, SQL_C_CHAR, &strResult, RESULT_LEN, 0);

	for (i = 0; ; i++) {
		retcode = SQLFetch(hstmt);
		if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
			printf("Result is: %s", strResult);
		}
		else {
			if (retcode != SQL_NO_DATA) {
				CHECK_ERROR(retcode, "SQLFetch()", hstmt, SQL_HANDLE_STMT);
			}
			else {
				break;
			}
		}
	}*/

exit:
	if (hstmt != SQL_NULL_HSTMT)
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
	if (hdbc != SQL_NULL_HDBC) {
		SQLDisconnect(hdbc);
		SQLFreeHandle(SQL_HANDLE_DBC, hdbc);
	}
	if (henv != SQL_NULL_HENV)
		SQLFreeHandle(SQL_HANDLE_ENV, henv);
	return 0;    
}