
void __thiscall FUN_006f31b0(allocator<char> *param_1,undefined4 param_2)

{
  undefined4 uVar1;
  undefined4 uVar2;
  
  uVar2 = *(undefined4 *)(param_1 + 8);
  uVar1 = std::allocator<char>::allocator<char>(param_1);
  uVar2 = FUN_006f60e0(uVar1,uVar2,param_2);
  FUN_006f6850(uVar2);
  return;
}

