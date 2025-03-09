//
// Created by doug on 2/21/25.
//

#ifndef RPCBIND_H
#define RPCBIND_H



class rpcbind {
public:
    rpcbind();
    std::string vpa_call(vpa_request_t& req);
};



#endif //RPCBIND_H
