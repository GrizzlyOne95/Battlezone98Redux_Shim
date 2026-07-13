/*
 * Entry: 00516c93
 * Name: tlog_ild
 * Namespace: Global
 * Signature: void tlog_ild(char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl tlog_ild(char *param_1)

{
  if (log_mode != 0) {
    vsprintf(scratch,param_1,&stack0x00000008);
    _tlog_filename = ".\\Schedule\\ScheduleGlue.cpp";
    _tlog_line = 0xc0c;
    tlog(0x800,scratch);
  }
  return;
}
