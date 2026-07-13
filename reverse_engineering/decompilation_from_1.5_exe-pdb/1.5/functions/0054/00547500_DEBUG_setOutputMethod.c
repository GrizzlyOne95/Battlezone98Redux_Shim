/*
 * Entry: 00547500
 * Name: DEBUG_setOutputMethod
 * Namespace: Global
 * Signature: long DEBUG_setOutputMethod(long param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long __cdecl DEBUG_setOutputMethod(long param_1)

{
  if ((uint)param_1 < 5) {
    DebugOutputMethod = param_1;
    return 0;
  }
  return 2;
}
