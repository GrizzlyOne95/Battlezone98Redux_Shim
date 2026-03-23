
void __fastcall FUN_007cf9f0(int *param_1)

{
  float10 fVar1;
  
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
            ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             (param_1 + 0x24c),"");
  fVar1 = (float10)FUN_007d37b0(0xbf800000,1);
  (**(code **)(*(int *)param_1[0x255] + 0x28))((float)fVar1);
  (**(code **)(*param_1 + 0x3c))(&DAT_008a1ad8);
  *(undefined1 *)(param_1 + 0x51) = 0;
  FUN_007cc750();
  return;
}

