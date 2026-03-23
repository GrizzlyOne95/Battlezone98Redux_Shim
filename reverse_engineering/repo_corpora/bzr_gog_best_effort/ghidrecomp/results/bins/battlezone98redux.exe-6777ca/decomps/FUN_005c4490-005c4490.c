
void __fastcall FUN_005c4490(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  int iVar4;
  void *pvVar5;
  float10 fVar6;
  undefined4 local_60;
  undefined4 local_58;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_3c;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084c700;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  switch(*(undefined4 *)(param_1 + 0x1c)) {
  case 0:
    iVar4 = FUN_004624b0();
    if (*(float *)(iVar4 + 4) <= 5.0) {
      uVar2 = FUN_005b52f0(*(undefined4 *)(param_1 + 0x28),0);
      *(undefined4 *)(param_1 + 0x58) = uVar2;
      *(undefined4 *)(param_1 + 0x1c) = 4;
    }
    else {
      pvVar5 = operator_new(0x134);
      local_8 = 0;
      if (pvVar5 == (void *)0x0) {
        local_2c = 0;
      }
      else {
        local_2c = FUN_00608990(*(undefined4 *)(param_1 + 0x28));
      }
      local_8 = 0xffffffff;
      *(undefined4 *)(param_1 + 0x58) = local_2c;
      fVar6 = (float10)FUN_00822d80();
      *(float *)(param_1 + 0x44) = (float)fVar6 + 5.0;
      *(undefined4 *)(param_1 + 0x1c) = 1;
    }
    break;
  case 1:
    pvVar5 = operator_new(0x134);
    local_8 = 1;
    if (pvVar5 == (void *)0x0) {
      local_34 = 0;
    }
    else {
      local_34 = FUN_00608580(*(undefined4 *)(param_1 + 0x28));
    }
    local_8 = 0xffffffff;
    *(undefined4 *)(param_1 + 0x58) = local_34;
    fVar6 = (float10)FUN_00822d80();
    *(float *)(param_1 + 0x44) = (float)fVar6 + 5.0;
    break;
  case 2:
    iVar4 = FUN_00462630(*(undefined4 *)(param_1 + 0x24));
    if ((iVar4 == 0) ||
       (iVar1 = (*(code *)**(undefined4 **)(iVar4 + 0x18))(), *(int *)(iVar1 + 0x1c) != 7)) {
      if (*(float *)(param_1 + 0x30) == -1.0) {
        pvVar5 = operator_new(0x14c);
        local_8 = 3;
        if (pvVar5 == (void *)0x0) {
          local_60 = 0;
        }
        else {
          local_60 = FUN_004e54c0(*(undefined4 *)(param_1 + 0x28),
                                  *(undefined4 *)(*(int *)(param_1 + 0x28) + 0xb4),1);
        }
        *(undefined4 *)(param_1 + 0x58) = local_60;
      }
      else {
        pvVar5 = operator_new(0x14c);
        local_8 = 2;
        if (pvVar5 == (void *)0x0) {
          local_50 = 0;
        }
        else {
          local_50 = FUN_004e5770(*(undefined4 *)(param_1 + 0x28),param_1 + 0x2c);
        }
        *(undefined4 *)(param_1 + 0x58) = local_50;
      }
    }
    else {
      uVar2 = FUN_005b52f0(*(undefined4 *)(param_1 + 0x28),iVar4);
      *(undefined4 *)(param_1 + 0x58) = uVar2;
    }
    break;
  case 3:
    uVar2 = FUN_00462630(*(undefined4 *)(param_1 + 0x24));
    pvVar5 = operator_new(0x134);
    local_8 = 4;
    if (pvVar5 == (void *)0x0) {
      local_58 = 0;
    }
    else {
      local_58 = FUN_004d3790(*(undefined4 *)(param_1 + 0x28),uVar2);
    }
    *(undefined4 *)(param_1 + 0x58) = local_58;
    break;
  case 4:
    fVar6 = (float10)FUN_00822d80();
    *(float *)(param_1 + 0x44) = (float)fVar6 + 10.0;
    uVar2 = FUN_005b52f0(*(undefined4 *)(param_1 + 0x28),0);
    *(undefined4 *)(param_1 + 0x58) = uVar2;
    break;
  case 5:
    FUN_005c4fb0();
    break;
  case 6:
    uVar2 = FUN_00462630(*(undefined4 *)(param_1 + 0x24));
    pvVar5 = operator_new(0x134);
    local_8 = 5;
    if (pvVar5 == (void *)0x0) {
      local_3c = 0;
    }
    else {
      local_3c = FUN_005b9c60(*(undefined4 *)(param_1 + 0x28),uVar2);
    }
    *(undefined4 *)(param_1 + 0x58) = local_3c;
    break;
  case 7:
    iVar4 = FUN_005c3140(*(undefined4 *)(param_1 + 0x28));
    if (iVar4 == 0) {
      *(undefined4 *)(param_1 + 0x58) = 0;
      *(undefined4 *)(param_1 + 0x20) = 1;
    }
    else {
      puVar3 = (undefined4 *)(**(code **)(*(int *)(iVar4 + 0x18) + 0xc))();
      *(undefined4 *)(param_1 + 0x2c) = *puVar3;
      *(undefined4 *)(param_1 + 0x30) = puVar3[1];
      *(undefined4 *)(param_1 + 0x34) = puVar3[2];
      pvVar5 = operator_new(0x14c);
      local_8 = 6;
      if (pvVar5 == (void *)0x0) {
        local_4c = 0;
      }
      else {
        local_4c = FUN_004e5770(*(undefined4 *)(param_1 + 0x28),param_1 + 0x2c);
      }
      *(undefined4 *)(param_1 + 0x58) = local_4c;
    }
    break;
  case 8:
    iVar4 = FUN_00463120(*(undefined4 *)(param_1 + 0x28),DAT_008e7000 ^ (uint)&stack0xfffffffc);
    if (iVar4 == 0) {
      *(undefined4 *)(param_1 + 0x58) = 0;
    }
    else {
      pvVar5 = operator_new(0x14c);
      local_8 = 7;
      if (pvVar5 == (void *)0x0) {
        local_30 = 0;
      }
      else {
        local_30 = FUN_004e58d0(*(undefined4 *)(param_1 + 0x28),iVar4);
      }
      *(undefined4 *)(param_1 + 0x58) = local_30;
    }
  }
  ExceptionList = local_10;
  return;
}

