
void FUN_00746090(undefined4 param_1,undefined4 param_2)

{
  char cVar1;
  char *pcVar2;
  uint uVar3;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> abStack_1bc [8];
  undefined4 uStack_1b4;
  undefined1 *puStack_1b0;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbStack_1ac;
  undefined1 auStack_180 [160];
  undefined1 local_e0 [16];
  undefined1 *local_d0;
  undefined4 local_cc;
  undefined4 local_c8;
  undefined4 local_c4;
  undefined4 local_c0;
  undefined4 local_bc;
  undefined4 local_b8;
  undefined4 local_b4;
  undefined1 *local_b0;
  undefined1 *local_ac;
  undefined1 *local_a8;
  undefined1 *local_a4;
  undefined1 *local_a0;
  undefined1 *local_9c;
  undefined1 *local_98;
  undefined1 *local_94;
  int *local_90;
  undefined1 local_74 [24];
  undefined1 local_5c [24];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_44 [24];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085b72e;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  cVar1 = FUN_0041f890();
  if (cVar1 == '\0') {
    pbStack_1ac = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                  0x3;
    puStack_1b0 = (undefined1 *)0x7460e4;
    FUN_00574400();
    local_8 = 0;
    if (&stack0x00000000 == (undefined1 *)0x190) {
      local_b0 = (undefined1 *)0x0;
    }
    else {
      local_b0 = auStack_180;
    }
    pbStack_1ac = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                  local_b0;
    puStack_1b0 = (undefined1 *)0x746122;
    FUN_004bc590();
    if (&stack0x00000000 == (undefined1 *)0x190) {
      local_a4 = (undefined1 *)0x0;
    }
    else {
      local_a4 = auStack_180;
    }
    pbStack_1ac = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                  local_a4;
    puStack_1b0 = (undefined1 *)0x74615b;
    FUN_004bc590();
    if (&stack0x00000000 == (undefined1 *)0x190) {
      local_98 = (undefined1 *)0x0;
    }
    else {
      local_98 = auStack_180;
    }
    pbStack_1ac = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                  local_98;
    puStack_1b0 = (undefined1 *)0x746196;
    FUN_004bc590();
    pbStack_1ac = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                  0x7461ab;
    FUN_0073a740();
    if (&stack0x00000000 == (undefined1 *)0x190) {
      local_a0 = (undefined1 *)0x0;
    }
    else {
      local_a0 = auStack_180;
    }
    pbStack_1ac = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                  local_a0;
    puStack_1b0 = (undefined1 *)0x7461e3;
    FUN_0073ba70();
    if (&stack0x00000000 == (undefined1 *)0x190) {
      local_a8 = (undefined1 *)0x0;
    }
    else {
      local_a8 = auStack_180;
    }
    pbStack_1ac = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                  local_a8;
    puStack_1b0 = (undefined1 *)0x74621e;
    FUN_004bc590();
    pbStack_1ac = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                  0x74623b;
    (**(code **)(*local_90 + 0x38))();
    if (&stack0x00000000 == (undefined1 *)0x190) {
      local_94 = (undefined1 *)0x0;
    }
    else {
      local_94 = auStack_180;
    }
    pbStack_1ac = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                  local_e0;
    puStack_1b0 = local_94;
    uStack_1b4 = 0x746273;
    FUN_0073ba70();
    if (&stack0x00000000 == (undefined1 *)0x190) {
      local_9c = (undefined1 *)0x0;
    }
    else {
      local_9c = auStack_180;
    }
    pbStack_1ac = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                  PTR_DAT_008eda34;
    puStack_1b0 = local_9c;
    uStack_1b4 = 0x7462ae;
    FUN_004bc590();
    if (&stack0x00000000 == (undefined1 *)0x190) {
      local_ac = (undefined1 *)0x0;
    }
    else {
      local_ac = auStack_180;
    }
    pbStack_1ac = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                  param_2;
    puStack_1b0 = local_ac;
    uStack_1b4 = 0x7462e6;
    FUN_00574730();
    pbStack_1ac = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                  0x7462fb;
    local_c0 = GetPolicy();
    local_8._0_1_ = 1;
    pbStack_1ac = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                  0x746323;
    local_b8 = local_c0;
    FUN_007458a0();
    local_8._0_1_ = 0;
    ~basic_string<>();
    pbStack_1ac = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                  0x74633f;
    basic_string<>();
    local_8._0_1_ = 2;
    pbStack_1ac = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                  0x746350;
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
              (local_2c,"<");
    pbStack_1ac = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                  0x8838e8;
    puStack_1b0 = (undefined1 *)0x74635f;
    pcVar2 = (char *)FUN_0081cb40();
    pbStack_1ac = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                  0x74636b;
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
              (local_2c,pcVar2);
    pbStack_1ac = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                  0x746378;
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
              (local_2c,":");
    pbStack_1ac = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                  0x746387;
    FUN_00449810();
    pbStack_1ac = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                  0x746394;
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
              (local_2c,"> ");
    pbStack_1ac = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                  0x7463a0;
    FUN_00449810();
    pbStack_1ac = local_2c;
    puStack_1b0 = local_5c;
    uStack_1b4 = 0x7463b2;
    local_bc = FUN_0048b7d0();
    local_8._0_1_ = 3;
    pbStack_1ac = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                  0x7463d7;
    local_b4 = local_bc;
    FUN_0081e8a0();
    pbStack_1ac = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                  0x7463de;
    FUN_0081e6c0();
    local_8._0_1_ = 2;
    ~basic_string<>();
    pbStack_1ac = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                  0x7463f6;
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
    basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>(local_44,local_2c);
    local_8 = CONCAT31(local_8._1_3_,4);
    if ((char)local_90[0x30] == '\x01') {
      local_d0 = abStack_1bc;
      local_cc = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
                 basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                           (abStack_1bc,local_44);
      local_c8 = FUN_0073bdb0(local_74);
      pbStack_1ac = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                    0x746453;
      local_c4 = local_c8;
      FUN_0045e0f0();
      ~basic_string<>();
    }
    pbStack_1ac = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                  0x74646d;
    FUN_00747e10();
    uVar3 = FUN_004170c0();
    if (1000 < uVar3) {
      FUN_00747f30();
    }
    FUN_007476a0();
    local_8._0_1_ = 2;
    ~basic_string<>();
    local_8 = (uint)local_8._1_3_ << 8;
    ~basic_string<>();
    local_8 = 0xffffffff;
    FUN_00417f10();
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

