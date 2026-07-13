/*
 * Entry: 00515080
 * Name: PREREQ_Log
 * Namespace: Global
 * Signature: void PREREQ_Log(ushort param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl PREREQ_Log(ushort param_1)

{
  tlog(0x100,
       "TYPE: %d #: %d SIDE: %d PREQ: %d MAKE: %d PLAN: %d REQS: %d %d %d %d MAKERS: %d %d %d %d ");
  return;
}
