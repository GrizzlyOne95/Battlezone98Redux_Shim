
void FUN_0083c537(int *param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = *param_1;
  FUN_0083cfe1(param_1,param_1[8],param_1[6],0xff,param_1[6]);
  param_1[8] = -1;
  if (*(int *)(iVar1 + 0x2c) < param_1[6] + 1) {
    uVar2 = FUN_008387f7(param_1[4],*(undefined4 *)(iVar1 + 0xc),(int *)(iVar1 + 0x2c),4,0x7ffffffd,
                         "code size overflow");
    *(undefined4 *)(iVar1 + 0xc) = uVar2;
  }
  *(undefined4 *)(*(int *)(iVar1 + 0xc) + param_1[6] * 4) = param_2;
  if (*(int *)(iVar1 + 0x30) < param_1[6] + 1) {
    uVar2 = FUN_008387f7(param_1[4],*(undefined4 *)(iVar1 + 0x14),(int *)(iVar1 + 0x30),4,0x7ffffffd
                         ,"code size overflow");
    *(undefined4 *)(iVar1 + 0x14) = uVar2;
  }
  *(undefined4 *)(*(int *)(iVar1 + 0x14) + param_1[6] * 4) = param_3;
  param_1[6] = param_1[6] + 1;
  return;
}

