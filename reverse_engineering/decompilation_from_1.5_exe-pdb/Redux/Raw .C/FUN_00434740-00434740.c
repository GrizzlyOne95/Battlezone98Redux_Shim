
void FUN_00434740(int param_1,undefined **param_2)

{
  char cVar1;
  int iVar2;
  int local_8;
  
  if (DAT_00915574 == 0) {
    DAT_00915574 = 1;
    if (param_1 != 0) {
      for (local_8 = 0; local_8 < 0x7d; local_8 = local_8 + 1) {
        (&PTR_DAT_008e7070)[local_8] = *(undefined **)(param_1 + local_8 * 4);
      }
    }
    if (param_2 == (undefined **)0x0) {
      param_2 = &PTR_s_Escape_Key_008ec2a0;
    }
    for (local_8 = 0; local_8 < 0x7d; local_8 = local_8 + 1) {
      *(undefined **)(&DAT_02cf4020 + local_8 * 4) = param_2[local_8];
    }
    iVar2 = FUN_00434700();
    if (iVar2 != 0) {
      DAT_008e73dc = 0xfc;
      DAT_008e73de = 0x2b;
      DAT_008e73e2 = 0x2d;
      DAT_008e73e6 = 0xe4;
      DAT_008e73e8 = 0xf6;
      DAT_008e741e = 0xdf;
      DAT_008e7420 = 0x60;
      DAT_008e7422 = 0x27;
      DAT_008e7424 = 0xe4;
      DAT_008e742c = 0x3c;
    }
    for (local_8 = 0; local_8 < 0x100; local_8 = local_8 + 1) {
      if (*(short *)(&DAT_008e7268 + local_8 * 2) == 0) {
        cVar1 = FUN_00619f40(local_8);
        iVar2 = tolower((int)cVar1);
        *(short *)(&DAT_008e7268 + local_8 * 2) = (short)iVar2;
      }
    }
  }
  return;
}

