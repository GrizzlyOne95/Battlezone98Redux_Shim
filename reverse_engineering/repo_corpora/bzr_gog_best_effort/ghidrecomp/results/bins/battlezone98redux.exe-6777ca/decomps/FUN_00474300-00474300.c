
void __fastcall FUN_00474300(int *param_1)

{
  char cVar1;
  uint uVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  void *pvVar6;
  float10 fVar7;
  int local_58;
  int local_50;
  int local_44;
  int local_3c;
  int local_34;
  int local_2c;
  int local_24;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00847794;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  switch(param_1[6]) {
  case 0:
    cVar1 = (**(code **)(*(int *)param_1[8] + 0x6c))();
    if (cVar1 == '\0') {
      param_1[7] = 3;
    }
    else {
      param_1[7] = 1;
    }
  case 3:
    (**(code **)(*param_1 + 0x20))();
    break;
  case 1:
  case 2:
    pvVar6 = operator_new(0x134);
    local_8 = 0;
    if (pvVar6 == (void *)0x0) {
      local_24 = 0;
    }
    else {
      local_24 = FUN_00608580();
    }
    param_1[10] = local_24;
    break;
  case 4:
    iVar5 = FUN_00462630();
    if (iVar5 == 0) {
      pvVar6 = operator_new(0x14c);
      local_8 = 3;
      if (pvVar6 == (void *)0x0) {
        local_3c = 0;
      }
      else {
        local_3c = FUN_004e54c0();
      }
      param_1[10] = local_3c;
    }
    else {
      iVar3 = (*(code *)**(undefined4 **)(iVar5 + 0x18))();
      if (*(int *)(iVar3 + 0x14) == 0x4745495a) {
        pvVar6 = operator_new(0x154);
        local_8 = 1;
        if (pvVar6 == (void *)0x0) {
          local_2c = 0;
        }
        else {
          local_2c = FUN_004e49b0(param_1[8],iVar5);
        }
        param_1[10] = local_2c;
      }
      else {
        pvVar6 = operator_new(0x14c);
        local_8 = 2;
        if (pvVar6 == (void *)0x0) {
          local_34 = 0;
        }
        else {
          local_34 = FUN_004e58d0(param_1[8],iVar5);
        }
        param_1[10] = local_34;
      }
    }
    break;
  case 5:
    uVar4 = FUN_00462630();
    pvVar6 = operator_new(0x134);
    local_8 = 4;
    if (pvVar6 == (void *)0x0) {
      local_44 = 0;
    }
    else {
      local_44 = FUN_004d3790(param_1[8],uVar4);
    }
    param_1[10] = local_44;
    break;
  case 6:
    param_1[0xd] = *(int *)(*(int *)(param_1[4] + 8) + 8);
    param_1[0xf] = *(int *)(*(int *)(param_1[4] + 8) + 0xc);
    fVar7 = (float10)FUN_007855e0((double)(float)param_1[0xd],(double)(float)param_1[0xf],uVar2);
    param_1[0xe] = (int)(float)fVar7;
    FUN_00473210(param_1[0xb],param_1 + 0xd);
    param_1[0xb] = 0;
    param_1[7] = 2;
    break;
  case 7:
    iVar5 = FUN_00463120();
    if (iVar5 == 0) {
      param_1[10] = 0;
    }
    else {
      pvVar6 = operator_new(0x14c);
      local_8 = 5;
      if (pvVar6 == (void *)0x0) {
        local_50 = 0;
      }
      else {
        local_50 = FUN_004e58d0(param_1[8],iVar5);
      }
      param_1[10] = local_50;
    }
    break;
  case 8:
    pvVar6 = operator_new(0x154);
    local_8 = 6;
    if (pvVar6 == (void *)0x0) {
      local_58 = 0;
    }
    else {
      local_58 = FUN_004e48e0();
    }
    param_1[10] = local_58;
  }
  ExceptionList = local_10;
  return;
}

