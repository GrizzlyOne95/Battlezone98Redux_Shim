/*
 * Entry: 005263b1
 * Name: RegisterSurfaceAttributes
 * Namespace: Global
 * Signature: void RegisterSurfaceAttributes(SURFACE_ATTRIBUTE * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl RegisterSurfaceAttributes(SURFACE_ATTRIBUTE *param_1)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 *puVar4;
  
  puVar1 = (undefined4 *)&SurfaceTable;
  do {
    puVar2 = puVar1 + 5;
    puVar4 = (undefined4 *)((int)&param_1[-0xa2582].roughness + (int)puVar1);
    for (iVar3 = 5; iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar1 = *puVar4;
      puVar4 = puVar4 + 1;
      puVar1 = puVar1 + 1;
    }
    puVar1 = puVar2;
  } while ((int)puVar2 < 0xcaeec0);
  return;
}
