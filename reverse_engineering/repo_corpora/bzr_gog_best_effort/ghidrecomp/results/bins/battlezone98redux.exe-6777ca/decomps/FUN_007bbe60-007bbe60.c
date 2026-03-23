
void __fastcall FUN_007bbe60(int param_1)

{
  char cVar1;
  uint uVar2;
  undefined4 uVar3;
  char *pcVar4;
  int iVar5;
  undefined1 local_74 [24];
  undefined1 local_5c [24];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_44 [24];
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008618b0;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar2;
  basic_string<>(&DAT_008a1ad8);
  local_8 = 0;
  if (*(int *)(param_1 + 0x150) != 0) {
    uVar3 = FUN_007cf960(uVar2);
    FID_conflict_operator_(uVar3);
  }
  cVar1 = operator!=<>(local_2c,&DAT_008a1ad8);
  if (cVar1 == '\0') {
    pcVar4 = (char *)FUN_007cb0c0();
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
              ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
               &DAT_009c8e28,pcVar4);
  }
  else {
    FID_conflict_operator_(local_2c);
  }
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
            (local_44,(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                       *)&DAT_009c8e28);
  local_8._0_1_ = 1;
  uVar3 = FUN_006ab6b0();
  local_8._0_1_ = 2;
  FUN_00756750(local_44,uVar3);
  local_8._0_1_ = 1;
  FUN_00417b50();
  iVar5 = FUN_0045e1a0(&DAT_008752b0,0xffffffff);
  basic_string<>();
  local_8 = CONCAT31(local_8._1_3_,3);
  if (iVar5 != -1) {
    uVar3 = FUN_0045e1d0(local_74,iVar5,0xffffffff);
    FUN_0045e0f0(uVar3);
    ~basic_string<>();
  }
  cVar1 = FUN_00427270(local_5c,&DAT_0087ba2c);
  if ((cVar1 == '\0') && (cVar1 = FUN_00427270(local_5c,&DAT_0087ba3c), cVar1 == '\0')) {
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
              ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
               &DAT_009c8e28,".bzn");
  }
  FUN_007bbe40();
  local_8._0_1_ = 1;
  ~basic_string<>();
  local_8 = (uint)local_8._1_3_ << 8;
  ~basic_string<>();
  local_8 = 0xffffffff;
  ~basic_string<>();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

