
void __thiscall FUN_007f1430(int param_1,undefined1 *param_2)

{
  char cVar1;
  undefined1 *puVar2;
  undefined1 local_5;
  
  cVar1 = FUN_007f1d30(param_2);
  if (cVar1 != '\0') {
    local_5 = *param_2;
    puVar2 = &local_5;
    std::allocator<char>::allocator<char>(*(allocator<char> **)(param_1 + 0x18));
    FUN_007f09b0(puVar2);
  }
  return;
}

