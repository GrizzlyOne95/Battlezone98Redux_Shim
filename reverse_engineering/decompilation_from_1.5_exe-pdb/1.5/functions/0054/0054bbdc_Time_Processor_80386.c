/*
 * Entry: 0054bbdc
 * Name: Time_Processor_80386
 * Namespace: Global
 * Signature: ushort Time_Processor_80386(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ushort __cdecl Time_Processor_80386(void)

{
  int iVar1;
  byte bVar2;
  undefined1 uVar3;
  undefined1 uVar4;
  short sVar5;
  
  out(0x43,0xb8);
  bVar2 = in(0x61);
  out(0x61,bVar2 | 1);
  out(0x42,0);
  out(0x42,0);
  sVar5 = 0x50;
  do {
    for (iVar1 = 0; (0x80000000U >> iVar1 & 1) == 0; iVar1 = iVar1 + 1) {
    }
    sVar5 = sVar5 + -1;
  } while (0 < sVar5);
  uVar3 = in(0x42);
  uVar4 = in(0x42);
  return -CONCAT11(uVar4,uVar3);
}
