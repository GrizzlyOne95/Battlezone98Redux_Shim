
int FUN_006af6f0(int param_1,undefined4 param_2,undefined4 param_3,char param_4,undefined4 *param_5)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  undefined4 local_10;
  int local_c;
  int local_8;
  
  if (param_1 == -1) {
    FUN_006d8cf0(0x2719);
    local_c = -1;
  }
  else if (param_4 == '\0') {
    FUN_006ae8d0();
    uVar3 = FUN_006d8e90(0,param_1,param_2,param_3,param_5);
    local_c = FUN_006d8d90(uVar3);
    if (local_c == 0) {
      puVar2 = (undefined4 *)FUN_004fbb60();
      uVar3 = puVar2[1];
      *param_5 = *puVar2;
      param_5[1] = uVar3;
    }
  }
  else {
    local_8 = 0;
    local_10 = 4;
    iVar1 = FUN_006af5a0(param_1,0,0xffff,0x700c,&local_8,&local_10,param_5);
    if (iVar1 == -1) {
      local_c = -1;
    }
    else if (local_8 == -1) {
      FUN_006d8cf0(0x2749);
      local_c = -1;
    }
    else {
      puVar2 = (undefined4 *)FUN_004fbb60();
      uVar3 = puVar2[1];
      *param_5 = *puVar2;
      param_5[1] = uVar3;
      local_c = 0;
    }
  }
  return local_c;
}

