
void __fastcall FUN_004380f0(int param_1)

{
  uint uVar1;
  int iVar2;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00845e88;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  *(undefined1 *)(param_1 + 0x34) = 0;
  *(byte *)(param_1 + 0x25) = *(byte *)(param_1 + 0x25) | 1;
  *(byte *)(param_1 + 0x25) = *(byte *)(param_1 + 0x25) & 0xfd;
  *(byte *)(param_1 + 0x25) = *(byte *)(param_1 + 0x25) & 0xfb;
  *(byte *)(param_1 + 0x25) = *(byte *)(param_1 + 0x25) & 0xf7;
  *(undefined4 *)(param_1 + 0x30) = 1;
  *(undefined1 *)(param_1 + 0x40) = 0;
  iVar2 = FUN_00481f10("audio.odf",uVar1);
  if (iVar2 != 0) {
    FUN_00589430("audio.odf");
    local_8 = 0;
    FUN_00589800(0x49172362,0x37e230bd,&DAT_008e762c,DAT_008e762c);
    FUN_00589800(0x49172362,0x6b9de01c,&DAT_008e7630,DAT_008e7630);
    FUN_00589800(0x49172362,0xaf94b358,&DAT_008e7654,DAT_008e7654);
    FUN_00589800(0x49172362,0xd5868120,&DAT_008e7660,DAT_008e7660);
    FUN_00589800(0x49172362,0x5e165aef,&DAT_008e7650,DAT_008e7650);
    FUN_00589800(0x49172362,0x79cffcbb,&DAT_008e7638,DAT_008e7638);
    FUN_00589800(0x49172362,0xca24532,&DAT_008e7644,DAT_008e7644);
    FUN_00589800(0x49172362,0x7a9fd210,&DAT_008e7640,DAT_008e7640);
    FUN_00589800(0x49172362,0x925b352e,&DAT_008e763c,DAT_008e763c);
    FUN_00589800(0x49172362,0x92f5be2c,&DAT_008e764c,DAT_008e764c);
    FUN_00589800(0x49172362,0x2e50edc,&DAT_008e7634,DAT_008e7644);
    FUN_00589800(0x49172362,0xc7834d4a,&DAT_008e866c,DAT_008e866c);
    FUN_00589800(0x49172362,0xdcb07fdc,&DAT_00917b14,DAT_00917b14);
    FUN_00589800(0x49172362,0xd58454fb,&DAT_008e8678,DAT_008e8678);
    FUN_00589800(0x49172362,0x55188f35,&DAT_008e8670,DAT_008e8670);
    FUN_00589800(0x49172362,0x88f86c72,&DAT_008e8664,DAT_008e8664);
    FUN_00589800(0x49172362,0xe358bda4,&DAT_008e8674,DAT_008e8674);
    FUN_00589800(0x49172362,0x14548923,&DAT_008e867c,DAT_008e867c);
    FUN_00589800(0x49172362,0x9074837d,&DAT_008e8680,DAT_008e8680);
    FUN_00589800(0x49172362,0xfbe7633a,&DAT_008e8668,DAT_008e8668);
    FUN_00589800(0x49172362,0x863e8495,&DAT_008e7648,DAT_008e7648);
    FUN_00589760(0x49172362,0xd2fb08d7,&DAT_008e765c,DAT_008e765c);
    FUN_00589760(0x49172362,0x550dcc8e,&DAT_008e7658,DAT_008e7658);
    if (0xffff < DAT_008e7658) {
      DAT_008e7658 = 0xffff;
    }
    if (DAT_008e7658 < 0) {
      DAT_008e7658 = 0;
    }
    local_8 = 0xffffffff;
    FUN_00589530();
  }
  ExceptionList = local_10;
  return;
}

