
undefined4 * FUN_005e51d0(int param_1,undefined4 param_2,undefined4 param_3)

{
  char cVar1;
  char cVar2;
  char cVar3;
  char cVar4;
  undefined4 uVar5;
  int local_40;
  int local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  uint local_2c;
  float local_28;
  float local_24;
  float local_20;
  float local_1c [2];
  undefined4 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00849720;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_005ab360(param_1,param_2,param_3);
  local_8 = 0;
  *local_14 = TorpedoClass::vftable;
  FUN_00589430(local_14 + 0xe);
  local_8 = CONCAT31(local_8._1_3_,1);
  FUN_00589800(0xcba43500,0x4f358485,local_14 + 0x5c,*(undefined4 *)(param_1 + 0x170));
  FUN_00589800(0xcba43500,0xb8add2a,local_14 + 0x5d,*(undefined4 *)(param_1 + 0x174));
  FUN_00589800(0xcba43500,0x473d5031,local_14 + 0x5e,*(undefined4 *)(param_1 + 0x178));
  FUN_00589800(0xcba43500,0x9410fcff,local_14 + 0x5f,*(undefined4 *)(param_1 + 0x17c));
  FUN_00589800(0xcba43500,0xe94c7c19,local_14 + 0x60,*(undefined4 *)(param_1 + 0x180));
  FUN_00589800(0xcba43500,0x4ad4b447,local_14 + 0x61,*(undefined4 *)(param_1 + 0x184));
  FUN_00589800(0xcba43500,0x19b84820,local_14 + 0x62,*(undefined4 *)(param_1 + 0x188));
  FUN_00589800(0xcba43500,0x7c7c544b,local_14 + 99,*(undefined4 *)(param_1 + 0x18c));
  local_14[100] = *(undefined4 *)(param_1 + 400);
  *(undefined2 *)(local_14 + 0x65) = *(undefined2 *)(param_1 + 0x194);
  cVar1 = FUN_00589800(0xcba43500,0x5be2a777,local_1c,0);
  cVar2 = FUN_00589800(0xcba43500,0x7c8a1300,&local_20,0);
  cVar3 = FUN_00589800(0xcba43500,0x52fd4a53,&local_24,0);
  cVar4 = FUN_00589800(0xcba43500,0x38720d72,&local_28,0);
  if (((cVar1 != '\0' || cVar2 != '\0') || cVar3 != '\0') || cVar4 != '\0') {
    local_14[100] = local_1c[0] + local_20 + local_24 + local_28;
    local_2c = (uint)(local_1c[0] != 0.0);
    if (local_20 == 0.0) {
      local_30 = 0;
    }
    else {
      local_30 = 2;
    }
    if (local_24 == 0.0) {
      local_34 = 0;
    }
    else {
      local_34 = 4;
    }
    if (local_28 == 0.0) {
      local_38 = 0;
    }
    else {
      local_38 = 8;
    }
    *(ushort *)(local_14 + 0x65) =
         (ushort)(local_1c[0] != 0.0) | (ushort)local_30 | (ushort)local_34 | (ushort)local_38;
  }
  FUN_00589c20(0xcba43500,0xd61bc22b,&local_40,0,0);
  if (local_40 == 0 && local_3c == 0) {
    local_14[0x66] = *(undefined4 *)(param_1 + 0x198);
  }
  else {
    uVar5 = FUN_004cb870(local_40,local_3c);
    local_14[0x66] = uVar5;
  }
  FUN_0047b6c0(0xcba43500,0x48b2e796,local_14 + 0x67,param_1 + 0x19c);
  local_8 = local_8 & 0xffffff00;
  FUN_00589530();
  ExceptionList = local_10;
  return local_14;
}

