
void FUN_006a2700(void)

{
  char cVar1;
  wchar_t *pwVar2;
  
  while( true ) {
    cVar1 = FUN_0041fc90();
    if (cVar1 != '\0') break;
    pwVar2 = std::
             basic_string<wchar_t,struct_std::char_traits<wchar_t>,class_std::allocator<wchar_t>_>::
             back((basic_string<wchar_t,struct_std::char_traits<wchar_t>,class_std::allocator<wchar_t>_>
                   *)&DAT_0260af90);
    operator_delete(*(void **)pwVar2);
    FUN_004cbb80();
  }
  while( true ) {
    cVar1 = FUN_0041fc90();
    if (cVar1 != '\0') break;
    pwVar2 = std::
             basic_string<wchar_t,struct_std::char_traits<wchar_t>,class_std::allocator<wchar_t>_>::
             back((basic_string<wchar_t,struct_std::char_traits<wchar_t>,class_std::allocator<wchar_t>_>
                   *)&DAT_0260afd0);
    operator_delete(*(void **)pwVar2);
    FUN_004cbb80();
  }
  return;
}

