
int * __thiscall FUN_0083fc20(int *param_1,uint param_2,undefined4 param_3)

{
  uint uVar1;
  int iVar2;
  
  iVar2 = param_1[4];
  if (-iVar2 - 1U <= param_2) {
                    /* WARNING: Subroutine does not return */
    std::_Xlength_error("string too long");
  }
  if (param_2 != 0) {
    uVar1 = iVar2 + param_2;
    if (0x7ffffffe < uVar1) {
                    /* WARNING: Subroutine does not return */
      std::_Xlength_error("string too long");
    }
    if ((uint)param_1[5] < uVar1) {
      FUN_004feb30(uVar1,iVar2);
      if (uVar1 == 0) {
        return param_1;
      }
    }
    else if (uVar1 == 0) {
      param_1[4] = 0;
      if ((uint)param_1[5] < 8) {
        *(undefined2 *)param_1 = 0;
        return param_1;
      }
      *(undefined2 *)*param_1 = 0;
      return param_1;
    }
    FID_conflict__Chassign(param_1[4],param_2,param_3);
    param_1[4] = uVar1;
    if (7 < (uint)param_1[5]) {
      *(undefined2 *)(*param_1 + uVar1 * 2) = 0;
      return param_1;
    }
    *(undefined2 *)((int)param_1 + uVar1 * 2) = 0;
  }
  return param_1;
}

