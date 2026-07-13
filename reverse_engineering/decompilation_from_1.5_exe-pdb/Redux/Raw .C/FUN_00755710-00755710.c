
void FUN_00755710(undefined4 param_1)

{
  char cVar1;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar2;
  undefined4 uVar3;
  uint uStack_138;
  undefined1 auStack_118 [160];
  undefined4 local_78;
  int *local_70;
  undefined4 local_6c;
  int local_68;
  undefined4 local_64;
  undefined4 local_60;
  int *local_5c;
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
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085c46b;
  local_10 = ExceptionList;
  uStack_138 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_14 = (undefined1 *)&uStack_138;
  ExceptionList = &local_10;
  local_18 = uStack_138;
  FUN_00764760();
  pbVar2 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
           FUN_00754c90();
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>(local_30,pbVar2);
  local_8._0_1_ = 1;
  local_8._1_3_ = 0;
  local_68 = FUN_0073ae00();
  if (local_68 != 0) {
    local_49 = FUN_0073a900();
    if (local_49 != '\0') {
      cVar1 = FUN_0041f890();
      if (cVar1 != '\0') {
        local_78 = FUN_00574400(3,1);
        local_8._0_1_ = 2;
        if (&stack0x00000000 == (undefined1 *)0x128) {
          local_50 = (undefined1 *)0x0;
        }
        else {
          local_50 = auStack_118;
        }
        local_64 = FUN_004bc590(local_50,"-connect-galaxy-lobby=");
        FUN_0073ba70(local_64,param_1);
        local_5c = (int *)FUN_0073ae00();
        local_58 = local_5c;
        local_6c = GetPolicy(local_48);
        local_8._0_1_ = 3;
        local_60 = local_6c;
        uVar3 = FUN_0041f870();
        (**(code **)(*local_58 + 0x44))("connect",uVar3);
        local_8._0_1_ = 2;
        ~basic_string<>();
        local_8._0_1_ = 1;
        FUN_00417f10();
        goto LAB_00755879;
      }
    }
    local_70 = (int *)FUN_0073ae00();
    local_54 = local_70;
    (**(code **)(*local_70 + 0x44))("connect",0);
  }
LAB_00755879:
  FUN_00755881();
  return;
}

