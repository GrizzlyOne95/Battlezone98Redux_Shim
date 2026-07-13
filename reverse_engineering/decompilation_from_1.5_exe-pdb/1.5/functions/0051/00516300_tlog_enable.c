/*
 * Entry: 00516300
 * Name: tlog_enable
 * Namespace: Global
 * Signature: void tlog_enable(int param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl tlog_enable(int param_1,int param_2)

{
  if (param_2 != 0) {
    log_mode = log_mode | param_1;
    return;
  }
  log_mode = log_mode & ~param_1;
  return;
}
