
undefined4 * FUN_004b0ab0(int param_1,undefined4 param_2,undefined4 param_3)

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
  *local_14 = DayWreckerClass::vftable;
  FUN_00589430(local_14 + 0xe);
  local_8 = CONCAT31(local_8._1_3_,1);
  local_14[0x5c] = *(undefined4 *)(param_1 + 0x170);
  *(undefined2 *)(local_14 + 0x5d) = *(undefined2 *)(param_1 + 0x174);
  cVar1 = FUN_00589800(0x2db342a,0x5be2a777,local_1c,0);
  cVar2 = FUN_00589800(0x2db342a,0x7c8a1300,&local_20,0);
  cVar3 = FUN_00589800(0x2db342a,0x52fd4a53,&local_24,0);
  cVar4 = FUN_00589800(0x2db342a,0x38720d72,&local_28,0);
  if (((cVar1 != '\0' || cVar2 != '\0') || cVar3 != '\0') || cVar4 != '\0') {
    local_14[0x5c] = local_1c[0] + local_20 + local_24 + local_28;
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
    *(ushort *)(local_14 + 0x5d) =
         (ushort)(local_1c[0] != 0.0) | (ushort)local_30 | (ushort)local_34 | (ushort)local_38;
  }
  FUN_00589c20(0x2db342a,0xd61bc22b,&local_40,0,0);
  if (local_40 == 0 && local_3c == 0) {
    local_14[0x5e] = *(undefined4 *)(param_1 + 0x178);
  }
  else {
    uVar5 = FUN_004cb870(local_40,local_3c);
    local_14[0x5e] = uVar5;
  }
  FUN_00589800(0x2db342a,0x1aa6522f,local_14 + 0x5f,*(undefined4 *)(param_1 + 0x17c));
  local_8 = local_8 & 0xffffff00;
  FUN_00589530();
  ExceptionList = local_10;
  return local_14;
}

