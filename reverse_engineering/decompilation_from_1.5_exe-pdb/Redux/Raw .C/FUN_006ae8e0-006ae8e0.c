
int FUN_006ae8e0(int param_1,undefined4 param_2,undefined4 param_3,undefined4 *param_4)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  
  if (param_1 == -1) {
    FUN_006d8cf0(0x2719);
    iVar1 = -1;
  }
  else {
    FUN_006ae8d0();
    uVar2 = FUN_006d8d20(0,param_1,param_2,param_3,param_4);
    iVar1 = FUN_006d8d90(uVar2);
    if (iVar1 != -1) {
      puVar3 = (undefined4 *)FUN_004fbb60();
      uVar2 = puVar3[1];
      *param_4 = *puVar3;
      param_4[1] = uVar2;
    }
  }
  return iVar1;
}

