
int FUN_00831196(int param_1,uint *param_2)

{
  uint uVar1;
  int iVar2;
  
  uVar1 = param_2[2];
  if (uVar1 == 1) {
    uVar1 = (1 << (*(byte *)(param_1 + 7) & 0x1f)) - 1U & *param_2;
LAB_00831204:
    iVar2 = uVar1 * 0x20 + *(int *)(param_1 + 0x10);
  }
  else {
    if (uVar1 != 2) {
      if (uVar1 == 3) {
        iVar2 = FUN_00830d4e(param_1,*(undefined8 *)param_2);
        return iVar2;
      }
      if (uVar1 == 4) {
        uVar1 = (1 << (*(byte *)(param_1 + 7) & 0x1f)) - 1U & *(uint *)(*param_2 + 8);
        goto LAB_00831204;
      }
    }
    iVar2 = (*param_2 % ((1 << (*(byte *)(param_1 + 7) & 0x1f)) - 1U | 1)) * 0x20 +
            *(int *)(param_1 + 0x10);
  }
  return iVar2;
}

