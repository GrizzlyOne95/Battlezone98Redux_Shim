/*
 * Entry: 004ca31c
 * Name: EditTerrain::RandomFlip
 * Namespace: EditTerrain
 * Signature: int RandomFlip(EditTerrain * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __thiscall EditTerrain::RandomFlip(EditTerrain *this,int param_1)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = rand();
  if (((param_1 >> 4 ^ param_1) & 0xf00U) == 0) {
    uVar2 = iVar1 >> 9 & 0x30U | param_1 & 0xffffff8fU;
  }
  else {
    uVar2 = param_1 ^ param_1 & 0x40U;
  }
  return uVar2;
}
