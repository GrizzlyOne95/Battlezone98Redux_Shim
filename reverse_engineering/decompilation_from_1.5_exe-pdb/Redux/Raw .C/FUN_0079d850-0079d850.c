
void FUN_0079d850(void)

{
  char cVar1;
  uint uVar2;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> abStack_c4 [8];
  undefined4 uStack_bc;
  undefined1 *puStack_b8;
  undefined4 uStack_b4;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbStack_b0;
  uint uStack_ac;
  undefined4 local_a8;
  undefined1 *local_a4;
  undefined1 *local_a0;
  undefined4 local_9c;
  undefined4 local_98;
  undefined4 local_94;
  undefined4 local_90;
  undefined4 local_8c;
  undefined4 local_88;
  undefined4 local_84;
  char local_7d;
  uint local_7c;
  int local_78;
  undefined1 local_74 [24];
  undefined1 local_5c [24];
  undefined1 local_44 [24];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085fb6a;
  local_10 = ExceptionList;
  uStack_ac = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_7c = 0;
  pbStack_b0 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
               local_5c;
  uStack_b4 = 0x79d897;
  local_14 = uStack_ac;
  uStack_b4 = FUN_007d04c0();
  local_8 = 0;
  local_7c = local_7c | 1;
  pbStack_b0 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
               &DAT_008a1ad8;
  puStack_b8 = (undefined1 *)0x79d8ca;
  local_94 = uStack_b4;
  local_8c = uStack_b4;
  cVar1 = operator!=<>();
  if (cVar1 != '\0') {
    pbStack_b0 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                 local_74;
    uStack_b4 = 0x79d8e6;
    uStack_b4 = FUN_007d04c0();
    local_8 = 1;
    local_7c = local_7c | 2;
    pbStack_b0 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                 0x871344;
    puStack_b8 = (undefined1 *)0x79d919;
    local_98 = uStack_b4;
    local_90 = uStack_b4;
    cVar1 = operator!=<>();
    if (cVar1 != '\0') {
      local_84 = 1;
      goto LAB_0079d933;
    }
  }
  local_84 = 0;
LAB_0079d933:
  local_7d = (char)local_84;
  local_8 = 0;
  if ((local_7c & 2) != 0) {
    local_7c = local_7c & 0xfffffffd;
    pbStack_b0 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                 0x79d954;
    ~basic_string<>();
  }
  local_8 = 0xffffffff;
  if ((local_7c & 1) != 0) {
    local_7c = local_7c & 0xfffffffe;
    pbStack_b0 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                 0x79d96f;
    ~basic_string<>();
  }
  if (local_7d != '\0') {
    pbStack_b0 = local_2c;
    uStack_b4 = 0x79d98d;
    FUN_007d04c0();
    local_8 = 2;
    pbStack_b0 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                 0x79d99c;
    uVar2 = FUN_004170c0();
    if (0xf < uVar2) {
      pbStack_b0 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                   0xf;
      uStack_b4 = 0;
      puStack_b8 = local_44;
      uStack_bc = 0x79d9b1;
      pbStack_b0 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                   FUN_0045e1d0();
      uStack_b4 = 0x79d9c6;
      local_88 = pbStack_b0;
      FUN_0045e0f0();
      pbStack_b0 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                   0x79d9ce;
      ~basic_string<>();
    }
    pbStack_b0 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                 0x79d9dc;
    cVar1 = FUN_007d05f0();
    if ((cVar1 == '\0') && (*(char *)(local_78 + 0x1fe) != '\x01')) {
      local_a4 = abStack_c4;
      local_9c = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
                 basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                           (abStack_c4,local_2c);
      FUN_0079dab0();
    }
    else {
      *(undefined1 *)(local_78 + 0x1fc) = 0;
      pbStack_b0 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                   0x0;
      uStack_b4 = 0x79da17;
      (**(code **)(**(int **)(local_78 + 0x1c0) + 0x24))();
      uStack_b4 = 1;
      puStack_b8 = (undefined1 *)0x79da32;
      (**(code **)(**(int **)(local_78 + 0x1bc) + 0x24))();
      local_a0 = abStack_c4;
      local_a8 = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
                 basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                           (abStack_c4,local_2c);
      FUN_0079dab0();
      pbStack_b0 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                   0x79da62;
      FUN_007d04a0();
    }
    local_8 = 0xffffffff;
    pbStack_b0 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                 0x79da95;
    ~basic_string<>();
  }
  ExceptionList = local_10;
  uStack_ac = 0x79daaa;
  FUN_0083e885();
  return;
}

