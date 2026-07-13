/*
 * Entry: 0054f5c3
 * Name: Scroll_ShowRegion
 * Namespace: Global
 * Signature: void Scroll_ShowRegion(void * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Scroll_ShowRegion(void *param_1,int param_2)

{
  int iVar1;
  long lVar2;
  
  iVar1 = *(int *)((int)param_1 + 8);
  *(uint *)(iVar1 + 0x60) = -(uint)(param_2 != 0) & 2 | *(uint *)(iVar1 + 0x60) & 0xfffffffd;
  lVar2 = Get_Closest_RGB_Entry
                    ((float)*(byte *)(iVar1 + 0x2c) * 0.003921569,
                     (float)*(byte *)(iVar1 + 0x2d) * 0.003921569,
                     (float)*(byte *)(iVar1 + 0x2e) * 0.003921569);
  *(long *)(iVar1 + 0x30) = lVar2;
  return;
}
