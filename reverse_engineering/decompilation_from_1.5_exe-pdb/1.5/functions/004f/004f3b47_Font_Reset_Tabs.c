/*
 * Entry: 004f3b47
 * Name: Font_Reset_Tabs
 * Namespace: Global
 * Signature: void Font_Reset_Tabs(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Font_Reset_Tabs(void)

{
  int iVar1;
  int *piVar2;
  
  piVar2 = tabdefs;
  iVar1 = 0x20;
  do {
    *piVar2 = iVar1;
    iVar1 = iVar1 + 0x20;
    piVar2 = piVar2 + 1;
  } while (iVar1 < 0x120);
  return;
}
