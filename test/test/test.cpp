// test.cpp : 定义控制台应用程序的入口点。
//


#include "stdafx.h"

#include "../include/iptcom/api/iptcom.h"
#include <iostream>

#include <sql.h>
#include <sqlext.h>
#include <odbcss.h>
#include <vector>
#include <windows.h>
#include <process.h>
#include <sstream>

using namespace std;

HINSTANCE hInstance = LoadLibraryA("iptcom.dll");
SQLHENV henv = SQL_NULL_HENV;//定义环境句柄
SQLHDBC hdbc1 = SQL_NULL_HDBC;//定义数据库连接句柄     
SQLHSTMT hstmt1 = SQL_NULL_HSTMT;//定义语句句柄

#define MaxNameLen 32

#define XML_FILE "ipt_config_MCU.xml"
#define TDC_FILE "tdc-071bart.hosts-with-multicast"

typedef struct {
	unsigned int comid;
	unsigned int handle;
	unsigned int groupid;
	unsigned int size;
	volatile bool reflesh_flag;
} PD_INFO;

vector<PD_INFO> pdVector;

int checkDB() {
	RETCODE retcode;//错误返回码
	retcode = SQLAllocHandle (SQL_HANDLE_ENV, NULL, &henv); 
	if(retcode < 0 )//错误处理
	{
		cout<<"allocate ODBC Environment handle errors."<<endl;
		return -1;
	}
	// Notify ODBC that this is an ODBC 3.0 application.
	retcode = SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER) SQL_OV_ODBC3, SQL_IS_INTEGER);
	if(retcode < 0 ) //错误处理
	{
		cout<<"the  ODBC is not version3.0 "<<endl;
		return -1;
	}

	 // Allocate an ODBC connection and connect.
	retcode = SQLAllocHandle(SQL_HANDLE_DBC, henv, &hdbc1);
	if(retcode < 0 ) //错误处理
	{
		cout<<"allocate ODBC connection handle errors."<<endl;
		return -1;
	}

	//Data Source Name must be of type User DNS or System DNS
	char* szDSN = "AD";
	char* szUID = "";//log name
	char* szAuthStr = "";//passward
	//connect to the Data Source
	retcode = SQLConnectA(hdbc1,(SQLCHAR*)szDSN,(SWORD)strlen(szDSN),(SQLCHAR*)szUID, (SWORD)strlen(szUID),(SQLCHAR*)szAuthStr, (SWORD)strlen(szAuthStr));
	if(retcode < 0 ) //错误处理
	{  
		cout<<"connect to  ODBC datasource errors."<<endl;
		return -1;
	}
	// Allocate a statement handle.
	retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc1, &hstmt1);
	if(retcode < 0 ) //错误处理
	{
		cout<<"allocate ODBC statement handle errors."<<endl;
		return -1;
	}
	return 0;
}

int initDevice() {

	typedef PD_HANDLE (*PROC_PDComAPI_publish)(UINT32, UINT32, const char *);
	typedef int (*PROC_IPTVosGetUniqueNumber)(void);
	typedef void (*PROC_PDComAPI_put)(PD_HANDLE, const BYTE *);
	typedef void (*PROC_PDComAPI_source)(UINT32);

	PROC_PDComAPI_publish PDComAPI_publish = (PROC_PDComAPI_publish)GetProcAddress(hInstance, "PDComAPI_publish");
	PROC_IPTVosGetUniqueNumber IPTVosGetUniqueNumber = (PROC_IPTVosGetUniqueNumber)GetProcAddress(hInstance, "IPTVosGetUniqueNumber");
	PROC_PDComAPI_put PDComAPI_put = (PROC_PDComAPI_put)GetProcAddress(hInstance, "PDComAPI_put");
	PROC_PDComAPI_source PDComAPI_source = (PROC_PDComAPI_source)GetProcAddress(hInstance, "PDComAPI_source");

	RETCODE retcode;//错误返回码
	retcode = SQLExecDirectA(hstmt1,(SQLCHAR*)"SELECT PD_LIST.COMID,COMID_TABLE.SIZE FROM PD_LIST, COMID_TABLE WHERE PD_LIST.FLAG=0 AND COMID_TABLE.COMID = PD_LIST.COMID", SQL_NTS);
	if(retcode != SQL_SUCCESS)
	{
		cout<<"Executing statement  throught ODBC  errors."<<endl;
		return -1;
	}
	SQLCHAR	comid[MaxNameLen];
	SQLINTEGER sqlInterger;
	SQLINTEGER columnLen = 0;//数据库定义中该属性列的长度

	pdVector.resize(0);

	while(1)
	{
		retcode = SQLFetch(hstmt1);
		if(retcode == SQL_NO_DATA)
		break;
  
		retcode = SQLGetData(hstmt1, 1, SQL_C_CHAR, comid, MaxNameLen, &columnLen);
		retcode = SQLGetData(hstmt1, 2, SQL_C_ULONG, &sqlInterger, 0, &columnLen);
		
		PD_INFO info;
		info.comid = atoi((char*)comid);
		info.size = sqlInterger;
		info.groupid = IPTVosGetUniqueNumber();
		info.reflesh_flag = true;
		info.handle = PDComAPI_publish(info.groupid, info.comid, NULL);
		pdVector.push_back(info);

	}
	SQLFreeHandle(SQL_HANDLE_STMT, hstmt1);

	while(1) {
		for(unsigned int i = 0; i < pdVector.size(); i++) {
			if(!pdVector[i].reflesh_flag)	continue;
			
			unsigned char* pData = new unsigned char[pdVector[i].size];
			stringstream ss;
			ss<<"SELECT ";
			for(unsigned int j = 0; j < pdVector[i].size; j++) {
				ss<<"DATA"<<j/100<<".L"<< j%100<<",";
			}
			ss<<"DATA0.COMID FROM DATA0";
			if(pdVector[i].size / 100 > 0)	ss<<",DATA1";
			if(pdVector[i].size / 100 > 1)	ss<<",DATA2";
			ss<<" WHERE DATA0.COMID = '"<<pdVector[i].comid<<"'";
			if(pdVector[i].size / 100 > 0)	ss<<" AND DATA1.COMID=DATA0.COMID";
			if(pdVector[i].size / 100 > 1)	ss<<" AND DATA2.COMID=DATA0.COMID";

			string sql = ss.str();
			//cout << sql.c_str() << endl;

			retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc1, &hstmt1);
			if(retcode < 0 ) //错误处理
			{
				cout<<"allocate ODBC statement handle errors."<<endl;
				return -1;
			}

			retcode = SQLExecDirectA(hstmt1,(SQLCHAR*)sql.c_str(), SQL_NTS);
			if(retcode < 0 )
			{
				cout<<"Executing statement  throught ODBC  errors."<<endl;
				return -1;
			}

			retcode = SQLFetch(hstmt1);
			if(retcode != SQL_NO_DATA) {
				for(int k = 0; k < pdVector[i].size; k++) {
					retcode = SQLGetData(hstmt1, k+1, SQL_C_ULONG, &sqlInterger, 0, &columnLen);
					pData[k] = sqlInterger & 0x00FF;
				}
			}	
			SQLFreeHandle(SQL_HANDLE_STMT, hstmt1);

			PDComAPI_put(pdVector[i].handle, pData);
			PDComAPI_source(pdVector[i].groupid);

			delete pData;
			pdVector[i].reflesh_flag = false;
		}
		Sleep(300);
	}

	return 0 ;
}

