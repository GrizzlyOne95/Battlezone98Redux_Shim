
void FUN_004886e0(void)

{
  char cVar1;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar2;
  undefined4 *puVar3;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> abStack_6c [16];
  undefined4 uStack_5c;
  undefined4 uStack_58;
  undefined4 *puStack_54;
  uint uStack_50;
  undefined4 local_4c;
  undefined1 local_48 [4];
  undefined4 local_44;
  undefined1 *local_40;
  undefined1 *local_3c;
  undefined1 local_38 [6];
  char local_32;
  char local_31;
  undefined4 local_30;
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00848fd8;
  local_10 = ExceptionList;
  uStack_50 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  puStack_54 = (undefined4 *)&DAT_008a1ad8;
  uStack_58 = 0x488712;
  local_14 = uStack_50;
  uStack_58 = FUN_00482850();
  uStack_5c = 0x488718;
  cVar1 = FUN_00427270();
  if (cVar1 != '\0') {
    puStack_54 = (undefined4 *)&DAT_00915540;
    uStack_58 = 0x488733;
    basic_string<>();
    local_8 = 0;
    puStack_54 = &local_30;
    uStack_58 = 0x488748;
    FUN_00424640();
    puStack_54 = (undefined4 *)local_38;
    uStack_58 = 0x488756;
    FID_conflict_begin();
    while( true ) {
      puStack_54 = (undefined4 *)local_38;
      uStack_58 = 0x488762;
      cVar1 = FUN_00420f10();
      if (cVar1 == '\0') break;
      puStack_54 = (undefined4 *)0x488771;
      puStack_54 = (undefined4 *)FUN_004237d0();
      uStack_58 = 0x488777;
      cVar1 = FUN_00488e20();
      if (cVar1 == '\0') {
        puStack_54 = (undefined4 *)local_2c;
        uStack_58 = 0x48878d;
        pbVar2 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                 FUN_004237d0();
        local_3c = abStack_6c;
        local_4c = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                   ::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                             (abStack_6c,pbVar2);
        local_31 = FUN_004882d0();
        if (local_31 != '\0') {
          puStack_54 = (undefined4 *)0x4887b9;
          puStack_54 = (undefined4 *)FUN_004237d0();
          uStack_58 = 0x4887c4;
          FID_conflict_operator_();
          local_8 = 0xffffffff;
          puStack_54 = (undefined4 *)0x4887d3;
          ~basic_string<>();
          goto LAB_00488893;
        }
      }
      puStack_54 = (undefined4 *)0x4887e0;
      FUN_00422190();
    }
    puStack_54 = (undefined4 *)local_48;
    uStack_58 = 0x4887f3;
    puVar3 = (undefined4 *)FUN_00424640();
    local_30 = *puVar3;
    while( true ) {
      puStack_54 = (undefined4 *)local_38;
      uStack_58 = 0x488804;
      cVar1 = FUN_00420f10();
      if (cVar1 == '\0') break;
      puStack_54 = (undefined4 *)0x488813;
      puStack_54 = (undefined4 *)FUN_004237d0();
      uStack_58 = 0x488819;
      cVar1 = FUN_00488e20();
      if (cVar1 != '\0') {
        puStack_54 = (undefined4 *)local_2c;
        uStack_58 = 0x48882f;
        pbVar2 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                 FUN_004237d0();
        local_40 = abStack_6c;
        local_44 = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                   ::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                             (abStack_6c,pbVar2);
        local_32 = FUN_004882d0();
        if (local_32 != '\0') {
          puStack_54 = (undefined4 *)0x48885b;
          puStack_54 = (undefined4 *)FUN_004237d0();
          uStack_58 = 0x488866;
          FID_conflict_operator_();
          local_8 = 0xffffffff;
          puStack_54 = (undefined4 *)0x488875;
          ~basic_string<>();
          goto LAB_00488893;
        }
      }
      puStack_54 = (undefined4 *)0x48887f;
      FUN_00422190();
    }
    local_8 = 0xffffffff;
    puStack_54 = (undefined4 *)0x488893;
    ~basic_string<>();
  }
LAB_00488893:
  ExceptionList = local_10;
  uStack_50 = 0x4888a8;
  FUN_0083e885();
  return;
}

