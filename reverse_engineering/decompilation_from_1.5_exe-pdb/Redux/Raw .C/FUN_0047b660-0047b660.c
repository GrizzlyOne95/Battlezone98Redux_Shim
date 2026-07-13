
int __thiscall FUN_0047b660(int param_1,int param_2)

{
  int iVar1;
  undefined4 local_10;
  
  iVar1 = FUN_00435a40(param_2);
  if (*(byte *)(param_2 + iVar1) < 5) {
    local_10 = (uint)*(byte *)(param_2 + iVar1);
  }
  else {
    local_10 = 0xffffffff;
  }
  *(uint *)(param_1 + 0x104) = local_10;
  return iVar1 + 1;
}