unsigned _stdcall ThreadProc(void* param) {
	cout<<"_beginthreadex create thread"<<endl;
	string command;
	while(1) {
		getline(cin, command, '\n');
		istringstream is(command);
		string cmd;
		is>>cmd;

		if(cmd=="pd") {
			int comid = 0;
			is>>comid;
			cout<<"comid="<<comid<<endl;
			for(unsigned int i = 0; i < pdVector.size(); i++) {
				if(pdVector[i].comid == comid) {
					pdVector[i].reflesh_flag = true;
					break;
				}
			}
		} else if(cmd=="") {
			//do nothing
		} else {
			cout<<"wrong command"<<endl;
		}

		Sleep(100);
	}
	return 0;
}

int _tmain(int argc, _TCHAR* argv[])
{

	typedef void (*PROC_IPTCom_enableIPTDirEmulation)(char*);
	typedef int (*PROC_IPTCom_prepareInit)(int, const char*);
	typedef int (*PROC_IPTCom_getStatus)(void);
	typedef int (*PROC_IPTCom_getUriHostPart)(UINT32 ,char *, UINT8 *);

	PROC_IPTCom_enableIPTDirEmulation IPTCom_enableIPTDirEmulation = (PROC_IPTCom_enableIPTDirEmulation)GetProcAddress(hInstance, "IPTCom_enableIPTDirEmulation"); 
	PROC_IPTCom_prepareInit IPTCom_prepareInit = (PROC_IPTCom_prepareInit)GetProcAddress(hInstance, "IPTCom_prepareInit"); 
	PROC_IPTCom_getStatus IPTCom_getStatus = (PROC_IPTCom_getStatus)GetProcAddress(hInstance, "IPTCom_getStatus"); 
	PROC_IPTCom_getUriHostPart IPTCom_getUriHostPart = (PROC_IPTCom_getUriHostPart)GetProcAddress(hInstance, "IPTCom_getUriHostPart"); 

	IPTCom_enableIPTDirEmulation(TDC_FILE);

    int ret;
    ret = IPTCom_prepareInit(0, XML_FILE);
    if(ret!=0) {
        cout<<"IPTCom_prepareInit() "<<ret<<endl;
        return -1;
    }

	while(1) {
		ret = IPTCom_getStatus();
		if(ret != 0) {
			cout << "IPTCom_getStatus() "<<ret<<endl;
		} else {
			break;
		}
	}

	HANDLE handle = (HANDLE)_beginthreadex(NULL, 0, ThreadProc, NULL, NULL, NULL);
	if (handle == NULL)
	{
		cout<<"create thread failed"<<endl;
		system("pause");
		return 0;
	}

	checkDB();
	initDevice();

	/* Clean up.*/
	SQLDisconnect(hdbc1);
	SQLFreeHandle(SQL_HANDLE_DBC, hdbc1);
	SQLFreeHandle(SQL_HANDLE_ENV, henv);
	system("pause");
	return 0;
}

