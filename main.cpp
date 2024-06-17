/*
NOCRASH_QMM - Anti-Vsay-Exploit Plugin
Copyright 2004-2024
https://github.com/thecybermind/nocrash_qmm/
3-clause BSD license: https://opensource.org/license/bsd-3-clause

Created By:
    Kevin Masterson < cybermind@gmail.com >

*/

#include "version.h"
#include <q_shared.h>
#include <g_local.h>
#include <qmmapi.h>
#include <string.h>

pluginres_t* g_result = NULL;
plugininfo_t g_plugininfo = {
	"NoCrash",				//name of plugin
	NOCRASH_QMM_VERSION,			//version of plugin
	"Stops the vsay crash exploit",		//description of plugin
	NOCRASH_QMM_BUILDER,			//author of plugin
	"http://www.q3mm.org/",			//website of plugin
	0,					//can this plugin be paused?
	1,					//can this plugin be loaded via cmd
	1,					//can this plugin be unloaded via cmd
	QMM_PIFV_MAJOR,				//plugin interface version major
	QMM_PIFV_MINOR				//plugin interface version minor
};
eng_syscall_t g_syscall = NULL;
mod_vmMain_t g_vmMain = NULL;
pluginfuncs_t* g_pluginfuncs = NULL;
int g_vmbase = 0;

C_DLLEXPORT void QMM_Query(plugininfo_t** pinfo) {
	*pinfo = &g_plugininfo;
}

C_DLLEXPORT int QMM_Attach(eng_syscall_t engfunc, mod_vmMain_t modfunc, pluginres_t* presult, pluginfuncs_t* pluginfuncs, int vmbase, int iscmd) {
	g_syscall = engfunc;
	g_vmMain = modfunc;
	g_result = presult;
	g_vmbase = vmbase;
	g_pluginfuncs = pluginfuncs;

	iscmd = 0;

	return 1;
}

C_DLLEXPORT void QMM_Detach(int iscmd) {
	iscmd = 0;
}

C_DLLEXPORT int QMM_vmMain(int cmd, int arg0, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7, int arg8, int arg9, int arg10, int arg11) {
	QMM_RET_IGNORED(1);
}

C_DLLEXPORT int QMM_syscall(int cmd, int arg0, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7, int arg8, int arg9, int arg10, int arg11, int arg12) {
	if (cmd == G_SEND_SERVER_COMMAND) {
		if (arg1 && strlen((char*)arg1) > 1022) {
			QMM_RET_SUPERCEDE(1);
		}
	}
	QMM_RET_IGNORED(1);
}

C_DLLEXPORT int QMM_vmMain_Post(int cmd, int arg0, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7, int arg8, int arg9, int arg10, int arg11) {
	QMM_RET_IGNORED(1);
}

C_DLLEXPORT int QMM_syscall_Post(int cmd, int arg0, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7, int arg8, int arg9, int arg10, int arg11, int arg12) {
	QMM_RET_IGNORED(1);
}
