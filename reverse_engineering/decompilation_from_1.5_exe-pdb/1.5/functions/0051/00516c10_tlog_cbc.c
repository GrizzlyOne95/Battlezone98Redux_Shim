/*
 * Entry: 00516c10
 * Name: tlog_cbc
 * Namespace: Global
 * Signature: void tlog_cbc(char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl tlog_cbc(char *param_1)

{
  if (log_mode != 0) {
    vsprintf(scratch,param_1,&stack0x00000008);
    _tlog_filename = ".\\Schedule\\ScheduleGlue.cpp";
    _tlog_line = 0xbf5;
    tlog(0x20,scratch);
  }
  return;
}
