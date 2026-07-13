
void FUN_00663d50(char *param_1)

{
  int iVar1;
  
  if (param_1 == (char *)0x0) {
    FUN_0041f830();
  }
  else {
    iVar1 = _stricmp(param_1,"dx9");
    if (iVar1 == 0) {
      std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
                ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                 &DAT_025f8d94,"Direct3D9 Rendering Subsystem");
    }
    else {
      iVar1 = _stricmp(param_1,"dx11");
      if (iVar1 == 0) {
        std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
                  ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                   &DAT_025f8d94,"Direct3D11 Rendering Subsystem");
      }
      else {
        iVar1 = _stricmp(param_1,"gl");
        if (iVar1 == 0) {
          std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
          operator=((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                    &DAT_025f8d94,"OpenGL Rendering Subsystem");
        }
      }
    }
  }
  return;
}

