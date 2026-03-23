
void FUN_0068d690(void *param_1,float *param_2,int param_3)

{
  int local_cb4;
  uint local_cb0;
  int local_cac;
  float local_ca8;
  int local_ca4;
  float *local_ca0;
  float *local_c9c;
  float local_c98 [804];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  FUN_0068d570(&local_cb4,&local_cb0,param_2,param_3);
  if (local_cb4 == 0) {
    if (local_cb0 != 0) {
      local_ca0 = local_c98;
      if ((local_cb0 & 8) != 0) {
        local_c9c = param_2 + param_3 * 6 + -6;
        local_ca4 = 0;
        for (local_cac = 0; local_cac < param_3; local_cac = local_cac + 1) {
          if (param_2[3] < 0.0) {
            if (0.0 <= local_c9c[3]) {
              local_ca8 = -local_c9c[3] / (param_2[3] - local_c9c[3]);
              *local_ca0 = (*param_2 - *local_c9c) * local_ca8 + *local_c9c;
              local_ca0[1] = (param_2[1] - local_c9c[1]) * local_ca8 + local_c9c[1];
              local_ca0[2] = (param_2[2] - local_c9c[2]) * local_ca8 + local_c9c[2];
              local_ca0[3] = 0.0;
              local_ca0[4] = (param_2[4] - local_c9c[4]) * local_ca8 + local_c9c[4];
              local_ca0 = local_ca0 + 6;
              local_ca4 = local_ca4 + 1;
            }
          }
          else if (local_c9c[3] < 0.0) {
            local_ca0[6] = *param_2;
            local_ca0[7] = param_2[1];
            local_ca0[8] = param_2[2];
            local_ca0[9] = param_2[3];
            local_ca0[10] = param_2[4];
            local_ca0[0xb] = param_2[5];
            local_ca8 = -local_c9c[3] / (param_2[3] - local_c9c[3]);
            *local_ca0 = (*param_2 - *local_c9c) * local_ca8 + *local_c9c;
            local_ca0[1] = (param_2[1] - local_c9c[1]) * local_ca8 + local_c9c[1];
            local_ca0[2] = (param_2[2] - local_c9c[2]) * local_ca8 + local_c9c[2];
            local_ca0[3] = 0.0;
            local_ca0[4] = (param_2[4] - local_c9c[4]) * local_ca8 + local_c9c[4];
            local_ca0 = local_ca0 + 0xc;
            local_ca4 = local_ca4 + 2;
          }
          else {
            *local_ca0 = *param_2;
            local_ca0[1] = param_2[1];
            local_ca0[2] = param_2[2];
            local_ca0[3] = param_2[3];
            local_ca0[4] = param_2[4];
            local_ca0[5] = param_2[5];
            local_ca0 = local_ca0 + 6;
            local_ca4 = local_ca4 + 1;
          }
          local_c9c = param_2;
          param_2 = param_2 + 6;
        }
        if (local_ca4 == 0) goto LAB_0068e5ee;
        param_3 = local_ca4;
        param_2 = local_ca0 + local_ca4 * -6;
      }
      if ((local_cb0 & 2) != 0) {
        local_c9c = param_2 + param_3 * 6 + -6;
        local_ca4 = 0;
        for (local_cac = 0; local_cac < param_3; local_cac = local_cac + 1) {
          if (param_2[4] < 0.0) {
            if (0.0 <= local_c9c[4]) {
              local_ca8 = -local_c9c[4] / (param_2[4] - local_c9c[4]);
              *local_ca0 = (*param_2 - *local_c9c) * local_ca8 + *local_c9c;
              local_ca0[1] = (param_2[1] - local_c9c[1]) * local_ca8 + local_c9c[1];
              local_ca0[2] = (param_2[2] - local_c9c[2]) * local_ca8 + local_c9c[2];
              local_ca0[3] = (param_2[3] - local_c9c[3]) * local_ca8 + local_c9c[3];
              local_ca0[4] = 0.0;
              local_ca0 = local_ca0 + 6;
              local_ca4 = local_ca4 + 1;
            }
          }
          else if (local_c9c[4] < 0.0) {
            local_ca0[6] = *param_2;
            local_ca0[7] = param_2[1];
            local_ca0[8] = param_2[2];
            local_ca0[9] = param_2[3];
            local_ca0[10] = param_2[4];
            local_ca0[0xb] = param_2[5];
            local_ca8 = -local_c9c[4] / (param_2[4] - local_c9c[4]);
            *local_ca0 = (*param_2 - *local_c9c) * local_ca8 + *local_c9c;
            local_ca0[1] = (param_2[1] - local_c9c[1]) * local_ca8 + local_c9c[1];
            local_ca0[2] = (param_2[2] - local_c9c[2]) * local_ca8 + local_c9c[2];
            local_ca0[3] = (param_2[3] - local_c9c[3]) * local_ca8 + local_c9c[3];
            local_ca0[4] = 0.0;
            local_ca0 = local_ca0 + 0xc;
            local_ca4 = local_ca4 + 2;
          }
          else {
            *local_ca0 = *param_2;
            local_ca0[1] = param_2[1];
            local_ca0[2] = param_2[2];
            local_ca0[3] = param_2[3];
            local_ca0[4] = param_2[4];
            local_ca0[5] = param_2[5];
            local_ca0 = local_ca0 + 6;
            local_ca4 = local_ca4 + 1;
          }
          local_c9c = param_2;
          param_2 = param_2 + 6;
        }
        if (local_ca4 == 0) goto LAB_0068e5ee;
        param_3 = local_ca4;
        param_2 = local_ca0 + local_ca4 * -6;
      }
      if ((local_cb0 & 4) != 0) {
        local_c9c = param_2 + param_3 * 6 + -6;
        local_ca4 = 0;
        for (local_cac = 0; local_cac < param_3; local_cac = local_cac + 1) {
          if (1.0 < param_2[3]) {
            if (local_c9c[3] <= 1.0) {
              local_ca8 = (1.0 - local_c9c[3]) / (param_2[3] - local_c9c[3]);
              *local_ca0 = (*param_2 - *local_c9c) * local_ca8 + *local_c9c;
              local_ca0[1] = (param_2[1] - local_c9c[1]) * local_ca8 + local_c9c[1];
              local_ca0[2] = (param_2[2] - local_c9c[2]) * local_ca8 + local_c9c[2];
              local_ca0[3] = 1.0;
              local_ca0[4] = (param_2[4] - local_c9c[4]) * local_ca8 + local_c9c[4];
              local_ca0 = local_ca0 + 6;
              local_ca4 = local_ca4 + 1;
            }
          }
          else if (1.0 < local_c9c[3]) {
            local_ca0[6] = *param_2;
            local_ca0[7] = param_2[1];
            local_ca0[8] = param_2[2];
            local_ca0[9] = param_2[3];
            local_ca0[10] = param_2[4];
            local_ca0[0xb] = param_2[5];
            local_ca8 = (1.0 - local_c9c[3]) / (param_2[3] - local_c9c[3]);
            *local_ca0 = (*param_2 - *local_c9c) * local_ca8 + *local_c9c;
            local_ca0[1] = (param_2[1] - local_c9c[1]) * local_ca8 + local_c9c[1];
            local_ca0[2] = (param_2[2] - local_c9c[2]) * local_ca8 + local_c9c[2];
            local_ca0[3] = 1.0;
            local_ca0[4] = (param_2[4] - local_c9c[4]) * local_ca8 + local_c9c[4];
            local_ca0 = local_ca0 + 0xc;
            local_ca4 = local_ca4 + 2;
          }
          else {
            *local_ca0 = *param_2;
            local_ca0[1] = param_2[1];
            local_ca0[2] = param_2[2];
            local_ca0[3] = param_2[3];
            local_ca0[4] = param_2[4];
            local_ca0[5] = param_2[5];
            local_ca0 = local_ca0 + 6;
            local_ca4 = local_ca4 + 1;
          }
          local_c9c = param_2;
          param_2 = param_2 + 6;
        }
        if (local_ca4 == 0) goto LAB_0068e5ee;
        param_3 = local_ca4;
        param_2 = local_ca0 + local_ca4 * -6;
      }
      if ((local_cb0 & 1) != 0) {
        local_c9c = param_2 + param_3 * 6 + -6;
        local_ca4 = 0;
        for (local_cac = 0; local_cac < param_3; local_cac = local_cac + 1) {
          if (1.0 < param_2[4] || param_2[4] == 1.0) {
            if (local_c9c[4] <= 1.0 && local_c9c[4] != 1.0) {
              local_ca8 = (1.0 - local_c9c[4]) / (param_2[4] - local_c9c[4]);
              *local_ca0 = (*param_2 - *local_c9c) * local_ca8 + *local_c9c;
              local_ca0[1] = (param_2[1] - local_c9c[1]) * local_ca8 + local_c9c[1];
              local_ca0[2] = (param_2[2] - local_c9c[2]) * local_ca8 + local_c9c[2];
              local_ca0[3] = (param_2[3] - local_c9c[3]) * local_ca8 + local_c9c[3];
              local_ca0[4] = 1.0;
              local_ca0 = local_ca0 + 6;
              local_ca4 = local_ca4 + 1;
            }
          }
          else if (1.0 < local_c9c[4] || local_c9c[4] == 1.0) {
            local_ca0[6] = *param_2;
            local_ca0[7] = param_2[1];
            local_ca0[8] = param_2[2];
            local_ca0[9] = param_2[3];
            local_ca0[10] = param_2[4];
            local_ca0[0xb] = param_2[5];
            local_ca8 = (1.0 - local_c9c[4]) / (param_2[4] - local_c9c[4]);
            *local_ca0 = (*param_2 - *local_c9c) * local_ca8 + *local_c9c;
            local_ca0[1] = (param_2[1] - local_c9c[1]) * local_ca8 + local_c9c[1];
            local_ca0[2] = (param_2[2] - local_c9c[2]) * local_ca8 + local_c9c[2];
            local_ca0[3] = (param_2[3] - local_c9c[3]) * local_ca8 + local_c9c[3];
            local_ca0[4] = 1.0;
            local_ca0 = local_ca0 + 0xc;
            local_ca4 = local_ca4 + 2;
          }
          else {
            *local_ca0 = *param_2;
            local_ca0[1] = param_2[1];
            local_ca0[2] = param_2[2];
            local_ca0[3] = param_2[3];
            local_ca0[4] = param_2[4];
            local_ca0[5] = param_2[5];
            local_ca0 = local_ca0 + 6;
            local_ca4 = local_ca4 + 1;
          }
          local_c9c = param_2;
          param_2 = param_2 + 6;
        }
        if (local_ca4 == 0) goto LAB_0068e5ee;
        param_3 = local_ca4;
        param_2 = local_ca0 + local_ca4 * -6;
      }
    }
    memmove(param_1,param_2,param_3 * 0x18);
  }
LAB_0068e5ee:
  FUN_0083e885();
  return;
}

