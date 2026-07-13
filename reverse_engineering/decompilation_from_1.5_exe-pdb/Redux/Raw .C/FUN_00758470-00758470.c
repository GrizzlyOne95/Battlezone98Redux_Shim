
void FUN_00758470(undefined4 param_1)

{
  char cVar1;
  undefined4 uVar2;
  uint uStack_144;
  undefined1 auStack_124 [160];
  undefined4 local_84;
  undefined4 local_80;
  undefined4 local_78;
  int local_74;
  int *local_70;
  int *local_6c;
  undefined4 local_68;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *local_64;
  undefined4 local_60;
  undefined4 local_5c;
  int *local_58;
  int *local_54;
  undefined1 *local_50;
  char local_49;
  undefined1 local_48 [24];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_30 [24];
  uint local_18;
  undefined1 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  puStack_c = &LAB_0085c75b;
  local_10 = ExceptionList;
  uStack_144 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_14 = (undefined1 *)&uStack_144;
  ExceptionList = &local_10;
  local_8 = 0;
  local_18 = uStack_144;
  local_74 = FUN_006aa1d0();
  if (local_74 == 0) goto LAB_007585f8;
  local_78 = FUN_00764760();
  local_64 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             FUN_00754c90();
  local_84 = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
             basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                       (local_30,local_64);
  local_8._0_1_ = 1;
  local_49 = FUN_0073a900();
  if (local_49 == '\0') {
LAB_00758506:
    local_70 = (int *)FUN_006aa1d0();
    local_54 = local_70;
    (**(code **)(*local_70 + 0xac))("connect",0);
  }
  else {
    cVar1 = FUN_0041f890();
    if (cVar1 == '\0') goto LAB_00758506;
    local_80 = FUN_00574400(3,1);
    local_8._0_1_ = 2;
    if (&stack0x00000000 == (undefined1 *)0x134) {
      local_50 = (undefined1 *)0x0;
    }
    else {
      local_50 = auStack_124;
    }
    local_5c = FUN_004bc590(local_50,"-connect-galaxy-lobby=");
    FUN_0073ba70(local_5c,param_1);
    local_6c = (int *)FUN_006aa1d0();
    local_58 = local_6c;
    local_68 = GetPolicy(local_48);
    local_8._0_1_ = 3;
    local_60 = local_68;
    uVar2 = FUN_0041f870();
    (**(code **)(*local_58 + 0xac))("connect",uVar2);
    local_8._0_1_ = 2;
    ~basic_string<>();
    local_8._0_1_ = 1;
    FUN_00417f10();
  }
  local_8 = (uint)local_8._1_3_ << 8;
  ~basic_string<>();
LAB_007585f8:
  FUN_00758600();
  return;
}

