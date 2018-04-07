#include <time.h>
#include <iostream>
#include <cstring>
#include <errno.h> 
#include <stdio.h>
#include "zlog.h"

using namespace std;
using namespace z;

static const string scg_slevelERROR("E");

static string getTime()
{
    time_t t = time(0);
    char tmp[64];
    strftime(tmp, sizeof(tmp), "%Y-%m-%d %H:%M:%S", localtime(&t));
    return tmp;
}
string getTime(const char* const stimeFormat)
{
    time_t t = time(0);
    char tmp[64];
    strftime(tmp, sizeof(tmp), stimeFormat, localtime(&t));
    return tmp;
}

zlog::zlog():m_slogFileName(scg_slogFileName), m_slogFileNameSuffixal(scg_slogFileNameSuffixal)
{
    getMemory();
    init();
}

z::zlog::zlog(const string& slogFileName) :m_slogFileName(slogFileName), m_slogFileNameSuffixal(scg_slogFileNameSuffixal)
{
    getMemory();
    init();
}


zlog::~zlog()
{
    clear();
    deleteMemory();
}

void z::zlog::init()
{
    m_wf.open((m_slogFileName + m_slogFileNameSuffixal).c_str(), ios::app);
    if (!m_wf.is_open())
    {
        PRINT(scg_slevelERROR, "open %s failed, %s", m_slogFileName.c_str(), strerror(errno));
    }
    return;
}

void z::zlog::getMemory()
{
    m_pperLogbuf = new char[scg_iperLogMaxLen];
    memset(m_pperLogbuf, 0, scg_iperLogMaxLen);
    return;
}

void z::zlog::deleteMemory()
{
    delete[] m_pperLogbuf;
    m_pperLogbuf = NULL;
}

void z::zlog::clear()
{
    m_wf << m_ss.str();
    m_ss.str("");
    m_wf.close();
    return;
}

void z::zlog::writeLog(const char * const logLevel, const string & sfileName, unsigned int iLineNo
    , const string & sfunctionName, const char * pformat, ...)
{
    memset(m_pperLogbuf, 0, scg_iperLogMaxLen);

    string sfileNameTmp(sfileName);
#ifdef _WIN32
    string::size_type index = sfileName.rfind("\\");
#else
    string::size_type index = sfileName.rfind("/");
#endif
    if (string::npos != index && index + 1 < sfileName.size())
    {
        sfileNameTmp = sfileName.substr(index + 1);
    }
    
    va_list args;
    va_start(args, pformat);
    vsprintf(m_pperLogbuf, pformat, args);
    va_end(args);
    m_ss << getTime() 
        << scg_cboxOffSignForLog << logLevel
        << scg_cboxOffSignForLog << "[" << sfileNameTmp << "," << iLineNo << "]"
        << scg_cboxOffSignForLog << sfunctionName
        << scg_cboxOffSignForLog << m_pperLogbuf << endl;
    
    return;
}

void z::zlog::backupLogFile()
{
    clear();
    string soldLogFileNewName = m_slogFileName.substr(0, m_slogFileName.size() - m_slogFileNameSuffixal.size())
        + getTime("%Y%m%d%H%M%S") + m_slogFileNameSuffixal;
    if (0 != rename(m_slogFileName.c_str(), soldLogFileNewName.c_str()))
    {
        PRINT(scg_slevelERROR, "rename [%s] to [%s] failed, %s", m_slogFileName.c_str(), soldLogFileNewName.c_str(), strerror(errno));
    }
    init();
    return;
}

