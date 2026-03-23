
undefined4 __thiscall FUN_00733160(allocator<char> *param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 *in_stack_00000010;
  undefined4 *in_stack_00000014;
  undefined4 uVar3;
  
  uVar2 = *in_stack_00000014;
  uVar3 = *in_stack_00000010;
  uVar1 = std::allocator<char>::allocator<char>(param_1);
  uVar2 = FUN_006f31f0(uVar1,uVar3,uVar2);
  *in_stack_00000014 = 0;
  return uVar2;
}

