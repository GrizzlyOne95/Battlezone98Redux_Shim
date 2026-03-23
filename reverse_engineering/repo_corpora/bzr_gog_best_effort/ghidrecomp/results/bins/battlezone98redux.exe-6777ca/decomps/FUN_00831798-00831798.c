
void FUN_00831798(int param_1,undefined4 param_2)

{
  undefined8 *puVar1;
  int iVar2;
  int iVar3;
  undefined8 local_10;
  int local_8;
  
  iVar2 = *(int *)(param_1 + 0x28);
  FUN_008319c8(iVar2,param_2);
  if (0 < iVar2) {
    local_8 = 0;
    do {
      puVar1 = (undefined8 *)(*(int *)(param_1 + 8) + local_8);
      FUN_0083177c(*(undefined4 *)(puVar1 + 1),param_2);
      iVar3 = *(int *)(puVar1 + 1);
      if (iVar3 == 1) {
        FUN_0083177c(*(undefined4 *)puVar1,param_2);
      }
      else if (iVar3 == 3) {
        local_10 = *puVar1;
        FUN_00831758(&local_10,8,param_2);
      }
      else if (iVar3 == 4) {
        FUN_008319de(*(undefined4 *)puVar1,param_2);
      }
      local_8 = local_8 + 0x10;
      iVar2 = iVar2 + -1;
    } while (iVar2 != 0);
  }
  iVar3 = 0;
  iVar2 = *(int *)(param_1 + 0x34);
  FUN_008319c8(iVar2,param_2);
  if (0 < iVar2) {
    do {
      FUN_00831931(*(undefined4 *)(*(int *)(param_1 + 0x10) + iVar3 * 4),
                   *(undefined4 *)(param_1 + 0x20),param_2);
      iVar3 = iVar3 + 1;
    } while (iVar3 < iVar2);
  }
  return;
}

