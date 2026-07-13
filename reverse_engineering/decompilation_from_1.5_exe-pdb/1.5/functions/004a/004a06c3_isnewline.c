/*
 * Entry: 004a06c3
 * Name: isnewline
 * Namespace: Global
 * Signature: bool isnewline(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl isnewline(int param_1)

{
  if ((param_1 != 10) && (param_1 != 0xd)) {
    return false;
  }
  return true;
}
