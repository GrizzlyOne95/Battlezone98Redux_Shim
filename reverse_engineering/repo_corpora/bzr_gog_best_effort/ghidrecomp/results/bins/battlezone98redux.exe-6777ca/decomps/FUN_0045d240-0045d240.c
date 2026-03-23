
void __fastcall FUN_0045d240(int param_1)

{
  char cVar1;
  undefined4 *puVar2;
  int iVar3;
  uint uVar4;
  float10 fVar5;
  undefined1 auStack_84 [12];
  undefined4 uStack_78;
  undefined1 *puStack_74;
  int **local_70;
  uint uStack_6c;
  undefined1 local_60 [4];
  undefined1 local_5c [4];
  undefined1 local_58 [4];
  undefined1 local_54 [4];
  undefined4 local_50;
  undefined1 *local_4c;
  undefined4 local_48;
  undefined1 *local_44;
  float local_40;
  undefined4 local_3c;
  undefined4 *local_38;
  undefined4 *local_34;
  float local_30;
  uint local_2c;
  undefined1 local_28 [4];
  undefined4 *local_24;
  undefined4 local_20;
  undefined4 local_1c;
  int *local_18;
  int local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00847238;
  local_10 = ExceptionList;
  uStack_6c = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = param_1;
  if (*(char *)(param_1 + 0x10) != '\0') {
    local_70 = (int **)0x45d27c;
    fVar5 = (float10)FUN_00822d80();
    local_30 = (float)fVar5;
    if (*(float *)(local_14 + 0x14) <= local_30 && local_30 != *(float *)(local_14 + 0x14)) {
      local_70 = (int **)0x45d296;
      cVar1 = operator==<>();
      if (cVar1 != '\0') {
        local_2c = (uint)(*(char *)(local_14 + 0x18) == '\0');
        local_70 = (int **)local_2c;
        puStack_74 = (undefined1 *)0x45d2c1;
        FUN_00434170();
        if (*(char *)(local_14 + 0x19) == '\0') {
          local_44 = auStack_84;
          local_48 = basic_string<>("nofile");
          FUN_00487b40();
          ExceptionList = local_10;
          return;
        }
        local_4c = auStack_84;
        local_50 = basic_string<>(local_14 + 0x19);
        FUN_00487b40();
        ExceptionList = local_10;
        return;
      }
    }
  }
  local_70 = (int **)0x45d320;
  FUN_006a3490();
  local_70 = (int **)0x45d328;
  vector<>();
  local_8 = 0;
  local_70 = (int **)0x45d337;
  FUN_00430590();
  local_70 = (int **)local_54;
  puStack_74 = (undefined1 *)0x45d346;
  puVar2 = (undefined4 *)FUN_0042d8c0();
  local_1c = *puVar2;
  while( true ) {
    local_70 = (int **)local_5c;
    puStack_74 = (undefined1 *)0x45d36a;
    local_70 = (int **)FID_conflict_begin();
    puStack_74 = (undefined1 *)0x45d373;
    cVar1 = FUN_00420f10();
    if (cVar1 == '\0') break;
    local_70 = (int **)0x45d382;
    local_18 = (int *)FUN_0042de50();
    local_18 = (int *)*local_18;
    if (local_18[5] == 0) {
      local_70 = (int **)0x45d39d;
      (**(code **)(*local_18 + 0x1c))();
    }
    if (local_18[5] != 0) {
      local_70 = &local_18;
      puStack_74 = (undefined1 *)0x45d3b2;
      FUN_00438be0();
    }
    local_70 = (int **)0x0;
    puStack_74 = local_58;
    uStack_78 = 0x45d35b;
    FUN_00438c10();
  }
  while( true ) {
    local_70 = (int **)0x45d3bc;
    cVar1 = FUN_0042d8f0();
    if (cVar1 != '\0') break;
    local_70 = (int **)0x45d3cb;
    local_34 = (undefined4 *)FUN_0045e220();
    local_34 = (undefined4 *)*local_34;
    local_70 = (int **)0x45d3d8;
    FUN_0045e250();
    local_38 = local_34;
    local_24 = local_34;
    if (local_34 == (undefined4 *)0x0) {
      local_3c = 0;
    }
    else {
      local_70 = (int **)0x1;
      puStack_74 = (undefined1 *)0x45d3f8;
      local_3c = (**(code **)*local_34)();
    }
  }
  local_70 = (int **)0x45d40b;
  fVar5 = (float10)FUN_00822d60();
  local_40 = (float)fVar5;
  local_70 = (int **)local_28;
  puStack_74 = (undefined1 *)0x45d41c;
  FID_conflict_begin();
  do {
    local_70 = (int **)local_60;
    puStack_74 = (undefined1 *)0x45d434;
    local_70 = (int **)FID_conflict_end();
    puStack_74 = (undefined1 *)0x45d43d;
    cVar1 = FID_conflict_operator__();
    if (cVar1 == '\0') {
      local_8 = 0xffffffff;
      local_70 = (int **)0x45d4a1;
      FUN_004284d0();
      ExceptionList = local_10;
      return;
    }
    local_70 = (int **)0x45d44c;
    puVar2 = (undefined4 *)FUN_00421ec0();
    local_20 = *puVar2;
    local_70 = (int **)0x45d459;
    iVar3 = FUN_0045bdf0();
    if (iVar3 == 0) {
      local_70 = (int **)0x45d465;
      uVar4 = FUN_0045c4b0();
      if ((uVar4 & 0x200) != 0) goto LAB_0045d46c;
LAB_0045d479:
      local_70 = (int **)local_40;
      puStack_74 = (undefined1 *)local_20;
      uStack_78 = 0x45d48d;
      FUN_0045cd00();
    }
    else {
LAB_0045d46c:
      local_70 = (int **)0x45d474;
      uVar4 = FUN_0045c4b0();
      if ((uVar4 & 0x30) != 0) goto LAB_0045d479;
    }
    local_70 = (int **)0x45d426;
    FUN_00421ee0();
  } while( true );
}

