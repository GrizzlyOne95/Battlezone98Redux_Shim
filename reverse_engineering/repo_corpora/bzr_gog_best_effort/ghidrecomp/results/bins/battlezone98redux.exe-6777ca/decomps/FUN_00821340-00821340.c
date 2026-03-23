
void FUN_00821340(int param_1,int param_2)

{
  int iVar1;
  undefined4 local_c;
  
  iVar1 = *(int *)(param_1 + 8);
  *(uint *)(iVar1 + 0x5c) = *(uint *)(iVar1 + 0x5c) & 0xfffffffd;
  if (param_2 == 0) {
    local_c = 0;
  }
  else {
    local_c = 2;
  }
  *(uint *)(iVar1 + 0x5c) = *(uint *)(iVar1 + 0x5c) | local_c;
  return;
}

