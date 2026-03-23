
void __fastcall FUN_006c6a10(char *param_1)

{
  char cVar1;
  undefined4 uVar2;
  basic_ostream<char,struct_std::char_traits<char>_> *pbVar3;
  char *pcVar4;
  code *pcVar5;
  undefined1 *puVar6;
  undefined4 uVar7;
  ushort uVar8;
  undefined *puVar9;
  basic_ostream<char,struct_std::char_traits<char>_> local_230 [176];
  undefined1 auStack_180 [160];
  undefined1 local_e0 [16];
  undefined1 local_d0 [8];
  undefined1 local_c8 [8];
  undefined1 local_c0 [8];
  undefined1 local_b8 [8];
  undefined1 local_b0 [8];
  undefined1 local_a8 [16];
  undefined1 local_98 [8];
  undefined1 local_90 [8];
  undefined8 local_88;
  undefined4 local_80;
  undefined4 local_7c;
  undefined4 local_78;
  undefined4 local_74;
  undefined1 *local_70;
  int local_6c;
  undefined1 local_65;
  uint local_64;
  int local_60;
  char *local_5c;
  undefined1 local_58 [24];
  undefined1 local_40 [24];
  byte local_28 [20];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00852406;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_5c = param_1;
  if (*param_1 == '\0') {
    cVar1 = FUN_004c85a0(local_14);
    if (cVar1 != '\0') {
      local_6c = *(int *)(local_5c + 4);
      if (local_6c == 0) {
        local_60 = 0;
      }
      else if (local_6c == 1) {
        local_60 = 10;
      }
      else {
        local_60 = 0x1e;
      }
      local_28[4] = 0;
      local_28[5] = 0;
      local_28[6] = 0;
      local_28[7] = 0;
      local_28[8] = 0;
      local_28[9] = 0;
      local_28[10] = 0;
      local_28[0xb] = 0;
      local_28[0xc] = 0;
      local_28[0xd] = 0;
      local_28[0xe] = 0;
      local_28[0xf] = 0;
      local_28[0x10] = 0;
      local_28[0x11] = 0;
      local_28[0] = 0x40;
      local_28[1] = 2;
      local_28[2] = 0;
      local_28[3] = 0;
      puVar9 = &DAT_0260b068;
      puVar6 = local_d0;
      FUN_006c9bd0(local_b8,puVar6,&DAT_0260b068);
      FUN_006c9b60(puVar6,puVar9);
      local_88 = FUN_006c9a10();
      FUN_006dc210(&local_88,local_28 + 2,0,0);
      if (DAT_008eda28 != 0) {
        FUN_00574400(3,1);
        local_8 = 0;
        for (local_64 = 0; local_64 < 0x12; local_64 = local_64 + 1) {
          uVar8 = (ushort)local_28[local_64];
          uVar2 = std::setw(CONCAT44(2,local_e0));
          pcVar5 = FUN_006ab840;
          uVar2 = FUN_006dc270(&local_65,0x30,FUN_006ab840,uVar2);
          pbVar3 = std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<
                             (local_230,FUN_00574a10);
          pbVar3 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_006dc290(pbVar3,uVar2);
          pbVar3 = std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<
                             (pbVar3,pcVar5);
          pbVar3 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_006db8a0(pbVar3);
          std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar3,uVar8);
        }
        FUN_00574400(3,1);
        local_8._0_1_ = 1;
        if (&stack0x00000000 == (undefined1 *)0x190) {
          local_70 = (undefined1 *)0x0;
        }
        else {
          local_70 = auStack_180;
        }
        FUN_006da360(local_70,local_5c + 0x328);
        local_7c = GetPolicy(local_58);
        local_8._0_1_ = 2;
        local_74 = local_7c;
        local_80 = GetPolicy(local_40);
        local_8._0_1_ = 3;
        local_78 = local_80;
        uVar2 = FUN_0041f870();
        uVar2 = FUN_0041f870(uVar2);
        FUN_007d6a70("BZRNet P2P Sent Packet to %s: %s\n",uVar2);
        local_8._0_1_ = 2;
        ~basic_string<>();
        local_8._0_1_ = 1;
        ~basic_string<>();
        local_8 = (uint)local_8._1_3_ << 8;
        FUN_00417f10();
        local_8 = 0xffffffff;
        FUN_00417f10();
      }
      FUN_004fbb60();
      puVar6 = local_98;
      uVar7 = 0;
      pcVar4 = local_5c + 0x328;
      uVar2 = FUN_006dc2b0(local_b0,local_28,pcVar4,0,puVar6);
      FUN_006dc2e0(uVar2,pcVar4,uVar7,puVar6);
      if (local_5c[0x324] != '\0') {
        local_5c[0x324] = '\0';
        uVar2 = FUN_006dc350(local_c0,FUN_006c83f0,local_5c,*DAT_0260b098,*DAT_0260b0cc);
        pcVar4 = local_5c + 0xc18;
        uVar7 = FUN_006dc320(local_c8,local_5c + 0x344,pcVar4,uVar2);
        FUN_006dc3a0(uVar7,pcVar4,uVar2);
      }
      if (local_60 == 0) {
        FUN_006b29f0(2);
        FUN_006cb0f0(local_90);
      }
      else {
        uVar2 = FUN_006b2a40(local_60);
        FUN_006cb140(uVar2);
      }
      uVar2 = FUN_006db740(local_a8,FUN_006c6a10,local_5c,DAT_0260b043);
      FUN_006db780(uVar2);
    }
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

