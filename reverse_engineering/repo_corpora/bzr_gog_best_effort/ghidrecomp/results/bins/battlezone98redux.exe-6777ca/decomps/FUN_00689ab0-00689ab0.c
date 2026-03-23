
void FUN_00689ab0(undefined4 param_1,char *param_2,float *param_3,float *param_4)

{
  bool bVar1;
  float10 fVar2;
  int local_10;
  int local_c;
  int local_8;
  
  if (param_3 != (float *)0x0) {
    *param_3 = 0.0;
  }
  if (param_4 != (float *)0x0) {
    *param_4 = 0.0;
  }
  local_8 = 0;
  local_10 = 0;
  bVar1 = false;
  fVar2 = (float10)FUN_00689a90(param_1);
  local_c = (int)((float)fVar2 + 0.0);
  for (; *param_2 != '\0'; param_2 = param_2 + 1) {
    if (*param_2 == '\t') {
      for (; (!bVar1 && (*(int *)(&DAT_008ed6b0 + local_10 * 4) <= local_8));
          local_10 = local_10 + 1) {
        if (*(int *)(&DAT_008ed6b0 + local_10 * 4) == -1) {
          bVar1 = true;
        }
      }
      if (bVar1) {
        local_8 = local_8 + 0x20;
      }
      else {
        local_8 = *(int *)(&DAT_008ed6b0 + local_10 * 4);
      }
    }
    else if (*param_2 == '\n') {
      if ((param_3 != (float *)0x0) && (*param_3 <= (float)local_8 && (float)local_8 != *param_3)) {
        *param_3 = (float)local_8;
      }
      local_10 = 0;
      local_8 = 0;
      fVar2 = (float10)FUN_00689a70(param_1);
      local_c = (int)((float)local_c + (float)fVar2 + DAT_02bf0420 * 2.0);
    }
    else {
      fVar2 = (float10)FUN_00689a20(param_1,*param_2);
      local_8 = (int)((float)local_8 + (float)fVar2);
    }
  }
  if ((local_8 != 0) || (local_c < 0)) {
    fVar2 = (float10)FUN_00689a70(param_1);
    local_c = (int)((float)local_c + (float)fVar2);
  }
  if ((param_3 != (float *)0x0) && (*param_3 <= (float)local_8 && (float)local_8 != *param_3)) {
    *param_3 = (float)local_8;
  }
  if (param_4 != (float *)0x0) {
    *param_4 = (float)local_c;
  }
  return;
}

