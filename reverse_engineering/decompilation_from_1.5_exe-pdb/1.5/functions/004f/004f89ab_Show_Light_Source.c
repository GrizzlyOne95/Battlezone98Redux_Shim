/*
 * Entry: 004f89ab
 * Name: Show_Light_Source
 * Namespace: Global
 * Signature: void Show_Light_Source(_OBJ76 * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok_supplemented
 */

void __cdecl Show_Light_Source(_OBJ76 *param_1,int param_2)

{
  ulong *puVar1;
  int iVar2;
  DYNAMIC_LIGHT *pDVar3;
  
  iVar2 = 0;
  if (0 < Lights_Struct.Light_Counter) {
    pDVar3 = Lights_Struct.Lights_Array;
    while (param_1 != pDVar3->Light_Owner) {
      iVar2 = iVar2 + 1;
      pDVar3 = pDVar3 + 1;
      if (Lights_Struct.Light_Counter <= iVar2) {
        return;
      }
    }
    puVar1 = &Lights_Struct.Lights_Array[iVar2].flags;
    *puVar1 = -(uint)(param_2 != 0) & 8 | *puVar1 & 0xfffffff7;
  }
  return;
}
