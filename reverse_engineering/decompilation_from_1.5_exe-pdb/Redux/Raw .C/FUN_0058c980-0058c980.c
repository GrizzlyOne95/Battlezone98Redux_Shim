
undefined * __thiscall FUN_0058c980(undefined4 param_1,char param_2)

{
  char cVar1;
  undefined *puVar2;
  wchar_t *pwVar3;
  
  cVar1 = FUN_0041fc90(param_1);
  if (cVar1 == '\0') {
    pwVar3 = std::
             basic_string<wchar_t,struct_std::char_traits<wchar_t>,class_std::allocator<wchar_t>_>::
             back(DAT_02a13c8c);
    puVar2 = *(undefined **)pwVar3;
    FUN_004cbb80();
  }
  else {
    if (0x7ffff < DAT_009181a0) {
                    /* WARNING: Subroutine does not return */
      exit(1);
    }
    puVar2 = &DAT_009cc320 + DAT_009181a0 * 0x38;
    DAT_009181a0 = DAT_009181a0 + 1;
  }
  FUN_0058c930(puVar2);
  if (param_2 != '\0') {
    DAT_00918168 = DAT_00918168 + 1;
    *(int *)(puVar2 + 0x14) = DAT_00918168;
  }
  return puVar2;
}

