
undefined4 FUN_0043c9d0(int *param_1,int *param_2,int *param_3,uint *param_4)

{
  int iVar1;
  uint uVar2;
  int *piVar3;
  int *local_8;
  
  if (param_2 != (int *)0x0) {
    *param_2 = 0;
  }
  if (param_3 != (int *)0x0) {
    *param_3 = 0;
  }
  if (param_4 != (uint *)0x0) {
    *param_4 = 0;
  }
  iVar1 = param_1[1];
  local_8 = param_1 + 3;
  if ((*param_1 == 0x46464952) && (param_1[2] == 0x45564157)) {
    while (local_8 < (int *)((int)param_1 + iVar1 + 8)) {
      uVar2 = local_8[1];
      piVar3 = local_8 + 2;
      if (*local_8 == 0x20746d66) {
        if ((param_2 != (int *)0x0) && (*param_2 == 0)) {
          if (uVar2 < 0xe) {
            return 0;
          }
          *param_2 = (int)piVar3;
          if (((param_3 == (int *)0x0) || (*param_3 != 0)) &&
             ((param_4 == (uint *)0x0 || (*param_4 != 0)))) {
            return 1;
          }
        }
      }
      else if ((*local_8 == 0x61746164) &&
              (((param_3 != (int *)0x0 && (*param_3 == 0)) ||
               ((param_4 != (uint *)0x0 && (*param_4 == 0)))))) {
        if (param_3 != (int *)0x0) {
          *param_3 = (int)piVar3;
        }
        if (param_4 != (uint *)0x0) {
          *param_4 = uVar2;
        }
        if ((param_2 == (int *)0x0) || (*param_2 != 0)) {
          return 1;
        }
      }
      local_8 = (int *)((uVar2 + 1 & 0xfffffffe) + (int)piVar3);
    }
  }
  return 0;
}

