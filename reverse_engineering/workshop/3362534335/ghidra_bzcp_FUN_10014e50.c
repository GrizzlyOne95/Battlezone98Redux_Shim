
bool __fastcall FUN_10014e50(byte *param_1,uint param_2,byte *param_3,uint param_4)

{
  uint uVar1;
  bool bVar2;
  
  if (param_2 != param_4) {
    return false;
  }
  if (param_2 == 0) {
    return true;
  }
  while (uVar1 = param_2 - 4, 3 < param_2) {
    if (*(int *)param_1 != *(int *)param_3) goto LAB_10014e86;
    param_1 = param_1 + 4;
    param_3 = param_3 + 4;
    param_2 = uVar1;
  }
  if (uVar1 != 0xfffffffc) {
LAB_10014e86:
    bVar2 = *param_1 < *param_3;
    if ((*param_1 != *param_3) ||
       ((uVar1 != 0xfffffffd &&
        ((bVar2 = param_1[1] < param_3[1], param_1[1] != param_3[1] ||
         ((uVar1 != 0xfffffffe &&
          ((bVar2 = param_1[2] < param_3[2], param_1[2] != param_3[2] ||
           ((uVar1 != 0xffffffff && (bVar2 = param_1[3] < param_3[3], param_1[3] != param_3[3]))))))
         )))))) {
      return (-(uint)bVar2 | 1) == 0;
    }
  }
  return true;
}

