
int FUN_005912f0(uint param_1,undefined2 param_2,undefined2 param_3,undefined2 param_4,
                undefined2 param_5)

{
  longlong lVar1;
  void *_Src;
  int iVar2;
  
  _Src = DAT_00918138;
  if (DAT_00918190 <= DAT_00918194) {
    if (DAT_00918138 == (void *)0x0) {
      DAT_00918194 = 0;
      DAT_00918190 = 0x400;
      DAT_00918138 = (void *)FUN_0083d92c(0x3000);
    }
    else {
      lVar1 = (ulonglong)(DAT_00918190 + 0x400) * 0xc;
      DAT_00918138 = (void *)FUN_0083d92c(-(uint)((int)((ulonglong)lVar1 >> 0x20) != 0) |
                                          (uint)lVar1);
      memcpy(DAT_00918138,_Src,DAT_00918190 * 0xc);
      operator_delete__(_Src);
      DAT_00918190 = DAT_00918190 + 0x400;
    }
  }
  *(undefined2 *)((int)DAT_00918138 + DAT_00918194 * 0xc) = param_2;
  *(undefined2 *)((int)DAT_00918138 + DAT_00918194 * 0xc + 4) = param_3;
  *(undefined2 *)((int)DAT_00918138 + DAT_00918194 * 0xc + 2) = param_4;
  *(undefined2 *)((int)DAT_00918138 + DAT_00918194 * 0xc + 6) = param_5;
  *(uint *)((int)DAT_00918138 + DAT_00918194 * 0xc + 8) = param_1 | 0x8000;
  *(int *)(DAT_02a13ca8 + DAT_02a13c98 * 4) = DAT_00918194;
  iVar2 = DAT_00918194;
  DAT_02a13c98 = DAT_02a13c98 + 1;
  DAT_00918194 = DAT_00918194 + 1;
  return iVar2;
}

