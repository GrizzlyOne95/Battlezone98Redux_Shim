
void FUN_00823330(int param_1,int param_2)

{
  int iVar1;
  uint local_c;
  
  iVar1 = *(int *)(param_1 + 8);
  *(uint *)(iVar1 + 0x120) = *(uint *)(iVar1 + 0x120) & 0xfffffffe;
  local_c = (uint)(param_2 != 0);
  *(uint *)(iVar1 + 0x120) = *(uint *)(iVar1 + 0x120) | local_c;
  return;
}

