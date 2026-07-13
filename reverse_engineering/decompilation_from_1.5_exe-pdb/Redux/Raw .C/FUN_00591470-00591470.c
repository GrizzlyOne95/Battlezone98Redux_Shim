
void FUN_00591470(short param_1)

{
  int iVar1;
  int iVar2;
  undefined4 local_8;
  
  iVar1 = DAT_02a13c98;
  DAT_02a13c98 = 0;
  for (local_8 = 0; local_8 < iVar1; local_8 = local_8 + 1) {
    iVar2 = *(int *)(DAT_02a13ca8 + local_8 * 4) * 0xc + DAT_00918138;
    if ((*(uint *)(iVar2 + 8) & 0x8000) == 0) {
      DAT_02a13c98 = DAT_02a13c98 + -1;
    }
    else {
      *(short *)(iVar2 + 4) = param_1 + 1;
      *(undefined4 *)(DAT_02a13ca8 + DAT_02a13c98 * 4) = *(undefined4 *)(DAT_02a13ca8 + local_8 * 4)
      ;
    }
    DAT_02a13c98 = DAT_02a13c98 + 1;
  }
  return;
}

