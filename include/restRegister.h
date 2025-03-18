/////////////////////////////////////////////////////////////////////
// /home/devo/public_html/fw/restRegister.h 2025-03-18 03:40       //
// Copyright (c) 2025 Douglas Wade Goodall. All Rights Reserved.   //
/////////////////////////////////////////////////////////////////////

#ifndef RESTREGISTER_H
#define RESTREGISTER_H

xmlrpc_c::methodPtr const restMethodP(new restMethod);
myRegistry.addMethod("rest", restMethodP);

#endif //RESTREGISTER_H
