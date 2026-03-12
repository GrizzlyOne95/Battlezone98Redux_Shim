
/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void FUN_1000ddd0(void)

{
  int iVar1;
  void *pvVar2;
  char *in_stack_fffffee4;
  undefined1 auStack_104 [8];
  undefined4 uStack_fc;
  undefined1 *local_e0;
  int local_dc [4];
  basic_ostream<char,struct_std::char_traits<char>_> local_cc [8];
  basic_streambuf<char,struct_std::char_traits<char>_> local_c4 [8];
  basic_iostream<char,struct_std::char_traits<char>_> local_bc [72];
  basic_ios<char,struct_std::char_traits<char>_> local_74 [72];
  void *local_2c [4];
  undefined4 local_1c;
  uint local_18;
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_10021b43;
  local_10 = ExceptionList;
  local_14 = DAT_1002a040 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  iVar1 = (*DAT_1002ae88)();
  if ((iVar1 != 0) && ((*(int *)(iVar1 + 8) == 1 || (*(int *)(iVar1 + 8) == 2)))) {
    uStack_fc = 0x1000de3a;
    memset(local_dc,0,0xb0);
    FUN_10010c00((basic_iostream<char,struct_std::char_traits<char>_> *)local_dc);
    local_8 = 0;
    if (*(int *)(iVar1 + 8) == 1) {
      FUN_10003260(local_cc,"S");
    }
    if (*(int *)(iVar1 + 8) == 2) {
      FUN_10003260(local_cc,"G");
    }
    std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<
              (local_cc,*(__uint64 *)(iVar1 + 0x10));
    FUN_100109b0(local_dc,local_2c);
    local_e0 = auStack_104;
    local_8._0_1_ = 1;
    FUN_10018a00(auStack_104,(undefined4 *)(iVar1 + 0x2c));
    local_8._0_1_ = 2;
    FUN_10018a00(&stack0xfffffee4,local_2c);
    local_8 = CONCAT31(local_8._1_3_,1);
    FUN_10005290(in_stack_fffffee4);
    if (0xf < local_18) {
      pvVar2 = local_2c[0];
      if (0xfff < local_18 + 1) {
        pvVar2 = *(void **)((int)local_2c[0] + -4);
        if (0x1f < (uint)((int)local_2c[0] + (-4 - (int)pvVar2))) {
                    /* WARNING: Subroutine does not return */
          _invalid_parameter_noinfo_noreturn();
        }
      }
      FUN_1001f9a8(pvVar2);
    }
    local_1c = 0;
    local_18 = 0xf;
    local_2c[0] = (void *)((uint)local_2c[0] & 0xffffff00);
    *(undefined ***)((int)local_dc + *(int *)(local_dc[0] + 4)) =
         std::basic_stringstream<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
         vftable;
    *(int *)((int)local_dc + *(int *)(local_dc[0] + 4) + -4) = *(int *)(local_dc[0] + 4) + -0x68;
    FUN_10010900(local_c4);
    std::basic_iostream<char,struct_std::char_traits<char>_>::
    ~basic_iostream<char,struct_std::char_traits<char>_>(local_bc);
    std::basic_ios<char,struct_std::char_traits<char>_>::
    ~basic_ios<char,struct_std::char_traits<char>_>(local_74);
  }
  ExceptionList = local_10;
  return;
}

