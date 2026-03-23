
void FUN_00755110(void)

{
  char cVar1;
  undefined4 uStack_224;
  undefined1 *puStack_220;
  uint uStack_218;
  undefined1 auStack_148 [160];
  undefined1 *local_a8;
  undefined4 local_a4;
  undefined4 local_a0;
  undefined4 local_9c;
  int local_94;
  int local_90;
  undefined4 local_8c;
  undefined4 local_88;
  undefined4 local_84;
  int *local_80;
  undefined4 local_7c;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *local_78;
  undefined4 local_74;
  undefined4 local_70;
  undefined4 local_6c;
  undefined4 local_68;
  undefined4 local_64;
  undefined4 local_60;
  undefined1 *local_5c;
  undefined1 *local_54;
  int *local_50;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_30 [24];
  uint local_18;
  undefined1 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  puStack_c = &LAB_0085c3e6;
  local_10 = ExceptionList;
  uStack_218 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_14 = (undefined1 *)&uStack_218;
  ExceptionList = &local_10;
  local_8 = 0;
  local_18 = uStack_218;
  local_88 = FUN_00764760();
  local_94 = FUN_0056f900();
  local_90 = local_94;
  if (local_94 == 0) {
    local_64 = FUN_0081e820();
    puStack_220 = (undefined1 *)FUN_0081e660();
    uStack_224 = 0x75531b;
    local_68 = puStack_220;
    FUN_004bc590();
  }
  else {
    puStack_220 = (undefined1 *)0x3;
    uStack_224 = 0x755193;
    local_9c = FUN_00574400();
    local_8._0_1_ = 1;
    if (&stack0x00000000 == (undefined1 *)0x158) {
      local_5c = (undefined1 *)0x0;
    }
    else {
      local_5c = auStack_148;
    }
    local_7c = FUN_00764760();
    local_6c = FUN_0056f900();
    puStack_220 = local_5c;
    uStack_224 = 0x7551dd;
    puStack_220 = (undefined1 *)FUN_004bc590();
    uStack_224 = 0x7551f3;
    local_84 = puStack_220;
    FUN_0073ba70();
    local_8c = FUN_00764760();
    local_78 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
               FUN_00754c90();
    puStack_220 = (undefined1 *)0x75521b;
    local_a0 = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
               basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                         (local_30,local_78);
    local_8 = CONCAT31(local_8._1_3_,2);
    cVar1 = FUN_0041f890();
    if (cVar1 == '\0') {
      if (&stack0x00000000 == (undefined1 *)0x158) {
        local_54 = (undefined1 *)0x0;
      }
      else {
        local_54 = auStack_148;
      }
      puStack_220 = local_54;
      uStack_224 = 0x755261;
      puStack_220 = (undefined1 *)FUN_004bc590();
      uStack_224 = 0x755274;
      local_60 = puStack_220;
      FUN_00574730();
    }
    local_80 = (int *)FUN_0073ae00();
    puStack_220 = (undefined1 *)0x755294;
    local_50 = local_80;
    local_74 = GetPolicy();
    local_8._0_1_ = 3;
    local_70 = local_74;
    FUN_0041f870();
    local_a8 = (undefined1 *)&uStack_224;
    local_a4 = FUN_0073a9b0(&uStack_224);
    (**(code **)(*local_50 + 0x68))();
    local_8._0_1_ = 2;
    ~basic_string<>();
    local_8._0_1_ = 1;
    ~basic_string<>();
    local_8 = (uint)local_8._1_3_ << 8;
    FUN_00417f10();
  }
  FUN_00755408();
  return;
}

