
float10 FUN_004504a0(void)

{
  double dVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = FUN_004505c0();
  dVar1 = (double)(&DAT_008a2fd0)[-(iVar2 >> 0x1f)];
  iVar3 = FUN_004187d0();
  return (float10)((float)((double)iVar2 + dVar1) /
                  (float)((double)iVar3 + (double)(&DAT_008a2fd0)[-(iVar3 >> 0x1f)]));
}

