
void __fastcall FUN_0076bfe0(int param_1)

{
  bool bVar1;
  uint uVar2;
  undefined1 local_ec [184];
  int *local_34;
  int local_30;
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085d8e3;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  *(undefined4 *)(param_1 + 0x8c) = 0;
  local_30 = param_1;
  local_14 = uVar2;
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
            ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             (param_1 + 0x90),"**INVALID**");
  FUN_00747fc0(uVar2);
  FUN_0076f800("modEnabled.dat",1,0x40,1);
  local_8 = 0;
  basic_string<>();
  local_8._0_1_ = 1;
  while( true ) {
    local_34 = (int *)FUN_004272d0(local_ec,local_2c);
    bVar1 = std::ios_base::operator_bool((ios_base *)((int)local_34 + *(int *)(*local_34 + 4)));
    if (!bVar1) break;
    FUN_0076f700(local_2c);
  }
  FUN_0048a570();
  local_8 = (uint)local_8._1_3_ << 8;
  ~basic_string<>();
  local_8 = 0xffffffff;
  FUN_0041d080();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

