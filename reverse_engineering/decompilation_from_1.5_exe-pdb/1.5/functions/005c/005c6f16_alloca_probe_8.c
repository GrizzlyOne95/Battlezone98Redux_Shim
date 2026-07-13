/*
 * Entry: 005c6f16
 * Name: __alloca_probe_8
 * Namespace: Global
 * Signature: undefined __alloca_probe_8()
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: This is an inlined function */
/* WARNING: Function: _chkstk replaced with injection: alloca_probe */

uint __alloca_probe_8(void)

{
  uint in_EAX;
  uint uVar1;
  
  uVar1 = 4 - in_EAX & 7;
  return in_EAX + uVar1 | -(uint)CARRY4(in_EAX,uVar1);
}
