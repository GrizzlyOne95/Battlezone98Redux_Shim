
void FUN_0083869a(undefined4 param_1)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  char *pcVar4;
  undefined1 local_10 [8];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  uVar1 = FUN_00838733(param_1,1);
  iVar2 = FUN_0082d490(param_1,2);
  if (iVar2 == -1) {
    pcVar4 = "0123456789abcdef";
    iVar2 = 8;
    iVar3 = 8;
  }
  else {
    iVar2 = FUN_00838733(param_1,2);
    pcVar4 = "0123456789abcdef";
    if (iVar2 < 0) {
      iVar2 = -iVar2;
      pcVar4 = "0123456789ABCDEF";
    }
    iVar3 = iVar2;
    if (8 < iVar2) {
      iVar2 = 8;
      iVar3 = 8;
    }
  }
  while (-1 < iVar2 + -1) {
    (&stack0xffffffef)[iVar2] = pcVar4[uVar1 & 0xf];
    uVar1 = uVar1 >> 4;
    iVar2 = iVar2 + -1;
  }
  FUN_0082cd08(param_1,local_10,iVar3);
  FUN_0083e885();
  return;
}

