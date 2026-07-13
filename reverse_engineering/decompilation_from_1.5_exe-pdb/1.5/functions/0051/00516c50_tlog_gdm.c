/*
 * Entry: 00516c50
 * Name: tlog_gdm
 * Namespace: Global
 * Signature: void tlog_gdm(char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl tlog_gdm(char *param_1)

{
  if (log_mode != 0) {
    vsprintf(scratch,param_1,&stack0x00000008);
    _tlog_filename = ".\\Schedule\\ScheduleGlue.cpp";
    _tlog_line = 0xc00;
    tlog(0x200,scratch);
  }
  return;
}
