
void FUN_004df9b0(void)

{
  basic_string<wchar_t,struct_std::char_traits<wchar_t>,class_std::allocator<wchar_t>_> *this;
  int iVar1;
  wchar_t *pwVar2;
  int local_8;
  
  this = DAT_00917a74;
  if (DAT_00917a74 !=
      (basic_string<wchar_t,struct_std::char_traits<wchar_t>,class_std::allocator<wchar_t>_> *)0x0)
  {
    iVar1 = size();
    local_8 = 0;
    while (local_8 < iVar1) {
      pwVar2 = std::
               basic_string<wchar_t,struct_std::char_traits<wchar_t>,class_std::allocator<wchar_t>_>
               ::back(this);
      (**(code **)(*(int *)(*(int *)pwVar2 + 0x18) + 0x10))();
      local_8 = local_8 + 1;
    }
  }
  return;
}

