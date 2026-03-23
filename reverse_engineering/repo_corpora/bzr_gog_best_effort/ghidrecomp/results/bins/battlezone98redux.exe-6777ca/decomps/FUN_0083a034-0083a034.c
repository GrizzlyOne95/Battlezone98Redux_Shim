
void FUN_0083a034(int param_1)

{
  short *psVar1;
  int iVar2;
  
  iVar2 = *(int *)(param_1 + 0x34);
  psVar1 = (short *)(iVar2 + 0x34);
  *psVar1 = *psVar1 + 1;
  if (200 < *(ushort *)(iVar2 + 0x34)) {
    FUN_00838ef5(param_1,"chunk has too many syntax levels",0);
  }
  return;
}

