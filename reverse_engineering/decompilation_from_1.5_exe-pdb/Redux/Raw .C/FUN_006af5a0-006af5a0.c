
int FUN_006af5a0(int param_1,byte param_2,int param_3,int param_4,uint *param_5,int *param_6,
                undefined4 *param_7)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  int iVar4;
  uint local_c;
  
  if (param_1 == -1) {
    FUN_006d8cf0(0x2719);
    iVar1 = -1;
  }
  else if ((param_3 == -0x5af00000) && (param_4 == 2)) {
    FUN_006d8cf0(0x2726);
    iVar1 = -1;
  }
  else if ((param_3 == -0x5af00000) && (param_4 == 1)) {
    if (*param_6 == 4) {
      local_c = (uint)((param_2 & 4) != 0);
      *param_5 = local_c;
      puVar2 = (undefined4 *)FUN_004fbb60();
      uVar3 = puVar2[1];
      *param_7 = *puVar2;
      param_7[1] = uVar3;
      iVar1 = 0;
    }
    else {
      FUN_006d8cf0(0x2726);
      iVar1 = -1;
    }
  }
  else {
    FUN_006ae8d0();
    uVar3 = FUN_006d8e50(0,param_1,param_3,param_4,param_5,param_6,param_7);
    iVar1 = FUN_006d8d90(uVar3);
    if ((((iVar1 != 0) && (param_3 == 0x29)) && (param_4 == 0x1b)) &&
       ((iVar4 = get(), iVar4 == 0x273a && (*param_6 == 4)))) {
      *param_5 = 1;
      puVar2 = (undefined4 *)FUN_004fbb60();
      uVar3 = puVar2[1];
      *param_7 = *puVar2;
      param_7[1] = uVar3;
    }
    if (iVar1 == 0) {
      puVar2 = (undefined4 *)FUN_004fbb60();
      uVar3 = puVar2[1];
      *param_7 = *puVar2;
      param_7[1] = uVar3;
    }
  }
  return iVar1;
}

