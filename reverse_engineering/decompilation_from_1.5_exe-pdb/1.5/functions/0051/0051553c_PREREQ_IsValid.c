/*
 * Entry: 0051553c
 * Name: PREREQ_IsValid
 * Namespace: Global
 * Signature: uchar PREREQ_IsValid(ushort param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

uchar __cdecl PREREQ_IsValid(ushort param_1)

{
  uchar uVar1;
  
  uVar1 = '\x01';
  if ((param_1 == 0) || (PREREQ_maxassigned <= (int)(uint)param_1)) {
    uVar1 = '\0';
  }
  return uVar1;
}
