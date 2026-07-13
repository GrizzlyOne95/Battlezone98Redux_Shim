
void __fastcall FUN_006d0e00(allocator<char> *param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  
  if (*(int *)(param_1 + 8) != 0) {
    uVar2 = *(undefined4 *)(param_1 + 8);
    uVar1 = *(undefined4 *)param_1;
    std::allocator<char>::allocator<char>(param_1);
    FUN_00417180(uVar1,uVar2);
  }
  return;
}

