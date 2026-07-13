
void FUN_0082fa32(undefined4 param_1,int param_2)

{
  int iVar1;
  
  if (*(char *)(param_2 + 6) == '\0') {
    iVar1 = (uint)*(byte *)(param_2 + 7) * 4 + 0x14;
  }
  else {
    iVar1 = (uint)*(byte *)(param_2 + 7) * 0x10 + 0x18;
  }
  FUN_00838869(param_1,param_2,iVar1,0);
  return;
}

