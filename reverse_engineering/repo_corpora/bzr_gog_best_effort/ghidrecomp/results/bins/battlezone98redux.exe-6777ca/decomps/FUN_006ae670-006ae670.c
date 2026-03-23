
undefined4 __thiscall FUN_006ae670(int *param_1,int param_2)

{
  undefined3 uVar1;
  undefined4 local_c;
  
  local_c = 0;
  do {
    if (*(uint *)*param_1 <= local_c) {
      FUN_006ae810(*(int *)*param_1 + 1);
      *(int *)(*param_1 + 4 + *(int *)*param_1 * 4) = param_2;
      *(int *)*param_1 = *(int *)*param_1 + 1;
      uVar1 = (undefined3)((uint)param_1 >> 8);
LAB_006ae6e7:
      return CONCAT31(uVar1,1);
    }
    if (*(int *)(*param_1 + 4 + local_c * 4) == param_2) {
      uVar1 = (undefined3)(local_c >> 8);
      goto LAB_006ae6e7;
    }
    local_c = local_c + 1;
  } while( true );
}

