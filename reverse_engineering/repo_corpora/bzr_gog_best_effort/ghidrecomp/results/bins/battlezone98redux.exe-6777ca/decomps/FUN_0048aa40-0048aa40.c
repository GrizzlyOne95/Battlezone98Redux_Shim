
undefined4 __thiscall FUN_0048aa40(int *param_1,uint param_2)

{
  undefined4 uVar1;
  uint uVar2;
  int iVar3;
  undefined1 local_5;
  
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  if (param_2 == 0) {
    uVar1 = 0;
  }
  else {
    uVar2 = FID_conflict_max_size();
    if (uVar2 < param_2) {
      FUN_00423e40();
    }
    else {
      uVar2 = param_2;
      Getal(&local_5);
      iVar3 = allocate(uVar2);
      *param_1 = iVar3;
      param_1[1] = *param_1;
      param_1[2] = *param_1 + param_2 * 4;
    }
    uVar1 = 1;
  }
  return uVar1;
}

