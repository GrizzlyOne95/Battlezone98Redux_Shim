
void FUN_005d2650(void)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 *puVar3;
  wchar_t *pwVar4;
  bool bVar5;
  int local_c;
  
  if (DAT_009182e8 == DAT_009182ec) {
    local_c = 0;
    for (DAT_009182e8 = DAT_009182ec; DAT_009182e8 != 0;
        DAT_009182e8 = *(int *)(DAT_009182e8 + 0x20)) {
      local_c = local_c + 1;
    }
    bVar5 = local_c == 1;
    if (bVar5) {
      local_c = 2;
    }
    FUN_00592340();
    FUN_005920f0(local_c);
    if (bVar5) {
      local_c = 1;
      puVar3 = (undefined4 *)FUN_005111d0(1);
      *puVar3 = DAT_009182d0;
      puVar3[1] = DAT_009182d4;
    }
    DAT_009182e8 = DAT_009182ec;
    while( true ) {
      if (local_c == 0) break;
      puVar3 = (undefined4 *)FUN_005111d0(local_c + -1);
      *puVar3 = *(undefined4 *)(DAT_009182e8 + 8);
      puVar3[1] = *(undefined4 *)(DAT_009182e8 + 0xc);
      DAT_009182e8 = *(int *)(DAT_009182e8 + 0x20);
      local_c = local_c + -1;
    }
    *(undefined4 *)(DAT_009182e4 + 0x10) = 0;
    *(undefined4 *)(DAT_009182e4 + 0x14) = 0;
    pwVar4 = std::
             basic_string<wchar_t,struct_std::char_traits<wchar_t>,class_std::allocator<wchar_t>_>::
             back((basic_string<wchar_t,struct_std::char_traits<wchar_t>,class_std::allocator<wchar_t>_>
                   *)(DAT_009182e4 + 4));
    iVar2 = DAT_009182e4;
    uVar1 = *(undefined4 *)(pwVar4 + 2);
    *(undefined4 *)(DAT_009182e4 + 0x18) = *(undefined4 *)pwVar4;
    *(undefined4 *)(iVar2 + 0x1c) = uVar1;
  }
  else {
    *(undefined4 *)(DAT_009182e4 + 0x10) = 1;
    *(undefined4 *)(DAT_009182e4 + 0x14) = 0;
  }
  return;
}

