/*
 * Entry: 00582369
 * Name: TextInput_ShowRegion
 * Namespace: Global
 * Signature: void TextInput_ShowRegion(void * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl TextInput_ShowRegion(void *param_1,int param_2)

{
  int iVar1;
  long lVar2;
  
  iVar1 = *(int *)((int)param_1 + 8);
  *(uint *)(iVar1 + 0x124) = (uint)(param_2 != 0) | *(uint *)(iVar1 + 0x124) & 0xfffffffe;
  lVar2 = Get_Closest_RGB_Entry
                    ((float)*(byte *)(iVar1 + 0x11c) * 0.00390625,
                     (float)*(byte *)(iVar1 + 0x11d) * 0.00390625,
                     (float)*(byte *)(iVar1 + 0x11e) * 0.00390625);
  *(long *)(iVar1 + 0x120) = lVar2;
  return;
}
