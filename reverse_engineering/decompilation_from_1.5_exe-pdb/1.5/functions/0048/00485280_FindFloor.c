/*
 * Entry: 00485280
 * Name: FindFloor
 * Namespace: Global
 * Signature: float FindFloor(VECTOR_3D_LONG param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

float __cdecl FindFloor(VECTOR_3D_LONG param_1)

{
  int iVar1;
  undefined4 *puVar2;
  VECTOR_3D_LONG in_stack_ffffffd0;
  float *pfVar3;
  VECTOR_3D *pVVar4;
  float local_8;
  
  pVVar4 = (VECTOR_3D *)0x0;
  pfVar3 = &local_8;
  puVar2 = (undefined4 *)&stack0xffffffd0;
  for (iVar1 = 6; register0x00000010 = (BADSPACEBASE *)((int)register0x00000010 + 4), iVar1 != 0;
      iVar1 = iVar1 + -1) {
    *puVar2 = *(undefined4 *)register0x00000010;
    puVar2 = puVar2 + 1;
  }
  Floor_GetFloor(in_stack_ffffffd0,pfVar3,pVVar4);
  return local_8;
}
