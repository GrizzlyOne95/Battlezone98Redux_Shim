
uint FUN_0058dd20(float param_1,float param_2,float param_3,float param_4,float param_5,
                 float param_6,float param_7,float param_8,float *param_9,float *param_10)

{
  uint3 uVar1;
  float *pfVar2;
  uint uVar3;
  float fVar4;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  
  local_c = param_3 - param_1;
  if (local_c == 0.0) {
    local_c = 1e-05;
  }
  local_c = (param_4 - param_2) / local_c;
  local_10 = param_7 - param_5;
  if (local_10 == 0.0) {
    local_10 = 1e-05;
  }
  local_10 = (param_8 - param_6) / local_10;
  param_2 = param_2 - local_c * param_1;
  fVar4 = param_6 - local_10 * param_5;
  local_8 = local_c - local_10;
  if (local_8 == 0.0) {
    local_8 = 1e-05;
  }
  *param_9 = (fVar4 - param_2) / local_8;
  *param_10 = (fVar4 * local_c - param_2 * local_10) / local_8;
  pfVar2 = (float *)((uint)CONCAT21((short)((uint)param_9 >> 0x10),
                                    (param_5 == param_7) << 6 | (NAN(param_5) || NAN(param_7)) << 2
                                    | 2U | param_5 < param_7) << 8);
  if ((param_5 == param_7) ||
     ((param_5 < *param_9 || param_5 == *param_9 && (pfVar2 = param_9, *param_9 < param_7)))) {
    uVar1 = CONCAT21((short)((uint)pfVar2 >> 0x10),
                     (param_6 == param_8) << 6 | (NAN(param_6) || NAN(param_8)) << 2 | 2U |
                     param_6 < param_8);
    if ((param_6 == param_8) ||
       ((param_6 < *param_10 || param_6 == *param_10 && (*param_10 < param_8)))) {
      uVar3 = CONCAT31(uVar1,1);
    }
    else {
      uVar3 = (uint)uVar1 << 8;
    }
  }
  else {
    uVar3 = (uint)pfVar2 & 0xffffff00;
  }
  return uVar3;
}

