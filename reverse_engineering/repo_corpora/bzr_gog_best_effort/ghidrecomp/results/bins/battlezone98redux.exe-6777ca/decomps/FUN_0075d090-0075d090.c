
void __thiscall FUN_0075d090(int param_1,undefined4 param_2,undefined4 *param_3)

{
  char cVar1;
  undefined4 uVar2;
  int *piVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined1 *puVar6;
  undefined1 local_1c8 [8];
  undefined1 local_1c0 [8];
  undefined1 local_1b8 [4];
  undefined1 local_1b4 [4];
  undefined4 local_1b0;
  undefined4 local_1ac;
  undefined4 local_1a8;
  undefined4 local_1a4;
  undefined4 local_1a0;
  undefined4 local_19c;
  undefined1 local_198 [4];
  undefined1 local_194 [4];
  int local_190;
  undefined1 local_18c [4];
  undefined4 local_188;
  undefined4 local_184;
  undefined4 *local_180;
  undefined4 *local_17c;
  undefined1 local_178 [4];
  undefined1 local_174 [4];
  int local_170;
  int local_16c;
  undefined1 local_168 [180];
  undefined1 local_b4 [28];
  undefined1 local_98 [28];
  undefined1 local_7c [28];
  undefined1 local_60 [28];
  undefined1 local_44 [24];
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085cc1b;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_16c = param_1;
  cVar1 = FUN_0073ba10(param_1 + 0x48);
  if ((cVar1 != '\0') || (cVar1 = FUN_0056f780(local_16c + 0x38), cVar1 != '\0')) {
LAB_0075d56e:
    ExceptionList = local_10;
    FUN_0083e885();
    return;
  }
  FUN_0042d8c0(local_168);
  FID_conflict_begin(local_18c);
  while( true ) {
    cVar1 = FUN_00420f10(local_18c);
    if (cVar1 == '\0') goto LAB_0075d3d4;
    puVar5 = param_3;
    FUN_0042da60(param_3);
    cVar1 = FUN_0056f780(puVar5);
    if (cVar1 != '\0') break;
    FUN_0042da80();
  }
  local_190 = FUN_0042de50();
  *(undefined4 *)(local_190 + 8) = *param_3;
  *(undefined4 *)(local_190 + 0xc) = param_3[1];
  *(undefined4 *)(local_190 + 0x10) = param_3[2];
  *(undefined4 *)(local_190 + 0x14) = param_3[3];
  uVar2 = FUN_0075cf00(local_7c,param_3 + 0x11);
  FUN_0042da60(uVar2);
  FUN_006cb4c0(uVar2);
  FUN_0042da60();
  FUN_00429ce0();
  local_180 = param_3 + 0x17;
  FUN_00424640(local_178);
  FID_conflict_begin(local_198);
  while (cVar1 = FUN_00420f10(local_198), cVar1 != '\0') {
    local_1a0 = FUN_004237d0();
    uVar2 = FUN_0075cf00(local_b4,local_1a0);
    puVar6 = local_1c8;
    FUN_0042da60(puVar6,uVar2);
    FUN_0075f880(puVar6,uVar2);
    FUN_00422190();
  }
  piVar3 = (int *)FUN_0042da60();
  if (*piVar3 != 0) {
    piVar3 = (int *)FUN_0042da60();
    if (*piVar3 == 8) {
      iVar4 = FUN_0042da60();
      iVar4 = FUN_0042da60(iVar4 + 0x44);
      cVar1 = operator!=<>(iVar4 + 0x28);
      if (cVar1 != '\0') {
        puVar6 = local_1b4;
        FUN_0042da60(puVar6);
        uVar2 = FID_conflict_begin(puVar6);
        iVar4 = FUN_0042da60(uVar2);
        iVar4 = iVar4 + 0x28;
        puVar6 = local_1b8;
        FUN_0042da60(puVar6,iVar4);
        FUN_0075f8b0(puVar6,iVar4);
        cVar1 = FUN_004221b0(uVar2);
        if (cVar1 != '\0') goto LAB_0075d328;
      }
    }
    else {
LAB_0075d328:
      if (DAT_008eda28 != 0) {
        puVar6 = local_2c;
        FUN_0042da60(puVar6);
        local_1b0 = FUN_0073a9f0(puVar6);
        local_8 = 0;
        local_1a8 = local_1b0;
        uVar2 = FUN_0041f870();
        FUN_007d6a70("BZRNet P2P Resetting Connection Status For Client %s\n",uVar2);
        local_8 = 0xffffffff;
        ~basic_string<>();
      }
      puVar5 = (undefined4 *)FUN_0042da60();
      *puVar5 = 0;
      uVar2 = 0;
      iVar4 = FUN_0042da60(0);
      iVar4 = iVar4 + 8;
      get(iVar4);
      FUN_006c59c0(iVar4,uVar2);
    }
  }
LAB_0075d3d4:
  local_1ac = FUN_0073a9f0(local_44);
  local_8 = 1;
  local_184 = local_1ac;
  uVar2 = FUN_0041f870();
  FUN_007d6a70("BZRNet P2P Adding Player %s To P2P Handler\n",uVar2);
  local_8 = 0xffffffff;
  ~basic_string<>();
  local_1a4 = FUN_0075a1a0();
  local_8 = 2;
  local_188 = local_1a4;
  FUN_0075fb10(local_1a4);
  local_8 = 0xffffffff;
  FUN_0075ce60();
  local_170 = FUN_0045e220();
  *(undefined4 *)(local_170 + 8) = *param_3;
  *(undefined4 *)(local_170 + 0xc) = param_3[1];
  *(undefined4 *)(local_170 + 0x10) = param_3[2];
  *(undefined4 *)(local_170 + 0x14) = param_3[3];
  uVar2 = FUN_0075cf00(local_98,param_3 + 0x11);
  FUN_006cb4c0(uVar2);
  local_17c = param_3 + 0x17;
  FUN_00424640(local_174);
  FID_conflict_begin(local_194);
  while (cVar1 = FUN_00420f10(local_194), cVar1 != '\0') {
    local_19c = FUN_004237d0();
    uVar2 = FUN_0075cf00(local_60,local_19c);
    FUN_0075f880(local_1c0,uVar2);
    FUN_00422190();
  }
  FUN_0075faa0(&local_170);
  goto LAB_0075d56e;
}

