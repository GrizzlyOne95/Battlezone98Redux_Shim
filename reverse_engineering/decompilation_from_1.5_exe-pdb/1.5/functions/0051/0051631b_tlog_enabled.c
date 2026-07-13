/*
 * Entry: 0051631b
 * Name: tlog_enabled
 * Namespace: Global
 * Signature: bool tlog_enabled(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl tlog_enabled(int param_1)

{
  return (log_mode & param_1) != 0;
}
