
void FUN_00692ce0(int param_1,int param_2)

{
  int iVar1;
  bool bVar2;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_8;
  
  local_8 = 1;
  bVar2 = false;
  do {
    iVar1 = *(int *)(param_1 + 0xbc + local_8 * 4);
    if ((*(int *)(param_1 + 0x13c + local_8 * 4) != 0) && ((!bVar2 || (iVar1 < local_18)))) {
      local_14 = local_8;
      bVar2 = true;
      local_18 = iVar1;
    }
    local_8 = local_8 + 1;
  } while (local_8 < 0x20);
  *(int *)(param_1 + 0xbc + local_14 * 4) = *(int *)(param_1 + 0xbc + local_14 * 4) + param_2;
  return;
}

