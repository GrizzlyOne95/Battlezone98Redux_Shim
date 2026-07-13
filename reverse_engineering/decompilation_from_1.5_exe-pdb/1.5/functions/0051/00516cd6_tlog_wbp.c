/*
 * Entry: 00516cd6
 * Name: tlog_wbp
 * Namespace: Global
 * Signature: void tlog_wbp(char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl tlog_wbp(char *param_1)

{
  if (log_mode != 0) {
    vsprintf(scratch,param_1,&stack0x00000008);
    _tlog_filename = ".\\Schedule\\ScheduleGlue.cpp";
    _tlog_line = 0xc17;
    tlog(0x8000,scratch);
  }
  return;
}
