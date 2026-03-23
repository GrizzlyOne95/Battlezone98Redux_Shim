
void __thiscall FUN_007c3c10(int param_1,int param_2)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  int local_c;
  
  local_c = 0;
  while( true ) {
    iVar1 = size();
    if (iVar1 <= local_c) {
      return;
    }
    FUN_004200d0(local_c);
    iVar1 = FUN_006cf300();
    if (iVar1 == param_2) break;
    local_c = local_c + 1;
  }
  *(int *)(param_1 + 0x1dc) = local_c;
  puVar2 = (undefined4 *)FUN_004200d0(local_c);
  uVar3 = std::allocator<char>::allocator<char>((allocator<char> *)*puVar2);
  (**(code **)(**(int **)(param_1 + 0x1f0) + 0x3c))(uVar3);
  FUN_007cc750();
  return;
}

