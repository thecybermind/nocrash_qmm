/*
NoCrash - QMM Plugin to fix q3msgboom  
Copyright 2026  
https://github.com/thecybermind/nocrash_qmm/  
3-clause BSD license: https://opensource.org/license/bsd-3-clause

Created By:
    Kevin Masterson < k.m.masterson@gmail.com >

*/

#define _CRT_SECURE_NO_WARNINGS 1
#include <string.h>

#include <qmmapi.h>
#include "version.h"

plugin_info g_plugininfo = {
    QMM_PIFV_MAJOR,                                  // plugin interface version major
    QMM_PIFV_MINOR,                                  // plugin interface version minor
    "NoCrash",                                       // name of plugin
    NOCRASH_QMM_VERSION,                             // version of plugin
    "Fix for q3msgboom",                             // description of plugin
    NOCRASH_QMM_BUILDER,                             // author of plugin
    "https://github.com/thecybermind/nocrash_qmm/",  // website of plugin
    "NOCRASH",                                       // log tag
};
plugin_funcs g_pluginfuncs;
plugin_vars g_pluginvars;


C_DLLEXPORT void QMM_Query(plugin_info** plugininfo, plugin_funcs** pluginfuncs, plugin_vars** pluginvars) {
    QMM_GIVE_PTRS();
}


intptr_t G_SEND_SERVER_COMMAND = 0;
intptr_t G_SEND_SERVER_COMMAND_ARGNUM = 1;


C_DLLEXPORT int QMM_Attach() {
    const char* engine = QMM_GETGAMEENGINE();

    if (!engine)
        return 0;

    // get G_SEND_SERVER_COMMAND value based on engine code
    if (strcmp(engine, "JK2MP") == 0 || strcmp(engine, "Q3A") == 0 || strcmp(engine, "STVOYHM") == 0)
        G_SEND_SERVER_COMMAND = 17;
    else if (strcmp(engine, "RTCWMP") == 0)
        G_SEND_SERVER_COMMAND = 18;
    else if (strcmp(engine, "RTCWSP") == 0 || strcmp(engine, "SOF2MP") == 0 || strcmp(engine, "JAMP") == 0 || strcmp(engine, "WET") == 0)
        G_SEND_SERVER_COMMAND = 19;
    else if (strcmp(engine, "JK2SP") == 0 || strcmp(engine, "STVOYSP") == 0)
        G_SEND_SERVER_COMMAND = 22;
    else if (strcmp(engine, "JASP") == 0)
        G_SEND_SERVER_COMMAND = 23;
    else if (strcmp(engine, "MOHAA") == 0)
        G_SEND_SERVER_COMMAND = 36;
    else if (strcmp(engine, "MOHBT") == 0 || strcmp(engine, "MOHSH") == 0)
        G_SEND_SERVER_COMMAND = 39;
    else if (strcmp(engine, "STEF2") == 0)
        G_SEND_SERVER_COMMAND = 41;
    else if (strcmp(engine, "SOF2SP") == 0)
        G_SEND_SERVER_COMMAND = 55;
    // server command string is 2nd arg in COD games, but 1st arg in all other games
    else if (strcmp(engine, "COD11MP") == 0) {
        G_SEND_SERVER_COMMAND = 26;
        G_SEND_SERVER_COMMAND_ARGNUM = 2;
    }
    // server command string is 2nd arg in COD games, but 1st arg in all other games
    else if (strcmp(engine, "CODMP") == 0 || strcmp(engine, "CODUOMP") == 0) {
        G_SEND_SERVER_COMMAND = 27;
        G_SEND_SERVER_COMMAND_ARGNUM = 2;
    }
    else {
        // Q2R, QUAKE2, SIN, SOF don't need this plugin
        QMM_WRITEQMMLOG(QMMLOG_ERROR, "NoCrash doesn't support engine %s\n", engine);
        return 0;
    }

    return 1;
}


C_DLLEXPORT void QMM_Detach() {
}


C_DLLEXPORT intptr_t QMM_vmMain(result_vars* results, intptr_t cmd, intptr_t* args) {
    QMM_RET_IGNORED(0);
}


C_DLLEXPORT intptr_t QMM_vmMain_Post(result_vars* results, intptr_t cmd, intptr_t* args) {
    QMM_RET_IGNORED(0);
}


C_DLLEXPORT intptr_t QMM_syscall(result_vars* results, intptr_t cmd, intptr_t* args) {
    if (cmd == G_SEND_SERVER_COMMAND) {
        const char* msg = (const char*)args[G_SEND_SERVER_COMMAND_ARGNUM];
        if (msg && strlen(msg) > 1022)
            QMM_RET_SUPERCEDE(0);
    }

    QMM_RET_IGNORED(0);
}


C_DLLEXPORT intptr_t QMM_syscall_Post(result_vars* results, intptr_t cmd, intptr_t* args) {
    QMM_RET_IGNORED(0);
}
