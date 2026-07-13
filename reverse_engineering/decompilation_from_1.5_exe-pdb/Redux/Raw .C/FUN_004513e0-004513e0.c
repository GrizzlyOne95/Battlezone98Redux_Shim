
void __thiscall
FUN_004513e0(int param_1,undefined4 *param_2,undefined4 *param_3,undefined4 *param_4,float param_5)

{
  char cVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined1 local_44 [4];
  int local_40;
  undefined4 local_3c;
  int local_38;
  int local_34;
  int local_30;
  int local_2c;
  float local_28;
  int local_24;
  undefined1 local_20 [4];
  int local_1c;
  int local_18;
  int local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00846a9b;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  if (param_1 != 0) {
    local_14 = param_1;
    iVar3 = FUN_004170c0(uVar2);
    if (iVar3 == *(int *)(local_14 + 0xe8)) {
      local_28 = 1e+30;
      local_1c = 0;
      FUN_00447e20(local_20);
      while( true ) {
        iVar3 = FUN_00447e70();
        FUN_00447e50(local_44);
        iVar4 = FUN_00447e70();
        if (iVar3 == iVar4) break;
        local_24 = FUN_00447e70();
        FUN_00447e90();
        if (*(float *)(local_24 + 0x68) <= local_28 && local_28 != *(float *)(local_24 + 0x68)) {
          local_28 = *(float *)(local_24 + 0x68);
          local_1c = local_24;
        }
      }
      FUN_0044dc60(0,0);
      FUN_0044e950(local_1c);
      local_38 = local_1c;
      local_2c = local_1c;
      if (local_1c == 0) {
        local_3c = 0;
      }
      else {
        local_3c = FUN_00451190(1);
      }
    }
    else {
      iVar3 = FUN_004170c0(uVar2);
      if (iVar3 == 0) {
        FUN_0044e9a0(local_14 + 4,local_14);
      }
    }
    local_30 = FUN_00450d40(0x70);
    local_8 = 0;
    if (local_30 == 0) {
      local_34 = 0;
    }
    else {
      local_34 = FUN_00450d80();
    }
    local_40 = local_34;
    local_8 = 0xffffffff;
    local_18 = local_34;
    puVar5 = (undefined4 *)(local_34 + 0x10);
    for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar5 = *param_2;
      param_2 = param_2 + 1;
      puVar5 = puVar5 + 1;
    }
    *(undefined4 *)(local_34 + 0x50) = *param_3;
    *(undefined4 *)(local_34 + 0x54) = param_3[1];
    *(undefined4 *)(local_34 + 0x58) = param_3[2];
    *(undefined4 *)(local_34 + 0x5c) = *param_4;
    *(undefined4 *)(local_34 + 0x60) = param_4[1];
    *(undefined4 *)(local_34 + 100) = param_4[2];
    *(float *)(local_34 + 0x68) = *(float *)(local_14 + 0xe0) - param_5;
    if ((*(int *)(local_14 + 0xdc) != 0) &&
       ((**(code **)(**(int **)(local_14 + 0xdc) + 8))(local_34 + 0x6c,local_34 + 0x10),
       *(int *)(local_18 + 0x6c) != 0)) {
      cVar1 = (**(code **)**(undefined4 **)(local_14 + 0xdc))();
      if (cVar1 == '\0') {
        *(float *)(*(int *)(local_18 + 0x6c) + 0x60) = *(float *)(local_14 + 0xe4) + param_5;
      }
      else {
        *(float *)(*(int *)(local_18 + 0x6c) + 0x60) = -*(float *)(local_14 + 0xe4) + param_5;
      }
    }
    FUN_0044e9a0(local_18,local_18);
  }
  ExceptionList = local_10;
  return;
}

