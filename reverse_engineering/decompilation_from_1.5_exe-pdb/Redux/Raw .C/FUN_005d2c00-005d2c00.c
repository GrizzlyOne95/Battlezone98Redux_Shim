
void __thiscall FUN_005d2c00(undefined4 param_1,int param_2,int param_3)

{
  int iVar1;
  
  if ((((-1 < param_2) && (-1 < param_3)) && (param_2 != DAT_009182dc)) && (param_3 != DAT_009182f4)
     ) {
    iVar1 = FUN_005d2970(param_2,param_3,param_1);
    FUN_005d2b30(iVar1);
    if (*(float *)(iVar1 + 0x24) <= 100.0) {
      *(int *)(&DAT_009182b0 + DAT_009182ac * 4) = iVar1;
      DAT_009182ac = DAT_009182ac + 1;
    }
  }
  return;
}

