
void FUN_0070a470(undefined4 param_1)

{
  char cVar1;
  undefined1 auStack_84 [4];
  undefined4 uStack_80;
  undefined1 *puStack_7c;
  code *pcStack_78;
  char *pcStack_74;
  char *pcStack_70;
  uint uStack_6c;
  undefined1 local_68 [16];
  undefined1 local_58 [16];
  undefined1 local_48 [8];
  code *local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined1 *local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  uint local_1c;
  int local_18;
  char local_12;
  char local_11;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00857528;
  local_10 = ExceptionList;
  uStack_6c = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  pcStack_70 = (char *)0x400;
  pcStack_74 = (char *)0x70a4ab;
  cVar1 = FUN_006d4590();
  if (cVar1 != '\0') {
    pcStack_70 = "connection handle_write_frame";
    pcStack_74 = (char *)0x400;
    pcStack_78 = (code *)0x70a4ca;
    FUN_006d08b0();
  }
  pcStack_70 = (char *)0x70a4d8;
  std::basic_string<wchar_t,struct_std::char_traits<wchar_t>,class_std::allocator<wchar_t>_>::back
            ((basic_string<wchar_t,struct_std::char_traits<wchar_t>,class_std::allocator<wchar_t>_>
              *)(local_18 + 0x4aac));
  pcStack_70 = (char *)0x70a4df;
  FUN_00421ec0();
  pcStack_70 = (char *)0x70a4e6;
  local_12 = FUN_006f2d90();
  pcStack_70 = (char *)0x70a4f7;
  FUN_006e73d0();
  pcStack_70 = (char *)0x70a505;
  FUN_007101d0();
  pcStack_70 = (char *)0x70a50d;
  cVar1 = FUN_006ab7d0();
  if (cVar1 == '\0') {
    if (local_12 == '\0') {
      local_11 = 0;
      pcStack_70 = (char *)(local_18 + 0xa2c);
      pcStack_74 = (char *)0x70a56c;
      FUN_006d1110();
      local_8 = 0;
      *(undefined1 *)(local_18 + 0x4ab8) = 0;
      pcStack_70 = (char *)0x70a58b;
      cVar1 = FUN_006e1c30();
      local_11 = cVar1 == '\0';
      local_1c = (uint)(byte)local_11;
      local_8 = 0xffffffff;
      pcStack_70 = (char *)0x70a5b7;
      FUN_006d1140();
      if (local_11 != '\0') {
        local_40 = FUN_006e9190;
        local_3c = 0;
        pcStack_70 = local_48;
        pcStack_74 = (char *)0x70a5dd;
        pcStack_70 = (char *)FUN_006e1540();
        local_8 = 1;
        pcStack_74 = (char *)local_3c;
        pcStack_78 = local_40;
        puStack_7c = local_68;
        uStack_80 = 0x70a602;
        local_28 = pcStack_70;
        local_24 = pcStack_70;
        local_30 = FUN_006eabe0();
        local_8._0_1_ = 2;
        local_34 = auStack_84;
        local_2c = local_30;
        local_38 = FUN_006eac20(local_30);
        FUN_006e1210(local_58);
        local_8 = CONCAT31(local_8._1_3_,1);
        pcStack_70 = (char *)0x70a63e;
        ~<>();
        local_8 = 0xffffffff;
        pcStack_70 = (char *)0x70a64d;
        FUN_006ca8c0();
      }
    }
    else {
      pcStack_70 = (char *)0x70a548;
      pcStack_70 = (char *)FUN_006ab750();
      pcStack_74 = (char *)0x70a551;
      FUN_006daf10();
    }
  }
  else {
    pcStack_70 = (char *)param_1;
    pcStack_74 = "handle_write_frame";
    pcStack_78 = (code *)0x20;
    puStack_7c = (undefined1 *)0x70a527;
    FUN_006f90a0();
    pcStack_70 = (char *)param_1;
    pcStack_74 = (char *)0x70a533;
    FUN_006daf10();
  }
  ExceptionList = local_10;
  return;
}

