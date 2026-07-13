
void __thiscall FUN_0081e6c0(int param_1,undefined4 param_2)

{
  undefined4 local_c;
  
  FUN_0081e660();
  if (param_1 == 0) {
    local_c = 0;
  }
  else {
    local_c = param_1 + 0x10;
  }
  FUN_00574730(local_c,param_2);
  std::basic_ostream<char,struct_std::char_traits<char>_>::flush
            ((basic_ostream<char,struct_std::char_traits<char>_> *)(param_1 + 0x10));
  return;
}

