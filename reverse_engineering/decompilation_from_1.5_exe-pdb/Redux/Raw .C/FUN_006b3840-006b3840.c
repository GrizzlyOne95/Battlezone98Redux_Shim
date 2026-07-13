
void FUN_006b3840(void)

{
  char cVar1;
  short sVar2;
  short sVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined1 local_40 [28];
  undefined1 local_24 [28];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  uVar4 = FUN_006b3750(local_24);
  uVar5 = FUN_006b3750(local_40);
  cVar1 = FUN_006b3430(uVar5,uVar4);
  if (cVar1 != '\0') {
    sVar2 = FUN_006b36c0();
    sVar3 = FUN_006b36c0();
    if (sVar2 == sVar3) {
      uVar4 = 1;
      goto LAB_006b38a4;
    }
  }
  uVar4 = 0;
LAB_006b38a4:
  FUN_0083e885(uVar4);
  return;
}

