
void __fastcall FUN_00626800(void *param_1)

{
  char cVar1;
  wchar_t *pwVar2;
  
  while( true ) {
    cVar1 = FUN_0041fc90(param_1);
    if (cVar1 != '\0') break;
    pwVar2 = std::
             basic_string<wchar_t,struct_std::char_traits<wchar_t>,class_std::allocator<wchar_t>_>::
             back((basic_string<wchar_t,struct_std::char_traits<wchar_t>,class_std::allocator<wchar_t>_>
                   *)&DAT_025f882c);
    param_1 = *(void **)pwVar2;
    operator_delete(param_1);
    FUN_004cbb80();
  }
  return;
}

