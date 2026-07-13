
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_004f49f0(int param_1)

{
  char cVar1;
  uint uVar2;
  char *pcVar3;
  undefined1 *puVar4;
  undefined4 uVar5;
  undefined4 *puVar6;
  float10 fVar7;
  undefined1 local_70 [8];
  float local_68;
  undefined4 local_64;
  int local_60;
  int local_5c;
  float local_58;
  undefined1 local_54 [4];
  undefined4 local_50;
  char local_49;
  undefined4 local_48;
  undefined1 local_44 [24];
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084a6b0;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar2;
  if (param_1 == 8) {
    basic_string<>("strafe");
    local_8 = 0;
    local_5c = FUN_0041ecd0(local_44);
    local_8 = 0xffffffff;
    ~basic_string<>();
    if (local_5c == 0) {
      param_1 = 9;
    }
    else if (local_5c == 2) {
      param_1 = 10;
    }
    else if ((local_5c != 1) && (local_5c == 3)) {
      FUN_007d6a70("WARNING: none found on the control system\n");
    }
  }
  if (param_1 == 0x15) {
    basic_string<>("pitch");
    local_8 = 1;
    local_60 = FUN_0041ecd0(local_2c);
    local_8 = 0xffffffff;
    ~basic_string<>();
    if (local_60 == 0) {
      param_1 = 0x16;
    }
    else if (local_60 == 2) {
      param_1 = 0x17;
    }
    else if ((local_60 != 1) && (local_60 == 3)) {
      FUN_007d6a70("WARNING: none found on the control system\n");
    }
  }
  fVar7 = (float10)FUN_00822da0(uVar2);
  _DAT_00917b18 = (float)fVar7;
  DAT_00917b1c = param_1;
  pcVar3 = (char *)FUN_004f4d20(param_1);
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
            ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             &DAT_009b7980,pcVar3);
  local_68 = 600.0;
  FID_conflict_begin(&local_50);
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::end
            ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             &DAT_009b7980);
  while (cVar1 = FID_conflict_operator__(local_54), cVar1 != '\0') {
    local_48 = local_50;
    local_49 = '\0';
    while ((cVar1 = FID_conflict_operator__(local_54), cVar1 != '\0' &&
           (pcVar3 = (char *)FUN_00421ec0(), *pcVar3 != '\n'))) {
      FUN_004f5330();
    }
    cVar1 = FID_conflict_operator__(local_54);
    if (cVar1 != '\0') {
      puVar4 = (undefined1 *)FUN_00421ec0();
      *puVar4 = 0;
    }
    local_64 = local_48;
    uVar5 = FUN_00421ec0();
    fVar7 = (float10)FUN_00689cb0(DAT_0091552c,uVar5);
    local_58 = (float)fVar7;
    while (local_68 < local_58) {
      while ((cVar1 = FID_conflict_operator__(&local_50), cVar1 != '\0' &&
             (pcVar3 = (char *)FUN_00421ec0(), *pcVar3 != ' '))) {
        FUN_004f5350();
      }
      cVar1 = FID_conflict_operator__(&local_50);
      if (cVar1 == '\0') {
        local_58 = 0.0;
      }
      else {
        puVar4 = (undefined1 *)FUN_00421ec0();
        *puVar4 = 0;
        uVar5 = FUN_00421ec0();
        fVar7 = (float10)FUN_00689cb0(DAT_0091552c,uVar5);
        local_58 = (float)fVar7;
        if (local_68 < local_58) {
          puVar4 = (undefined1 *)FUN_00421ec0();
          *puVar4 = 0x20;
          FUN_004f5350();
        }
        else {
          puVar4 = (undefined1 *)FUN_00421ec0();
          *puVar4 = 10;
          puVar6 = (undefined4 *)FID_conflict_operator_(local_70,1);
          local_50 = *puVar6;
          local_49 = '\x01';
        }
      }
    }
    cVar1 = FID_conflict_operator__(local_54);
    if (cVar1 != '\0') {
      puVar4 = (undefined1 *)FUN_00421ec0();
      *puVar4 = 10;
    }
    if (local_49 == '\0') {
      local_50 = local_64;
      cVar1 = FID_conflict_operator__(local_54);
      if (cVar1 != '\0') {
        FUN_004f5330();
      }
    }
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

