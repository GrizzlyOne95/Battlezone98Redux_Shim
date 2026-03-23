
basic_istream<char,struct_std::char_traits<char>_> * __thiscall
FUN_0048a460(basic_istream<char,struct_std::char_traits<char>_> *param_1,undefined4 param_2,
            uint param_3,undefined4 param_4,int param_5)

{
  uint uVar1;
  undefined4 uVar2;
  int iVar3;
  uint uVar4;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008491b4;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  uVar4 = 0;
  if (param_5 != 0) {
    *(undefined **)param_1 = &DAT_00871418;
    std::basic_ios<char,struct_std::char_traits<char>_>::
    basic_ios<char,struct_std::char_traits<char>_>
              ((basic_ios<char,struct_std::char_traits<char>_> *)(param_1 + 0x70));
    local_8 = 0;
    uVar4 = uVar4 | 1;
  }
  std::basic_istream<char,struct_std::char_traits<char>_>::
  basic_istream<char,struct_std::char_traits<char>_>
            (param_1,(basic_streambuf<char,struct_std::char_traits<char>_> *)(param_1 + 0x10),false)
  ;
  local_8 = 1;
  *(undefined ***)(param_1 + *(int *)(*(int *)param_1 + 4)) =
       std::basic_ifstream<char,struct_std::char_traits<char>_>::vftable;
  *(int *)(param_1 + *(int *)(*(int *)param_1 + 4) + -4) = *(int *)(*(int *)param_1 + 4) + -0x70;
  FUN_004230e0(0);
  local_8 = CONCAT31(local_8._1_3_,2);
  param_3 = param_3 | 1;
  uVar2 = FUN_0041f870(param_3,param_4,uVar1,uVar4);
  iVar3 = FUN_00423150(uVar2,param_3,param_4);
  if (iVar3 == 0) {
    std::basic_ios<char,struct_std::char_traits<char>_>::setstate
              ((basic_ios<char,struct_std::char_traits<char>_> *)
               (param_1 + *(int *)(*(int *)param_1 + 4)),2,false);
  }
  ExceptionList = local_10;
  return param_1;
}

