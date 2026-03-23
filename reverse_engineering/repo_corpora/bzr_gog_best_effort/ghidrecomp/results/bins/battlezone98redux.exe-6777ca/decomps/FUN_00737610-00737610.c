
void __thiscall FUN_00737610(allocator<char> *param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  
  iVar1 = FUN_006e1d50();
  iVar3 = iVar1;
  uVar2 = std::allocator<char>::allocator<char>(param_1);
  iVar3 = FUN_00737f60(uVar2,param_2,param_3,iVar3);
  *(int *)(param_1 + 4) = (iVar3 - iVar1 >> 5) + *(int *)(param_1 + 4);
  return;
}

