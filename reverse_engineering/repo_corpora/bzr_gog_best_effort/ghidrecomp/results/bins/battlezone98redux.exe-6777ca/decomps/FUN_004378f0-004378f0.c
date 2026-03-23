
void FUN_004378f0(void)

{
  char cVar1;
  undefined1 uVar2;
  int iVar3;
  int iVar4;
  char local_28 [32];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  if (DAT_00915580 == 0) {
    sprintf(local_28,"%02d.ogg",DAT_008e75f4);
    iVar3 = FUN_00481a60(local_28);
    if (iVar3 < 1) {
      DAT_008e75f4 = 0xffffffff;
    }
    else {
      iVar4 = FUN_00481af0(local_28);
      if (((iVar4 != 0) && (DAT_008e75f8 = FUN_0043f9b0(local_28,iVar4,iVar3,0), DAT_008e75f8 != -1)
          ) && (cVar1 = FUN_004376b0(), cVar1 != '\0')) {
        DAT_00915580 = 1;
        DAT_00915584 = DAT_00918324;
        FUN_0043f9e0(DAT_008e75f8);
        uVar2 = FUN_004376b0();
        FUN_00437800(uVar2);
      }
    }
  }
  FUN_0083e885();
  return;
}

