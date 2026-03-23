
void FUN_00780ff0(int param_1,int *param_2,int *param_3,int *param_4,int *param_5)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  double dVar6;
  double dVar7;
  undefined8 local_44;
  undefined8 local_3c;
  undefined8 local_34;
  undefined8 local_2c;
  undefined4 local_24;
  undefined8 local_18;
  
  if (DAT_008eaad8 == 3) {
    local_2c = *(double *)(param_1 + 0x160);
    local_34 = *(double *)(param_1 + 0x160);
    local_44 = *(double *)(param_1 + 0x170);
    local_3c = *(double *)(param_1 + 0x170);
    for (local_24 = 1; local_24 < 5; local_24 = local_24 + 1) {
      local_18 = *(double *)(param_1 + 0x168 + local_24 * 0x18) - *(double *)(param_1 + 0x168);
      if (local_18 < 0.0) {
        local_18 = -local_18;
      }
      local_18 = *(double *)(param_1 + 0x168) / local_18;
      dVar6 = local_18 *
              (*(double *)(param_1 + 0x160 + local_24 * 0x18) - *(double *)(param_1 + 0x160)) +
              *(double *)(param_1 + 0x160);
      dVar7 = local_18 *
              (*(double *)(param_1 + 0x170 + local_24 * 0x18) - *(double *)(param_1 + 0x170)) +
              *(double *)(param_1 + 0x170);
      if (dVar6 < local_2c) {
        local_2c = dVar6;
      }
      if (local_34 < dVar6) {
        local_34 = dVar6;
      }
      if (dVar7 < local_44) {
        local_44 = dVar7;
      }
      if (local_3c < dVar7) {
        local_3c = dVar7;
      }
    }
  }
  else {
    local_2c = *(double *)(param_1 + 0x160);
    local_34 = *(double *)(param_1 + 0x160);
    if (*(double *)(param_1 + 0x178) <= local_2c && local_2c != *(double *)(param_1 + 0x178)) {
      local_2c = *(double *)(param_1 + 0x178);
    }
    if (local_34 < *(double *)(param_1 + 0x178)) {
      local_34 = *(double *)(param_1 + 0x178);
    }
    if (*(double *)(param_1 + 400) <= local_2c && local_2c != *(double *)(param_1 + 400)) {
      local_2c = *(double *)(param_1 + 400);
    }
    if (local_34 < *(double *)(param_1 + 400)) {
      local_34 = *(double *)(param_1 + 400);
    }
    if (*(double *)(param_1 + 0x1a8) <= local_2c && local_2c != *(double *)(param_1 + 0x1a8)) {
      local_2c = *(double *)(param_1 + 0x1a8);
    }
    if (local_34 < *(double *)(param_1 + 0x1a8)) {
      local_34 = *(double *)(param_1 + 0x1a8);
    }
    if (*(double *)(param_1 + 0x1c0) <= local_2c && local_2c != *(double *)(param_1 + 0x1c0)) {
      local_2c = *(double *)(param_1 + 0x1c0);
    }
    if (local_34 < *(double *)(param_1 + 0x1c0)) {
      local_34 = *(double *)(param_1 + 0x1c0);
    }
    local_44 = *(double *)(param_1 + 0x170);
    local_3c = *(double *)(param_1 + 0x170);
    if (*(double *)(param_1 + 0x188) <= local_44 && local_44 != *(double *)(param_1 + 0x188)) {
      local_44 = *(double *)(param_1 + 0x188);
    }
    if (local_3c < *(double *)(param_1 + 0x188)) {
      local_3c = *(double *)(param_1 + 0x188);
    }
    if (*(double *)(param_1 + 0x1a0) <= local_44 && local_44 != *(double *)(param_1 + 0x1a0)) {
      local_44 = *(double *)(param_1 + 0x1a0);
    }
    if (local_3c < *(double *)(param_1 + 0x1a0)) {
      local_3c = *(double *)(param_1 + 0x1a0);
    }
    if (*(double *)(param_1 + 0x1b8) <= local_44 && local_44 != *(double *)(param_1 + 0x1b8)) {
      local_44 = *(double *)(param_1 + 0x1b8);
    }
    if (local_3c < *(double *)(param_1 + 0x1b8)) {
      local_3c = *(double *)(param_1 + 0x1b8);
    }
    if (*(double *)(param_1 + 0x1d0) <= local_44 && local_44 != *(double *)(param_1 + 0x1d0)) {
      local_44 = *(double *)(param_1 + 0x1d0);
    }
    if (local_3c < *(double *)(param_1 + 0x1d0)) {
      local_3c = *(double *)(param_1 + 0x1d0);
    }
  }
  dVar6 = (double)DAT_02cc50e4;
  dVar7 = (double)DAT_02cc50e4;
  iVar4 = (int)((double)DAT_02cc50e4 * local_34) + 1;
  iVar1 = (int)((double)DAT_02cc50e4 * local_3c) + 1;
  iVar3 = (int)(DAT_02ce99c8 * DAT_02cc50e4);
  iVar5 = (int)((double)DAT_02cc50e4 * *(double *)(param_1 + 0x160));
  iVar2 = (int)((double)DAT_02cc50e4 * *(double *)(param_1 + 0x170));
  *param_2 = iVar5 - iVar3;
  *param_4 = iVar5 + iVar3;
  *param_3 = iVar2 - iVar3;
  *param_5 = iVar2 + iVar3;
  if (*param_2 < (int)(dVar6 * local_2c)) {
    *param_2 = (int)(dVar6 * local_2c);
  }
  if (iVar4 < *param_4) {
    *param_4 = iVar4;
  }
  if (*param_3 < (int)(dVar7 * local_44)) {
    *param_3 = (int)(dVar7 * local_44);
  }
  if (iVar1 < *param_5) {
    *param_5 = iVar1;
  }
  FUN_0083e885();
  return;
}

