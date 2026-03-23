
undefined1 FUN_004883c0(void)

{
  char cVar1;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar2;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> abStack_44 [16];
  undefined4 uStack_34;
  undefined *puStack_30;
  undefined1 *puStack_2c;
  uint uStack_28;
  undefined4 local_24;
  undefined1 *local_20;
  undefined1 local_1c [4];
  undefined1 local_18 [4];
  undefined1 local_14;
  undefined1 local_13;
  char local_12;
  undefined1 local_11;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_00848f48;
  local_10 = ExceptionList;
  uStack_28 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_8 = 0;
  puStack_2c = local_18;
  puStack_30 = (undefined *)0x4883fa;
  FUN_00424640();
  puStack_2c = local_1c;
  puStack_30 = (undefined *)0x488408;
  FID_conflict_begin();
  puStack_2c = &DAT_0094ffe0;
  puStack_30 = &DAT_0094fee0;
  uStack_34 = 0x488417;
  cVar1 = operator!=<>();
  if (cVar1 != '\0') {
    puStack_2c = &DAT_0094fea8;
    puStack_30 = &DAT_0094fee0;
    uStack_34 = 0x488430;
    cVar1 = operator!=<>();
    if (cVar1 != '\0') {
      puStack_2c = &DAT_0094fe78;
      puStack_30 = &DAT_0094fee0;
      uStack_34 = 0x488449;
      cVar1 = operator!=<>();
      if (cVar1 != '\0') {
        puStack_2c = &DAT_0094fe90;
        puStack_30 = &DAT_0094fee0;
        uStack_34 = 0x488462;
        cVar1 = operator!=<>();
        if (cVar1 != '\0') {
          puStack_2c = &DAT_0094fef8;
          puStack_30 = &DAT_0094fee0;
          uStack_34 = 0x48847b;
          cVar1 = operator!=<>();
          if (cVar1 != '\0') {
            local_11 = 0;
            local_8 = 0xffffffff;
            puStack_2c = (undefined1 *)0x488498;
            ~basic_string<>();
            ExceptionList = local_10;
            return local_11;
          }
        }
      }
    }
  }
  do {
    puStack_2c = local_1c;
    puStack_30 = (undefined *)0x4884ac;
    cVar1 = FUN_00420f10();
    if (cVar1 == '\0') {
      local_14 = 0;
      local_8 = 0xffffffff;
      puStack_2c = (undefined1 *)0x4885b0;
      ~basic_string<>();
      ExceptionList = local_10;
      return local_14;
    }
    puStack_2c = &DAT_0094ffe0;
    puStack_30 = (undefined *)0x4884c4;
    puStack_30 = (undefined *)FUN_004237d0();
    uStack_34 = 0x4884ca;
    cVar1 = FUN_00427310();
    if (cVar1 == '\0') {
      puStack_2c = &DAT_0094fea8;
      puStack_30 = (undefined *)0x4884e1;
      puStack_30 = (undefined *)FUN_004237d0();
      uStack_34 = 0x4884e7;
      cVar1 = FUN_00427310();
      if (cVar1 != '\0') goto LAB_00488548;
      puStack_2c = &DAT_0094fe78;
      puStack_30 = (undefined *)0x4884fe;
      puStack_30 = (undefined *)FUN_004237d0();
      uStack_34 = 0x488504;
      cVar1 = FUN_00427310();
      if (cVar1 != '\0') goto LAB_00488548;
      puStack_2c = &DAT_0094fe90;
      puStack_30 = (undefined *)0x48851b;
      puStack_30 = (undefined *)FUN_004237d0();
      uStack_34 = 0x488521;
      cVar1 = FUN_00427310();
      if (cVar1 != '\0') goto LAB_00488548;
      puStack_2c = &DAT_0094fef8;
      puStack_30 = (undefined *)0x488538;
      puStack_30 = (undefined *)FUN_004237d0();
      uStack_34 = 0x48853e;
      cVar1 = FUN_00427310();
      if (cVar1 != '\0') goto LAB_00488548;
    }
    else {
LAB_00488548:
      puStack_2c = &stack0x00000004;
      puStack_30 = (undefined *)0x488554;
      pbVar2 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
               FUN_004237d0();
      local_20 = abStack_44;
      local_24 = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
                 basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                           (abStack_44,pbVar2);
      local_12 = FUN_004882d0();
      if (local_12 != '\0') {
        local_13 = 1;
        local_8 = 0xffffffff;
        puStack_2c = (undefined1 *)0x48858b;
        ~basic_string<>();
        ExceptionList = local_10;
        return local_13;
      }
    }
    puStack_2c = (undefined1 *)0x488598;
    FUN_00422190();
  } while( true );
}

