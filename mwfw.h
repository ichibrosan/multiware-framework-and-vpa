//
// Created by doug on 2/2/25.
//

#ifndef MWFW_H
#define MWFW_H

#include "CSysLog.hpp"

class mwfw {
  CSysLog * m_pSysLog;
  bool      m_bCGI;
public:
  mwfw();
  bool isCGI();
  void sl_loginfo(const char *);
};



#endif //MWFW_H
