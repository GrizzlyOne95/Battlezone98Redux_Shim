
void __fastcall FUN_005b3cb0(int *param_1)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  void *pvVar5;
  int local_60;
  int local_58;
  int local_4c;
  int local_44;
  int local_3c;
  int local_34;
  int local_2c;
  int local_24;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084c490;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  switch(param_1[6]) {
  case 1:
  case 2:
    pvVar5 = operator_new(0x134);
    local_8 = 0;
    if (pvVar5 == (void *)0x0) {
      local_24 = 0;
    }
    else {
      local_24 = FUN_00608580(param_1[8]);
    }
    param_1[0xb] = local_24;
    break;
  case 3:
    (**(code **)(*param_1 + 0x24))();
    break;
  case 4:
    iVar4 = FUN_00462630(param_1[9]);
    if (iVar4 == 0) {
      pvVar5 = operator_new(0x14c);
      local_8 = 3;
      if (pvVar5 == (void *)0x0) {
        local_3c = 0;
      }
      else {
        local_3c = FUN_004e54c0(param_1[8],param_1[4],1);
      }
      param_1[0xb] = local_3c;
    }
    else {
      iVar2 = (*(code *)**(undefined4 **)(iVar4 + 0x18))();
      if (*(int *)(iVar2 + 0x14) == 0x4745495a) {
        pvVar5 = operator_new(0x154);
        local_8 = 1;
        if (pvVar5 == (void *)0x0) {
          local_2c = 0;
        }
        else {
          local_2c = FUN_004e49b0(param_1[8],iVar4);
        }
        param_1[0xb] = local_2c;
      }
      else {
        pvVar5 = operator_new(0x14c);
        local_8 = 2;
        if (pvVar5 == (void *)0x0) {
          local_34 = 0;
        }
        else {
          local_34 = FUN_004e58d0(param_1[8],iVar4);
        }
        param_1[0xb] = local_34;
      }
    }
    break;
  case 5:
    uVar3 = FUN_00462630(param_1[9]);
    pvVar5 = operator_new(0x134);
    local_8 = 4;
    if (pvVar5 == (void *)0x0) {
      local_44 = 0;
    }
    else {
      local_44 = FUN_004d3790(param_1[8],uVar3);
    }
    param_1[0xb] = local_44;
    break;
  case 6:
    pvVar5 = operator_new(0x134);
    local_8 = 5;
    if (pvVar5 == (void *)0x0) {
      local_4c = 0;
    }
    else {
      local_4c = FUN_00608580(param_1[8]);
    }
    local_8 = 0xffffffff;
    param_1[0xb] = local_4c;
    cVar1 = FUN_005aecb0(param_1[0xc]);
    if (cVar1 == '\0') {
      param_1[7] = 2;
    }
    else {
      FUN_005f91e0(param_1[8],0x10,0);
    }
    break;
  case 7:
    iVar4 = FUN_00463120(param_1[8],DAT_008e7000 ^ (uint)&stack0xfffffffc);
    if (iVar4 == 0) {
      param_1[0xb] = 0;
    }
    else {
      pvVar5 = operator_new(0x14c);
      local_8 = 6;
      if (pvVar5 == (void *)0x0) {
        local_58 = 0;
      }
      else {
        local_58 = FUN_004e58d0(param_1[8],iVar4);
      }
      param_1[0xb] = local_58;
    }
    break;
  case 8:
    pvVar5 = operator_new(0x154);
    local_8 = 7;
    if (pvVar5 == (void *)0x0) {
      local_60 = 0;
    }
    else {
      local_60 = FUN_004e48e0(param_1[8]);
    }
    param_1[0xb] = local_60;
  }
  ExceptionList = local_10;
  return;
}

