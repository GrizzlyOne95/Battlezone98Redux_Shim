
void FUN_0082df5b(int param_1,undefined4 param_2)

{
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  undefined1 local_44 [60];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  uVar1 = FUN_0082e8e4(param_1,param_2,&stack0x0000000c);
  iVar3 = *(int *)(param_1 + 0x14);
  if (((*(int **)(iVar3 + 4))[2] == 6) && (*(char *)(**(int **)(iVar3 + 4) + 6) == '\0')) {
    uVar2 = FUN_0082da9d(param_1,iVar3);
    iVar3 = FUN_0082dc5a(iVar3,0x3c);
    FUN_0082e741(local_44,*(int *)(iVar3 + 0x20) + 0x10);
    FUN_0082e8cd(param_1,"%s:%d: %s",local_44,uVar2,uVar1);
  }
  FUN_0082de88(param_1);
  FUN_0083e885();
  return;
}

