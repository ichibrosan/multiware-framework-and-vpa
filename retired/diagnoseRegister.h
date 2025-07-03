/////////////////////////////////////////////////////////////////////
// /home/devo/public_html/fw/diagnoseRegister.h 2025-03-148 12:28  //
// Derived from xmlrpc-c/examples/cpp/xmlrpc_sample_add_client.cpp //
// Copyright (c) 2025 Douglas Wade Goodall. All Rights Reserved.   //
/////////////////////////////////////////////////////////////////////

#ifndef DIAGNOSEREGISTER_H
#define DIAGNOSEREGISTER_H

xmlrpc_c::methodPtr const diagnoseMethodP(new diagnoseMethod);
myRegistry.addMethod("diagnose", diagnoseMethodP);

#endif //DIAGNOSEREGISTER_H
