
void FUN_006be060(uint *param_1,SchedulerBase *param_2)

{
  bool bVar1;
  uint uVar2;
  int iVar3;
  uint *puVar4;
  runtime_error local_74 [12];
  undefined4 local_68;
  undefined1 local_64 [2];
  undefined1 local_62 [2];
  undefined4 local_60;
  undefined1 local_5c [8];
  int local_54;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_50 [24];
  uint local_38 [10];
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00851400;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_38[9] = uVar2;
  bVar1 = Concurrency::details::SchedulerBase::HasWorkPending(param_2);
  if (bVar1) {
    basic_string<>("tm unable to handle ");
    local_8 = 0;
    local_54 = FUN_006c97f0(uVar2);
    if (local_54 == 0) {
      std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
                (local_50,"not-a-date-time value");
    }
    else if (local_54 == 1) {
      std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
                (local_50,"-infinity date value");
    }
    else if (local_54 == 2) {
      std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
                (local_50,"+infinity date value");
    }
    else {
      std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
                (local_50,"a special date value");
    }
    local_68 = std::runtime_error::runtime_error(local_74,local_50);
    local_8._0_1_ = 1;
    local_60 = local_68;
    FUN_006d94f0(local_68);
    local_8 = (uint)local_8._1_3_ << 8;
    FUN_006ab660();
    local_8 = 0xffffffff;
    ~basic_string<>();
  }
  local_38[0] = 0;
  local_38[1] = 0;
  local_38[2] = 0;
  local_38[3] = 0;
  local_38[4] = 0;
  local_38[5] = 0;
  local_38[6] = 0;
  local_38[7] = 0;
  local_38[8] = 0;
  FUN_006c9780(local_5c);
  uVar2 = FUN_006b2540();
  local_38[5] = (uVar2 & 0xffff) - 0x76c;
  uVar2 = FUN_006b2540();
  local_38[4] = (uVar2 & 0xffff) - 1;
  local_38[3] = FUN_006b2540();
  local_38[3] = local_38[3] & 0xffff;
  FUN_006c9740(local_64);
  local_38[6] = FUN_006b2540();
  local_38[6] = local_38[6] & 0xffff;
  FUN_006b2880(local_62);
  uVar2 = FUN_006b2540();
  local_38[7] = (uVar2 & 0xffff) - 1;
  local_38[8] = 0xffffffff;
  puVar4 = local_38;
  for (iVar3 = 9; iVar3 != 0; iVar3 = iVar3 + -1) {
    *param_1 = *puVar4;
    puVar4 = puVar4 + 1;
    param_1 = param_1 + 1;
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

