
void FUN_0082c61c(int param_1,int param_2)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  
  if (param_2 < 2) {
    if (param_2 == 0) {
      puVar1 = *(undefined4 **)(param_1 + 8);
      uVar2 = FUN_008309f4(param_1,&DAT_008a1ad8,0);
      *puVar1 = uVar2;
      puVar1[2] = 4;
      *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + 0x10;
    }
  }
  else {
    if (*(uint *)(*(int *)(param_1 + 0x10) + 0x40) <= *(uint *)(*(int *)(param_1 + 0x10) + 0x44)) {
      FUN_00830222(param_1);
    }
    FUN_00831f3a(param_1,param_2,(*(int *)(param_1 + 8) - *(int *)(param_1 + 0xc) >> 4) + -1);
    *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + param_2 * -0x10 + 0x10;
  }
  return;
}

