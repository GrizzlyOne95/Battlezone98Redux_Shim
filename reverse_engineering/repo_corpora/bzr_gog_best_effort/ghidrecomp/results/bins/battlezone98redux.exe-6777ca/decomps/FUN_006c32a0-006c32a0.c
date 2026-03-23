
void __fastcall FUN_006c32a0(char *param_1)

{
  char cVar1;
  undefined1 auStack_1d0 [100];
  undefined4 uStack_16c;
  undefined1 *puStack_168;
  code *pcStack_164;
  int local_154 [4];
  undefined1 auStack_144 [168];
  undefined1 local_9c [20];
  undefined4 local_88;
  undefined1 *local_84;
  undefined4 local_80;
  undefined1 *local_7c;
  undefined4 local_78;
  locale local_74 [4];
  undefined4 local_70;
  undefined4 local_6c;
  undefined4 local_68;
  undefined4 local_64;
  undefined4 local_5c;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined1 *local_3c;
  void *local_38;
  char *local_34;
  uint local_30;
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00851d53;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_30 = 0;
  local_34 = param_1;
  if (*param_1 == '\0') {
    cVar1 = FUN_004c85a0();
    if (cVar1 != '\0') {
      pcStack_164 = (code *)0x6c3305;
      FUN_00574400();
      local_8 = 0;
      local_38 = operator_new(0x114);
      local_8._0_1_ = 1;
      if (local_38 == (void *)0x0) {
        local_40 = 0;
      }
      else {
        local_7c = (undefined1 *)&puStack_168;
        uStack_16c = 0x6c333a;
        local_88 = FUN_006ccb70();
        local_8._0_1_ = 2;
        uStack_16c = 0x6c3355;
        local_64 = local_88;
        uStack_16c = FUN_006ccef0();
        local_8 = CONCAT31(local_8._1_3_,3);
        local_30 = local_30 | 1;
        local_84 = auStack_1d0;
        local_5c = uStack_16c;
        local_4c = uStack_16c;
        local_80 = FUN_006cce50(1,&DAT_008961b8,&DAT_00896190,&DAT_00896290,&DAT_008961bc);
        local_8 = 4;
        local_68 = FUN_006cc7d0("%Y-%m-%d %H:%M:%S");
        local_40 = local_68;
      }
      local_70 = local_40;
      local_8 = 5;
      local_78 = std::ios_base::getloc((ios_base *)((int)local_154 + *(int *)(local_154[0] + 4)));
      local_8 = 6;
      pcStack_164 = (code *)0x6c3402;
      local_54 = local_78;
      local_6c = FUN_006db9f0();
      local_8._0_1_ = 7;
      pcStack_164 = (code *)0x6c342d;
      local_44 = local_6c;
      std::basic_ios<char,struct_std::char_traits<char>_>::imbue
                ((basic_ios<char,struct_std::char_traits<char>_> *)
                 ((int)local_154 + *(int *)(local_154[0] + 4)),local_74);
      FUN_00417b50();
      local_8._0_1_ = 6;
      FUN_00417b50();
      local_8 = CONCAT31(local_8._1_3_,5);
      FUN_00417b50();
      local_8 = 0;
      if ((local_30 & 1) != 0) {
        local_30 = local_30 & 0xfffffffe;
        FUN_006c3560();
      }
      if (&stack0x00000000 == (undefined1 *)0x154) {
        local_3c = (undefined1 *)0x0;
      }
      else {
        local_3c = auStack_144;
      }
      FUN_006ccf80();
      pcStack_164 = (code *)0x6c34a3;
      FUN_006dba70();
      local_50 = GetPolicy();
      local_8._0_1_ = 8;
      local_48 = local_50;
      FUN_0041f870();
      pcStack_164 = (code *)0x6c34d5;
      FUN_007d6a70();
      local_8 = (uint)local_8._1_3_ << 8;
      ~basic_string<>();
      FUN_006cb140();
      pcStack_164 = FUN_006c32a0;
      puStack_168 = local_9c;
      uStack_16c = 0x6c3515;
      FUN_006db740();
      FUN_006db780();
      local_8 = 0xffffffff;
      FUN_00417f10();
    }
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

