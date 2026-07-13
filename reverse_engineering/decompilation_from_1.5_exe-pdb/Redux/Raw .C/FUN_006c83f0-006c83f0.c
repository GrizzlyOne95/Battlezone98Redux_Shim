
void FUN_006c83f0(undefined4 *param_1,undefined4 param_2)

{
  char cVar1;
  undefined4 uVar2;
  uint uStack_194;
  undefined1 auStack_174 [184];
  undefined4 local_bc;
  undefined1 local_80 [8];
  undefined4 local_78;
  undefined4 local_74;
  undefined4 local_70;
  undefined4 local_6c;
  undefined4 local_68;
  undefined4 local_64;
  undefined4 local_60;
  undefined4 local_5c;
  undefined4 local_58;
  undefined1 *local_54;
  char *local_50;
  undefined1 local_49;
  undefined1 local_48 [24];
  undefined1 local_30 [24];
  uint local_18;
  undefined1 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085268b;
  local_10 = ExceptionList;
  uStack_194 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_14 = (undefined1 *)&uStack_194;
  ExceptionList = &local_10;
  local_18 = uStack_194;
  cVar1 = FUN_004c85a0();
  if (cVar1 != '\0') {
    local_49 = 1;
    local_8 = 0;
    FUN_006c6e60(param_1,param_2,&local_49);
    FUN_006c845b();
    return;
  }
  FUN_006d8cc0(0x3e3,0);
  cVar1 = operator!=<>(param_1,local_80);
  if ((cVar1 != '\0') && (*local_50 == '\0')) {
    local_8 = 2;
    local_bc = FUN_00574400(3,1);
    local_8._0_1_ = 3;
    if (&stack0x00000000 == (undefined1 *)0x184) {
      local_54 = (undefined1 *)0x0;
    }
    else {
      local_54 = auStack_174;
    }
    local_74 = FUN_004486a0(local_30);
    local_8._0_1_ = 4;
    local_6c = local_74;
    local_70 = FUN_004bc590(local_54,"BZRNet P2P UDP receive listener recovering from error ");
    local_78 = FUN_006da310(local_70,*param_1,param_1[1]);
    local_58 = FUN_004bc590(local_78,", source ");
    local_64 = FUN_006da360(local_58,local_50 + 0xc18);
    local_5c = FUN_004bc590(local_64,&DAT_00874924);
    FUN_00574730(local_5c,local_74);
    local_8._0_1_ = 3;
    ~basic_string<>();
    local_68 = GetPolicy(local_48);
    local_8._0_1_ = 5;
    local_60 = local_68;
    uVar2 = FUN_0041f870();
    FUN_007d6a70(&DAT_008767e0,uVar2);
    local_8._0_1_ = 3;
    ~basic_string<>();
    local_8 = CONCAT31(local_8._1_3_,2);
    FUN_00417f10();
    FUN_006c85ef();
    return;
  }
  FUN_007d6a70("BZRNet P2P Listener Shutting Down\n");
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

