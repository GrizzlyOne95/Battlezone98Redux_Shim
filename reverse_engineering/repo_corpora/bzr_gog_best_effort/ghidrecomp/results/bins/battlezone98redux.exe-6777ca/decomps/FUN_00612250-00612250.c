
void FUN_00612250(void)

{
  char cVar1;
  wchar_t *pwVar2;
  undefined4 uVar3;
  
  while( true ) {
    cVar1 = FUN_0041fc90();
    if (cVar1 != '\0') break;
    pwVar2 = std::
             basic_string<wchar_t,struct_std::char_traits<wchar_t>,class_std::allocator<wchar_t>_>::
             back((basic_string<wchar_t,struct_std::char_traits<wchar_t>,class_std::allocator<wchar_t>_>
                   *)&DAT_025f7ea0);
    if (*(undefined4 **)pwVar2 == (undefined4 *)0x0) {
      uVar3 = 0;
    }
    else {
      uVar3 = (**(code **)**(undefined4 **)pwVar2)(1);
    }
    FUN_004cbb80(uVar3);
  }
  return;
}

