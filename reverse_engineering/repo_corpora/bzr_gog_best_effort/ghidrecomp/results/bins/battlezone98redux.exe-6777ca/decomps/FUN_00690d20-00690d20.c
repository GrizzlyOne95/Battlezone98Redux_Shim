
uint FUN_00690d20(uint param_1)

{
  char cVar1;
  int iVar2;
  uint local_8;
  
  cVar1 = FUN_006a0600(param_1 & 0xffff);
  if (cVar1 == '\0') {
    cVar1 = FUN_006a05c0(param_1 & 0xffff);
    if (cVar1 == '\0') {
      local_8 = 1000000000;
      FUN_006a5f50(1,"AIBuild_CostOfObject (%d) - input is not a building or unit\n",param_1);
    }
    else {
      iVar2 = FUN_006a0670(param_1 & 0xffff);
      local_8 = *(uint *)(iVar2 + 0x20);
    }
  }
  else {
    iVar2 = FUN_006a0670(param_1 & 0xffff);
    local_8 = (uint)*(ushort *)(iVar2 + 0x56);
  }
  return local_8;
}

