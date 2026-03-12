
/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __cdecl FUN_10005290(char *param_1)

{
  basic_ostream<char,struct_std::char_traits<char>_> *pbVar1;
  basic_streambuf<char,struct_std::char_traits<char>_> *pbVar2;
  char **ppcVar3;
  char *pcVar4;
  uint in_stack_00000014;
  uint in_stack_00000018;
  char *in_stack_0000001c;
  uint in_stack_0000002c;
  uint in_stack_00000030;
  int local_c4;
  basic_streambuf<char,struct_std::char_traits<char>_> local_c0 [76];
  int local_74;
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_100210b0;
  local_10 = ExceptionList;
  local_14 = DAT_1002a040 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_8 = 1;
  if (DAT_1002af1c != 0) {
    FUN_100189e0(DAT_1002af1c,"[Ban Engine] AddBan(\"%s\", \"%s\")\n");
    fflush((FILE *)DAT_1002af1c);
  }
  FUN_10012ca0(&DAT_1002acac,(undefined4 *)&stack0xffffff34,(byte *)&param_1);
  memset(&local_c4,0,0xb0);
  FUN_10002d00(&local_c4,"banlist.txt",8);
  local_8 = CONCAT31(local_8._1_3_,2);
  if (local_74 != 0) {
    if (in_stack_0000002c == 0) {
      ppcVar3 = &param_1;
      if (0xf < in_stack_00000018) {
        ppcVar3 = (char **)param_1;
      }
      pbVar1 = FUN_10013d30((basic_ostream<char,struct_std::char_traits<char>_> *)&local_c4,
                            (char *)ppcVar3,in_stack_00000014);
    }
    else {
      ppcVar3 = &param_1;
      if (0xf < in_stack_00000018) {
        ppcVar3 = (char **)param_1;
      }
      pbVar1 = FUN_10013d30((basic_ostream<char,struct_std::char_traits<char>_> *)&local_c4,
                            (char *)ppcVar3,in_stack_00000014);
      pbVar1 = FUN_10003260(pbVar1," ");
      pcVar4 = (char *)&stack0x0000001c;
      if (0xf < in_stack_00000030) {
        pcVar4 = in_stack_0000001c;
      }
      pbVar1 = FUN_10013d30(pbVar1,pcVar4,in_stack_0000002c);
    }
    std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar1,FUN_10003480);
    pbVar2 = FUN_10003040(local_c0);
    if (pbVar2 == (basic_streambuf<char,struct_std::char_traits<char>_> *)0x0) {
      std::basic_ios<char,struct_std::char_traits<char>_>::setstate
                ((basic_ios<char,struct_std::char_traits<char>_> *)
                 (local_c0 + *(int *)(local_c4 + 4) + -4),2,false);
    }
  }
  FUN_10002110(&local_c4);
  if (0xf < in_stack_00000018) {
    pcVar4 = param_1;
    if ((0xfff < in_stack_00000018 + 1) &&
       (pcVar4 = *(char **)(param_1 + -4), (char *)0x1f < param_1 + (-4 - (int)pcVar4)))
    goto LAB_10005445;
    FUN_1001f9a8(pcVar4);
  }
  in_stack_00000014 = 0;
  in_stack_00000018 = 0xf;
  param_1 = (char *)((uint)param_1 & 0xffffff00);
  if (0xf < in_stack_00000030) {
    pcVar4 = in_stack_0000001c;
    if ((0xfff < in_stack_00000030 + 1) &&
       (pcVar4 = *(char **)(in_stack_0000001c + -4),
       (char *)0x1f < in_stack_0000001c + (-4 - (int)pcVar4))) {
LAB_10005445:
                    /* WARNING: Subroutine does not return */
      _invalid_parameter_noinfo_noreturn();
    }
    FUN_1001f9a8(pcVar4);
  }
  ExceptionList = local_10;
  return;
}

