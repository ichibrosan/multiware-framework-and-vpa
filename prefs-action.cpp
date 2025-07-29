////////////////////////////////////////////////////////////////////
// ~/public_html/fw/mutations.cpp 2025-07-15 18:16 dwg -          //
// This file is part of MultiWare Engineering's VPA and FrameWork //
////////////////////////////////////////////////////////////////////

#include "mwfw2.h"

/**
 * The main function initializes necessary components, processes form
 * variables, updates shared memory with preferences, and creates objects
 * for user preferences, dashboard, and stylist. It performs the
 * following operations:
 * - Initializes schema and shared memory management.
 * - Retrieves and updates user preferences from a form.
 * - Sets preferences such as colors for body, table, rows, headers,
 *   and database elements.
 * - Prepares a dashboard and applies user-specific styles.
 *
 * @return An integer indicating the execution status. Returns 0 on
 *          successful execution.
 */
int main()
{
    mwfw2* pMwFw = new mwfw2(__FILE__, __FUNCTION__);

    gpSchema = new schema("prefs.csv");
    int h = atoi(gpCgiBind->get_form_variable("handle").c_str());
    std::string ssUsername = gpCgiBind->get_form_variable("username");
    std::string ssPassword = gpCgiBind->get_form_variable("pwname");

    std::string ssBodyFg = gpCgiBind->get_form_variable("bodyfgcolor");
    std::string ssBodyBg = gpCgiBind->get_form_variable("bodybgcolor");
    std::string ssTableFg = gpCgiBind->get_form_variable("tablefgcolor");
    std::string ssTableBg = gpCgiBind->get_form_variable("tablebgcolor");
    std::string ssTrFg = gpCgiBind->get_form_variable("trfgcolor");
    std::string ssTrBg = gpCgiBind->get_form_variable("trbgcolor");
    std::string ssThFg = gpCgiBind->get_form_variable("thfgcolor");
    std::string ssThBg = gpCgiBind->get_form_variable("thbgcolor");
    std::string ssTdFg = gpCgiBind->get_form_variable("tdfgcolor");
    std::string ssTdBg = gpCgiBind->get_form_variable("tdbgcolor");
    std::string ssDbFg = gpCgiBind->get_form_variable("dbfgcolor");
    std::string ssDbBg = gpCgiBind->get_form_variable("dbbgcolor");

    strcpy(gpSh->m_pShMemng->prefs[h].szBodyFGcolor, ssBodyFg.c_str());
    strcpy(gpSh->m_pShMemng->prefs[h].szBodyBGcolor, ssBodyBg.c_str());
    strcpy(gpSh->m_pShMemng->prefs[h].szTableFGcolor, ssTableFg.c_str());
    strcpy(gpSh->m_pShMemng->prefs[h].szTableBGcolor, ssTableBg.c_str());
    strcpy(gpSh->m_pShMemng->prefs[h].szTrFGcolor, ssTrFg.c_str());
    strcpy(gpSh->m_pShMemng->prefs[h].szTrBGcolor, ssTrBg.c_str());
    strcpy(gpSh->m_pShMemng->prefs[h].szThFGcolor, ssThFg.c_str());
    strcpy(gpSh->m_pShMemng->prefs[h].szThBGcolor, ssThBg.c_str());
    strcpy(gpSh->m_pShMemng->prefs[h].szTdFGcolor, ssTdFg.c_str());
    strcpy(gpSh->m_pShMemng->prefs[h].szTdBGcolor, ssTdBg.c_str());
    strcpy(gpSh->m_pShMemng->prefs[h].szDbFGcolor, ssDbFg.c_str());
    strcpy(gpSh->m_pShMemng->prefs[h].szDbBGcolor, ssDbBg.c_str());

    stylist* pStylist = new stylist(h);

    gpDash = new dashboard(h, JOURNAL | LOGOUT,__FILE__,
                           ssUsername, ssPassword);
    gpSchema->gen_from_schema(CFG_HANDLE_NA);
    // if(pMwFw->isCGI()) {
    //     gpHtml->dump_schema();
    //     gpHtml->dump_shm_vars();
    //     gpHtml->dump_env_vars();
    // }
    return 0;
}

////////////////////
// eof - menu.cpp //
////////////////////
