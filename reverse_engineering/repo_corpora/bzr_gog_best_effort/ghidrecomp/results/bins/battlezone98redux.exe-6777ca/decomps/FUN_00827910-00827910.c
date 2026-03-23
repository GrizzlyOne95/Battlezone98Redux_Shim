
void FUN_00827910(char *param_1)

{
  char cVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  wchar_t *pwVar5;
  char *local_10;
  wchar_t *local_c;
  
  uVar2 = FUN_00829550();
  uVar3 = FUN_00829680();
  if (uVar2 <= uVar3) {
    iVar4 = FUN_00829680();
    FUN_00829510(iVar4 + 0x14);
  }
  iVar4 = FUN_00829680();
  FUN_00829570(iVar4 + 1);
  pwVar5 = std::
           basic_string<wchar_t,struct_std::char_traits<wchar_t>,class_std::allocator<wchar_t>_>::
           back((basic_string<wchar_t,struct_std::char_traits<wchar_t>,class_std::allocator<wchar_t>_>
                 *)&DAT_0260c218);
  local_10 = param_1;
  local_c = pwVar5;
  do {
    cVar1 = *local_10;
    *(char *)local_c = cVar1;
    local_10 = local_10 + 1;
    local_c = (wchar_t *)((int)local_c + 1);
  } while (cVar1 != '\0');
  pwVar5[0x800] = L'\0';
  pwVar5[0x801] = L'\0';
  return;
}

