
int FUN_00615560(float *param_1,float *param_2,float param_3,float param_4,float param_5,
                float param_6,int param_7)

{
  float fVar1;
  float fVar2;
  float fVar3;
  int local_20;
  float local_1c;
  int local_c;
  float *local_8;
  
  local_8 = param_2 + param_7 * 6 + -6;
  local_c = 0;
  local_1c = *local_8 * param_3 + local_8[1] * param_4 + param_5;
  for (local_20 = 0; local_20 < param_7; local_20 = local_20 + 1) {
    fVar3 = *param_2 * param_3 + param_2[1] * param_4 + param_5;
    if (fVar3 <= 0.0) {
      if (0.0 < local_1c) {
        fVar1 = *param_2;
        fVar2 = *local_8;
        local_1c = local_1c / ((fVar1 - fVar2) * param_3 + (param_2[1] - local_8[1]) * param_4);
        param_1[1] = local_8[1] - local_1c * (param_2[1] - local_8[1]);
        *param_1 = *local_8 - local_1c * (fVar1 - fVar2);
        param_1[2] = local_8[2];
        param_1[5] = param_6;
        param_1 = param_1 + 6;
        local_c = local_c + 1;
      }
    }
    else if (local_1c <= 0.0) {
      param_1[6] = *param_2;
      param_1[7] = param_2[1];
      param_1[8] = param_2[2];
      param_1[9] = param_2[3];
      param_1[10] = param_2[4];
      param_1[0xb] = param_2[5];
      fVar1 = *param_2;
      fVar2 = *local_8;
      local_1c = local_1c / ((fVar1 - fVar2) * param_3 + (param_2[1] - local_8[1]) * param_4);
      param_1[1] = local_8[1] - local_1c * (param_2[1] - local_8[1]);
      *param_1 = *local_8 - local_1c * (fVar1 - fVar2);
      param_1[2] = local_8[2];
      param_1[5] = param_6;
      param_1 = param_1 + 0xc;
      local_c = local_c + 2;
    }
    else {
      *param_1 = *param_2;
      param_1[1] = param_2[1];
      param_1[2] = param_2[2];
      param_1[3] = param_2[3];
      param_1[4] = param_2[4];
      param_1[5] = param_2[5];
      param_1 = param_1 + 6;
      local_c = local_c + 1;
    }
    local_8 = param_2;
    param_2 = param_2 + 6;
    local_1c = fVar3;
  }
  return local_c;
}

