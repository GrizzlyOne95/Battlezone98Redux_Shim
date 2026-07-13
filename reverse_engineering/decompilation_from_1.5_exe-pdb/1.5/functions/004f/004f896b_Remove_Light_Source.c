/*
 * Entry: 004f896b
 * Name: Remove_Light_Source
 * Namespace: Global
 * Signature: void Remove_Light_Source(_OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Remove_Light_Source(_OBJ76 *param_1)

{
  DYNAMIC_LIGHT *pDVar1;
  int iVar2;
  DYNAMIC_LIGHT **ppDVar3;
  int iVar4;
  
  iVar4 = 0;
  if (0 < Lights_Struct.Light_Counter) {
    pDVar1 = Lights_Struct.Lights_Array;
    do {
      if (param_1 == pDVar1->Light_Owner) {
        ppDVar3 = Lights_Struct.Apply_Lights + Lights_Struct.Light_Counter * 0x1b + 2;
        pDVar1 = Lights_Struct.Lights_Array + iVar4;
        Lights_Struct.Light_Counter = Lights_Struct.Light_Counter + -1;
        for (iVar2 = 0x1b; iVar2 != 0; iVar2 = iVar2 + -1) {
          pDVar1->Light_Owner = (_OBJ76 *)*ppDVar3;
          ppDVar3 = ppDVar3 + 1;
          pDVar1 = (DYNAMIC_LIGHT *)&pDVar1->flags;
        }
        return;
      }
      iVar4 = iVar4 + 1;
      pDVar1 = pDVar1 + 1;
    } while (iVar4 < Lights_Struct.Light_Counter);
  }
  return;
}
