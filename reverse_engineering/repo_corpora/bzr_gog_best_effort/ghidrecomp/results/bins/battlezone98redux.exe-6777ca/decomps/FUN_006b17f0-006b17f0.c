
undefined4 *
FUN_006b17f0(undefined4 *param_1,undefined4 *param_2,undefined4 param_3,int param_4,
            undefined4 param_5,undefined4 *param_6)

{
  char cVar1;
  uint uVar2;
  undefined4 uVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined1 local_2c [8];
  undefined4 local_24;
  int local_20;
  undefined1 local_11;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008505a8;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  cVar1 = FUN_006b1390(param_2);
  if (cVar1 == '\0') {
    uVar3 = FUN_006af3f0(param_3,param_4,param_5,param_6,uVar2);
    FUN_006b0020(uVar3);
    local_8 = 0;
    iVar4 = get();
    if (iVar4 == -1) {
      uVar3 = param_6[1];
      *param_1 = *param_6;
      param_1[1] = uVar3;
      local_8 = 0xffffffff;
      FUN_006b0040();
    }
    else {
      local_24 = get();
      FUN_006ad2a0(local_2c,local_24,param_6);
      iVar4 = FUN_00667170();
      if (iVar4 == 0) {
        uVar3 = FUN_006b00c0();
        *param_2 = uVar3;
        local_20 = param_4;
        if (param_4 == 1) {
          *(undefined1 *)(param_2 + 1) = 0x10;
        }
        else if (param_4 == 2) {
          *(undefined1 *)(param_2 + 1) = 0x20;
        }
        else {
          *(undefined1 *)(param_2 + 1) = 0;
        }
        local_11 = 0;
        FUN_006d9020(0,0);
        puVar5 = (undefined4 *)FUN_004fbb60();
        uVar3 = puVar5[1];
        *param_6 = *puVar5;
        param_6[1] = uVar3;
        uVar3 = param_6[1];
        *param_1 = *param_6;
        param_1[1] = uVar3;
        local_8 = 0xffffffff;
        FUN_006b0040();
      }
      else {
        uVar3 = param_6[1];
        *param_1 = *param_6;
        param_1[1] = uVar3;
        local_8 = 0xffffffff;
        FUN_006b0040();
      }
    }
  }
  else {
    FUN_006d8e00(1);
    uVar3 = param_6[1];
    *param_1 = *param_6;
    param_1[1] = uVar3;
  }
  ExceptionList = local_10;
  return param_1;
}

