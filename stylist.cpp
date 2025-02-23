//
// Created by doug on 2/23/25.
//

#include "mwfw2.h"
#include "stylist.h"

char sz_default_button[] = {
"    .default_button\n"
"    {\n"
"        text-decoration:  none;\n"
"        color: #ffffff;\n"
"        font-size: 24px;\n"
"        font-family: Arial;\n"
"        background:linear-gradient(#ffff00, #ff0000);\n"
"        box-shadow: 5px 5px 10px #000000, 0px 0px 0px 2px #000000;\n"
"        border-top: #ffff00 3px groove;\n"
"        border-left: #ffff00 3px groove;\n"
"        border-right: #ff0000 3px groove;\n"
"        border-bottom: #ff0000 3px groove;\n"
"        border-radius: 10px;\n"
"        -webkit-text-stroke-width: 1px;\n"
"        -webkit-text-stroke-color: #000000;\n"
"        padding-left: 10px;\n"
"        padding-right: 10px;\n"
"    }\n"
};

char sz_journal_container[] = {
"    .journal_container\n"
"    {\n"
"        position: fixed;\n"
"        top: 0;\n"
"        left: 0;\n"
"        grid-template-columns: repeat(2, 29ch) repeat(2, 27ch);\n"
"        grid-template-rows: repeat(4, 7cap);\n"
"        width: 112ch;\n"
"        height: 27.2cap;\n"
"        display: grid;\n"
"    }\n"
};

char szReturn[BUFSIZ];

stylist::stylist() {
    std::string ssCssFQFS =
        "/home/devo/public_html/fw/styles/exp.css";
    FILE * fp = fopen(ssCssFQFS.c_str(),"w");
    fprintf(fp,"%s\n",default_button());
    fprintf(fp,"%s\n",journal_container());

    fclose(fp);
}

const char * stylist::default_button() {
    sprintf(szReturn,"%s",sz_default_button);
    return szReturn;
}

const char * stylist::journal_container() {
    sprintf(szReturn,"%s",sz_journal_container);
    return szReturn;
}