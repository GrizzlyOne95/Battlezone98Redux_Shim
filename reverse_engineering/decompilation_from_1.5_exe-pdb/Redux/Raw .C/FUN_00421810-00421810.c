
fpos<int> * __thiscall
FUN_00421810(basic_streambuf<char,struct_std::char_traits<char>_> *param_1,fpos<int> *param_2,
            int param_3,int param_4,int param_5)

{
  char cVar1;
  basic_streambuf<char,struct_std::char_traits<char>_> *pbVar2;
  int iVar3;
  bool bVar4;
  int in_stack_fffffff0;
  undefined4 local_c;
  
  pbVar2 = (basic_streambuf<char,struct_std::char_traits<char>_> *)
           std::basic_streambuf<char,struct_std::char_traits<char>_>::gptr(param_1);
  if (((pbVar2 == param_1 + 0x44) && (param_5 == 1)) && (*(int *)(param_1 + 0x40) == 0)) {
    bVar4 = param_3 == 0;
    param_3 = param_3 + -1;
    param_4 = param_4 - (uint)bVar4;
  }
  if ((((*(int *)(param_1 + 0x50) != 0) && (cVar1 = FUN_00423330(), cVar1 != '\0')) &&
      (((param_3 == 0 && param_4 == 0 && (param_5 == 1)) ||
       (iVar3 = _fseeki64(*(FILE **)(param_1 + 0x50),CONCAT44(param_5,param_4),in_stack_fffffff0),
       iVar3 == 0)))) &&
     (iVar3 = fgetpos(*(FILE **)(param_1 + 0x50),(fpos_t *)&stack0xfffffff0), iVar3 == 0)) {
    FUN_00423580();
    std::fpos<int>::fpos<int>(param_2,*(int *)(param_1 + 0x48),CONCAT44(in_stack_fffffff0,local_c));
    return param_2;
  }
  std::fpos<int>::fpos<int>(param_2,*(__int64 *)_BADOFF_exref);
  return param_2;
}

