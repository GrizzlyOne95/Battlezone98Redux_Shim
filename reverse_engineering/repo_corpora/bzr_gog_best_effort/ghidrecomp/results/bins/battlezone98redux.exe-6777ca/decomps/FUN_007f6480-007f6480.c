
void FUN_007f6480(allocator<char> *param_1,char *param_2)

{
  undefined1 *puVar1;
  undefined1 local_6;
  char local_5;
  
  local_5 = *param_2;
  while (local_5 != '\0') {
    FUN_007f0bc0(local_5);
    puVar1 = &local_6;
    std::allocator<char>::allocator<char>(param_1);
    FUN_007f0750(puVar1);
    FUN_007efea0();
    param_2 = param_2 + 1;
    local_5 = *param_2;
  }
  FUN_007eba50(param_1);
  return;
}

