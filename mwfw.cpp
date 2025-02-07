//
// Created by doug on 2/2/25.
//

#include "mwfw.h"

mwfw::mwfw()
{
	m_bCGI = false;
	char * ptr = getenv("SERVER_PORT");
	if(nullptr != ptr) {
		m_bCGI = true;
	}

	if(isCGI()) {
		std::cout << "content-type:\ttext/html\n\n" << std::endl;
	}

	m_pSysLog = new CSysLog();
	m_pSysLog->loginfo(__PRETTY_FUNCTION__);


}

bool mwfw::isCGI()
{
	return m_bCGI;
}

void mwfw::sl_loginfo(const char *pszMsg)
{
  m_pSysLog->loginfo(pszMsg);
}