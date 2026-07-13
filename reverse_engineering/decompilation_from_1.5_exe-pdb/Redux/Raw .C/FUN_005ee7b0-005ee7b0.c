
void __fastcall FUN_005ee7b0(int param_1)

{
  uint uVar1;
  int *piVar2;
  int iVar3;
  undefined4 uVar4;
  void *pvVar5;
  undefined4 local_64;
  undefined4 local_5c;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_20;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084cfec;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  switch(*(undefined4 *)(param_1 + 0x18)) {
  case 2:
    if (*(float *)(param_1 + 0x28) == -1e+30) {
      pvVar5 = operator_new(0x14c);
      local_8 = 0;
      if (pvVar5 == (void *)0x0) {
        local_28 = 0;
      }
      else {
        local_28 = FUN_004e54c0(*(undefined4 *)(param_1 + 0x20),
                                *(undefined4 *)(*(int *)(param_1 + 0x20) + 0xb4),1);
      }
      *(undefined4 *)(param_1 + 0x34) = local_28;
    }
    else {
      pvVar5 = operator_new(0x14c);
      local_8 = 1;
      if (pvVar5 == (void *)0x0) {
        local_30 = 0;
      }
      else {
        local_30 = FUN_004e5770(*(undefined4 *)(param_1 + 0x20),param_1 + 0x24);
      }
      *(undefined4 *)(param_1 + 0x34) = local_30;
    }
    break;
  case 3:
    uVar4 = FUN_00462630(*(undefined4 *)(param_1 + 0x30),uVar1);
    pvVar5 = operator_new(0x134);
    local_8 = 2;
    if (pvVar5 == (void *)0x0) {
      local_38 = 0;
    }
    else {
      local_38 = FUN_004d3790(*(undefined4 *)(param_1 + 0x20),uVar4);
    }
    *(undefined4 *)(param_1 + 0x34) = local_38;
    break;
  case 4:
    piVar2 = (int *)FUN_00462630(*(undefined4 *)(param_1 + 0x30),uVar1);
    pvVar5 = operator_new(0x15c);
    local_8 = 3;
    if (pvVar5 == (void *)0x0) {
      local_40 = 0;
    }
    else {
      local_40 = FUN_005efdf0(*(undefined4 *)(param_1 + 0x20),piVar2);
    }
    local_8 = 0xffffffff;
    *(undefined4 *)(param_1 + 0x34) = local_40;
    uVar4 = (**(code **)(**(int **)(param_1 + 0x20) + 0x28))();
    *(undefined4 *)(param_1 + 0x4c) = uVar4;
    if (piVar2 == (int *)0x0) {
      *(undefined4 *)(param_1 + 0x48) = 0;
    }
    else {
      uVar4 = (**(code **)(*piVar2 + 0x28))();
      *(undefined4 *)(param_1 + 0x48) = uVar4;
    }
    break;
  case 5:
    pvVar5 = operator_new(0x14c);
    local_8 = 6;
    if (pvVar5 == (void *)0x0) {
      local_20 = 0;
    }
    else {
      local_20 = FUN_004e5770(*(undefined4 *)(param_1 + 0x20),param_1 + 0x24);
    }
    *(undefined4 *)(param_1 + 0x34) = local_20;
    break;
  case 6:
    if (*(float *)(param_1 + 0x28) == -1e+30) {
      pvVar5 = operator_new(0x14c);
      local_8 = 4;
      if (pvVar5 == (void *)0x0) {
        local_64 = 0;
      }
      else {
        local_64 = FUN_004e54c0(*(undefined4 *)(param_1 + 0x20),
                                *(undefined4 *)(*(int *)(param_1 + 0x20) + 0xb4),1);
      }
      *(undefined4 *)(param_1 + 0x34) = local_64;
    }
    else {
      pvVar5 = operator_new(0x14c);
      local_8 = 5;
      if (pvVar5 == (void *)0x0) {
        local_5c = 0;
      }
      else {
        local_5c = FUN_004e5770(*(undefined4 *)(param_1 + 0x20),param_1 + 0x24);
      }
      *(undefined4 *)(param_1 + 0x34) = local_5c;
    }
    break;
  case 7:
    FUN_005ef260();
    break;
  case 8:
    iVar3 = FUN_00463120(*(undefined4 *)(param_1 + 0x20));
    if (iVar3 == 0) {
      *(undefined4 *)(param_1 + 0x34) = 0;
    }
    else {
      pvVar5 = operator_new(0x14c);
      local_8 = 7;
      if (pvVar5 == (void *)0x0) {
        local_2c = 0;
      }
      else {
        local_2c = FUN_004e58d0(*(undefined4 *)(param_1 + 0x20),iVar3);
      }
      *(undefined4 *)(param_1 + 0x34) = local_2c;
    }
    break;
  case 9:
    uVar4 = FUN_00462630(*(undefined4 *)(param_1 + 0x30),uVar1);
    pvVar5 = operator_new(0x134);
    local_8 = 8;
    if (pvVar5 == (void *)0x0) {
      local_3c = 0;
    }
    else {
      local_3c = FUN_005b9c60(*(undefined4 *)(param_1 + 0x20),uVar4);
    }
    *(undefined4 *)(param_1 + 0x34) = local_3c;
  }
  ExceptionList = local_10;
  return;
}

