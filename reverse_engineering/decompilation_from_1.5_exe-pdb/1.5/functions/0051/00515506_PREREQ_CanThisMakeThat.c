/*
 * Entry: 00515506
 * Name: PREREQ_CanThisMakeThat
 * Namespace: Global
 * Signature: uchar PREREQ_CanThisMakeThat(ushort param_1, ushort param_2, char param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

uchar __cdecl PREREQ_CanThisMakeThat(ushort param_1,ushort param_2,char param_3)

{
  uchar uVar1;
  ushort *puVar2;
  
  puVar2 = PREREQ_GetMakers(param_2);
  while( true ) {
    if (*puVar2 == 0) {
      return '\0';
    }
    uVar1 = PREREQ_TestEquivalent(*puVar2,param_3,param_1);
    if (uVar1 != '\0') break;
    puVar2 = puVar2 + 1;
  }
  return '\x01';
}
