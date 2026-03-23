
void __thiscall
FUN_007c1a50(int param_1,float param_2,float param_3,float param_4,float param_5,undefined4 param_6)

{
  uint uVar1;
  void *pvVar2;
  undefined4 uVar3;
  float fVar4;
  undefined4 local_34;
  undefined4 local_2c;
  undefined4 local_24;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00861d54;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  fVar4 = param_5 * 0.33;
  if ((*(uint *)(param_1 + 0x14) & 0x100) == 0) {
    FUN_007d2870("popup3.png");
    pvVar2 = operator_new(0x1ec);
    local_8 = 2;
    if (pvVar2 == (void *)0x0) {
      local_34 = 0;
    }
    else {
      local_34 = FUN_007c2480("LeftAlertButton",(param_4 * 0.5) / 2.0 + param_2,
                              (param_3 + param_5) - fVar4,param_4 * 0.5,fVar4,0x20,param_6,0,0);
    }
    local_8 = 0xffffffff;
    *(undefined4 *)(param_1 + 0x148) = local_34;
    uVar1 = FUN_007c19b0();
    FUN_007d3f20((uVar1 & 0xff) + 1);
    FUN_007c23e0(FUN_007c19d0);
    uVar3 = FUN_0081cb40("multi_popup","ok_button");
    FUN_007c2950(uVar3);
    (**(code **)(**(int **)(param_1 + 0x148) + 0x40))("cancelon.png");
    (**(code **)(**(int **)(param_1 + 0x148) + 0x3c))("cancelcl.png");
    FUN_007d2110(*(undefined4 *)(param_1 + 0x148),0);
  }
  else {
    param_4 = param_4 / 2.0;
    FUN_007d2870("popup5.png");
    pvVar2 = operator_new(0x1ec);
    local_8 = 0;
    if (pvVar2 == (void *)0x0) {
      local_24 = 0;
    }
    else {
      local_24 = FUN_007c2480("LeftAlertButton",param_2,(param_3 + param_5) - fVar4,param_4,fVar4,
                              0x20,param_6,0,0);
    }
    local_8 = 0xffffffff;
    *(undefined4 *)(param_1 + 0x148) = local_24;
    uVar1 = FUN_007c19b0(uVar1);
    FUN_007d3f20((uVar1 & 0xff) + 1);
    FUN_007c23e0(FUN_007c19d0);
    uVar3 = FUN_0081cb40("multi_popup","cancel_button");
    FUN_007c2950(uVar3);
    (**(code **)(**(int **)(param_1 + 0x148) + 0x40))("cancelon.png");
    (**(code **)(**(int **)(param_1 + 0x148) + 0x3c))("cancelcl.png");
    FUN_007d2110(*(undefined4 *)(param_1 + 0x148),0);
    pvVar2 = operator_new(0x1ec);
    local_8 = 1;
    if (pvVar2 == (void *)0x0) {
      local_2c = 0;
    }
    else {
      local_2c = FUN_007c2480("RightAlertButton",param_2 + param_4,(param_3 + param_5) - fVar4,
                              param_4,fVar4,0x22,param_6,0,0);
    }
    local_8 = 0xffffffff;
    *(undefined4 *)(param_1 + 0x14c) = local_2c;
    uVar1 = FUN_007c19b0();
    FUN_007d3f20((uVar1 & 0xff) + 1);
    FUN_007c23e0(FUN_007c19e0);
    uVar3 = FUN_0081cb40("multi_popup","ok_button");
    FUN_007c2950(uVar3);
    (**(code **)(**(int **)(param_1 + 0x14c) + 0x40))("cancelon.png");
    (**(code **)(**(int **)(param_1 + 0x14c) + 0x3c))("cancelcl.png");
    FUN_007d2110(*(undefined4 *)(param_1 + 0x14c),0);
  }
  ExceptionList = local_10;
  return;
}

