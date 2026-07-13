
undefined4 FUN_0077d560(double param_1,double param_2)

{
  int iVar1;
  int iVar2;
  undefined4 local_10;
  
  iVar1 = (int)((double)DAT_02cc50e4 * param_1);
  iVar2 = (int)((double)DAT_02cc50e4 * param_2);
  if ((((iVar1 < -0x17ff) || (0x67fe < iVar1)) || (iVar2 < -0x17ff)) ||
     ((0x67fe < iVar2 || ((iVar1 == 0 && (iVar2 == 0)))))) {
    local_10 = 0;
  }
  else {
    local_10 = 1;
  }
  return local_10;
}

