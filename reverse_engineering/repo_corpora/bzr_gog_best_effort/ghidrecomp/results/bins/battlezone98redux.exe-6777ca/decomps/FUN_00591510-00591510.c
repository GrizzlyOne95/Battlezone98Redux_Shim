
int FUN_00591510(undefined4 param_1,int param_2,int param_3,int param_4,uint param_5)

{
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  
  local_10 = -1;
  local_c = 0;
  do {
    if (DAT_02a13c98 <= local_c) {
LAB_0059163c:
      if (local_10 == -1) {
        FUN_005912f0(param_5,param_1,param_2,param_3,param_4);
      }
      return param_4;
    }
    local_8 = *(int *)(DAT_02a13ca8 + local_c * 4) * 0xc + DAT_00918138;
    if (*(short *)(local_8 + 4) < param_2) {
      if (((((*(uint *)(local_8 + 8) & 0xffff7fff) == param_5) &&
           (*(short *)(local_8 + 2) == param_3)) && (*(short *)(local_8 + 6) == param_4)) &&
         (*(int *)(DAT_02a13ca8 + local_c * 4) != local_10)) {
        *(uint *)(local_8 + 8) = *(uint *)(local_8 + 8) | 0x8000;
        local_10 = -2;
        goto LAB_0059163c;
      }
      if (((*(short *)(local_8 + 2) < param_4) && (param_3 < *(short *)(local_8 + 6))) &&
         (*(int *)(DAT_02a13ca8 + local_c * 4) != local_10)) {
        if (local_10 < 0) {
          local_10 = FUN_005912f0(param_5,param_1,param_2,param_3,param_4);
          local_8 = *(int *)(DAT_02a13ca8 + local_c * 4) * 0xc + DAT_00918138;
        }
        *(uint *)(local_8 + 8) = *(uint *)(local_8 + 8) & 0xffff7fff;
      }
    }
    local_c = local_c + 1;
  } while( true );
}

