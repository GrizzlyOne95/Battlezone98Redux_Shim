
void __fastcall FUN_004c18a0(int param_1)

{
  undefined4 uVar1;
  
  *(undefined4 *)(param_1 + 0x20) = 0xff000000;
  *(undefined4 *)(param_1 + 0x24) = 0xff4c4c4c;
  *(undefined4 *)(param_1 + 0x28) = 0xff999999;
  *(undefined4 *)(param_1 + 0x2c) = 0xffffffff;
  FUN_004c8390();
  FUN_004c22b0(&PTR_PTR_008e8204);
  FUN_004c22b0(&PTR_PTR_008e8124);
  uVar1 = FUN_0068bed0("edit_but.0");
  *(undefined4 *)(param_1 + 0x40) = uVar1;
  *(float *)(param_1 + 0xf4) = (float)*(int *)(param_1 + 0x34) * 0.1;
  *(undefined4 *)(param_1 + 0xec) = 0;
  *(undefined4 *)(param_1 + 0xf0) = 0;
  *(undefined4 *)(param_1 + 0xf8) = 0x3dcccccd;
  *(undefined4 *)(param_1 + 0xfc) = 0x3f800000;
  *(undefined4 *)(param_1 + 0x118) = 0;
  *(undefined4 *)(param_1 + 0x100) = DAT_008e812c;
  *(int *)(param_1 + 0x104) = DAT_008e8138 + 8;
  *(int *)(param_1 + 0x108) = *(int *)(param_1 + 0x100) + 0x85;
  *(int *)(param_1 + 0x10c) = *(int *)(param_1 + 0x104) + 0x85;
  *(int *)(param_1 + 0x110) = (*(int *)(param_1 + 0x108) - *(int *)(param_1 + 0x100)) + 1;
  *(int *)(param_1 + 0x114) = (*(int *)(param_1 + 0x10c) - *(int *)(param_1 + 0x104)) + 1;
  return;
}

