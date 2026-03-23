
char * __fastcall FUN_006ab6d0(int *param_1)

{
  char *local_c;
  
  if (*param_1 == 0) {
    local_c = "";
  }
  else {
    local_c = std::_Yarn<char>::c_str((_Yarn<char> *)(*param_1 + 0x18));
  }
  return local_c;
}

