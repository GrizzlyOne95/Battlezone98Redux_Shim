
void FUN_00466be0(undefined4 param_1,undefined4 *param_2,float *param_3,undefined4 *param_4,
                 int *param_5)

{
  char cVar1;
  undefined4 local_20;
  undefined4 local_1c;
  uint local_18;
  int local_14;
  float local_10;
  int local_c;
  int local_8;
  
  *param_2 = 0;
  *param_3 = 10.0;
  *param_4 = 0x3f800000;
  *param_5 = 0;
  local_14 = FUN_00417ca0();
  if (local_14 != 0) {
    local_18 = FUN_00462510();
    for (local_8 = 0; local_8 < 5; local_8 = local_8 + 1) {
      if (((1 << ((byte)local_8 & 0x1f) & local_18) != 0) &&
         (local_c = FUN_00417f60(local_8), local_c != 0)) {
        if (*param_5 == 0) {
          *param_5 = local_c;
        }
        cVar1 = FUN_00466890(local_c,&local_1c,&local_10,&local_20);
        if (cVar1 != '\0') {
          if ((*(int *)(*(int *)(*param_5 + 8) + 0xc) != 0x44495350) &&
             (*(int *)(*(int *)(local_c + 8) + 0xc) == 0x44495350)) {
            local_10 = -1e+30;
          }
          if (*param_3 <= local_10 && local_10 != *param_3) {
            *param_2 = local_1c;
            *param_3 = local_10;
            *param_4 = local_20;
            *param_5 = local_c;
          }
        }
      }
    }
    *param_3 = *param_3 - 1.0;
  }
  return;
}

