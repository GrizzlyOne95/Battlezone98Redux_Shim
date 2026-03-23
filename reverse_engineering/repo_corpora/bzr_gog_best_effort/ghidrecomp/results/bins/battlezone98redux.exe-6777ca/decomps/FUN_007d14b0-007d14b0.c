
void FUN_007d14b0(undefined4 param_1,undefined4 param_2,float param_3,float param_4)

{
  int iVar1;
  int iVar2;
  float10 fVar3;
  undefined1 local_d0 [12];
  undefined1 local_c4 [44];
  double local_98;
  undefined1 local_88 [24];
  float local_70;
  int *local_68;
  int local_60;
  int local_44;
  int local_24;
  float local_18;
  int local_10;
  int local_c;
  int local_8;
  
  iVar2 = FUN_0044d2a0();
  local_68 = *(int **)(iVar2 + 0xc);
  (**(code **)(*local_68 + 0x148))(&local_c,&local_10,local_d0,local_88,local_c4);
  local_44 = local_c;
  iVar2 = local_c >> 0x1f;
  local_98 = (double)local_c + (double)(&DAT_008a2fd0)[-iVar2];
  *(float *)(local_8 + 0x18) = (float)local_98 / 1440.0;
  local_24 = local_10;
  iVar1 = local_10 >> 0x1f;
  *(float *)(local_8 + 0x1c) = (float)((double)local_10 + (double)(&DAT_008a2fd0)[-iVar1]) / 1080.0;
  *(undefined4 *)(local_8 + 4) = param_1;
  *(undefined4 *)(local_8 + 8) = param_2;
  *(float *)(local_8 + 0xc) = param_3;
  *(float *)(local_8 + 0x10) = param_4;
  if ((*(uint *)(local_8 + 0x14) & 1) == 0) {
    if ((*(uint *)(local_8 + 0x14) & 8) == 0) {
      if ((*(uint *)(local_8 + 0x14) & 0x40) == 0) {
        if ((*(uint *)(local_8 + 0x14) & 0x80) == 0) {
          if ((*(uint *)(local_8 + 0x14) & 0x20) == 0) {
            *(float *)(local_8 + 4) = *(float *)(local_8 + 4) * *(float *)(local_8 + 0x18);
            *(float *)(local_8 + 0xc) = *(float *)(local_8 + 0xc) * *(float *)(local_8 + 0x18);
          }
          else {
            *(float *)(local_8 + 4) = *(float *)(local_8 + 4) * *(float *)(local_8 + 0x1c);
            *(float *)(local_8 + 0xc) = *(float *)(local_8 + 0xc) * *(float *)(local_8 + 0x1c);
          }
        }
        else {
          local_60 = local_c;
          local_18 = (float)((double)local_c + (double)(&DAT_008a2fd0)[-iVar2]) / 1920.0;
          if ((*(uint *)(local_8 + 0x14) & 0x20) == 0) {
            *(float *)(local_8 + 4) = ((1920.0 - param_3) + *(float *)(local_8 + 0xfc)) * local_18;
            *(float *)(local_8 + 0xc) = *(float *)(local_8 + 0xc) * *(float *)(local_8 + 0x18);
          }
          else {
            *(float *)(local_8 + 0xc) = *(float *)(local_8 + 0xc) * *(float *)(local_8 + 0x1c);
            *(float *)(local_8 + 4) =
                 (*(float *)(local_8 + 0xfc) + 1920.0) * local_18 - *(float *)(local_8 + 0xc);
          }
        }
      }
      else {
        *(float *)(local_8 + 4) = *(float *)(local_8 + 0x18) * 720.0;
        if ((*(uint *)(local_8 + 0x14) & 0x20) == 0) {
          *(float *)(local_8 + 0xc) = *(float *)(local_8 + 0xc) * *(float *)(local_8 + 0x18);
        }
        else {
          *(float *)(local_8 + 0xc) = *(float *)(local_8 + 0xc) * *(float *)(local_8 + 0x1c);
        }
        *(float *)(local_8 + 4) = *(float *)(local_8 + 4) - *(float *)(local_8 + 0xc) / 2.0;
      }
      *(float *)(local_8 + 8) = *(float *)(local_8 + 8) * *(float *)(local_8 + 0x1c);
      *(float *)(local_8 + 0x10) = *(float *)(local_8 + 0x10) * *(float *)(local_8 + 0x1c);
    }
    if (*(int *)(local_8 + 0x13c) != 0) {
      fVar3 = (float10)FUN_007d37b0();
      local_70 = (float)fVar3;
      *(float *)(local_8 + 4) = local_70 + *(float *)(local_8 + 4);
      fVar3 = (float10)FUN_007d37d0();
      *(float *)(local_8 + 8) = (float)fVar3 + *(float *)(local_8 + 8);
    }
  }
  else if ((*(uint *)(local_8 + 0x14) & 0x100) == 0) {
    if ((*(uint *)(local_8 + 0x14) & 0x200) == 0) {
      *(float *)(local_8 + 0xc) = (float)((double)local_c + (double)(&DAT_008a2fd0)[-iVar2]);
      *(float *)(local_8 + 0x10) = (float)((double)local_10 + (double)(&DAT_008a2fd0)[-iVar1]);
    }
    else {
      *(undefined4 *)(local_8 + 8) = 0;
      *(float *)(local_8 + 0xc) = *(float *)(local_8 + 0x1c) * 1920.0;
      *(float *)(local_8 + 0x10) = (float)((double)local_10 + (double)(&DAT_008a2fd0)[-iVar1]);
      *(float *)(local_8 + 4) =
           ((float)((double)local_c + (double)(&DAT_008a2fd0)[-iVar2]) - *(float *)(local_8 + 0xc))
           / 2.0;
    }
  }
  else if ((param_3 == 0.0) || (param_4 == 0.0)) {
    *(undefined4 *)(local_8 + 8) = 0;
    *(float *)(local_8 + 0xc) = *(float *)(local_8 + 0x1c) * 1440.0;
    *(float *)(local_8 + 0x10) = (float)((double)local_10 + (double)(&DAT_008a2fd0)[-iVar1]);
    *(float *)(local_8 + 4) =
         ((float)((double)local_c + (double)(&DAT_008a2fd0)[-iVar2]) - *(float *)(local_8 + 0xc)) /
         2.0;
    if (*(float *)(local_8 + 4) <= 0.0 && *(float *)(local_8 + 4) != 0.0) {
      *(undefined4 *)(local_8 + 4) = 0;
      *(float *)(local_8 + 0x10) = *(float *)(local_8 + 0x18) * 1080.0;
      *(float *)(local_8 + 8) =
           ((float)((double)local_10 + (double)(&DAT_008a2fd0)[-iVar1]) - *(float *)(local_8 + 0x10)
           ) / 2.0;
      *(float *)(local_8 + 0xc) = (float)((double)local_c + (double)(&DAT_008a2fd0)[-iVar2]);
    }
  }
  else {
    param_4 = (param_3 * 1.0) / param_4;
    if (((float)((double)local_c + (double)(&DAT_008a2fd0)[-iVar2]) * 1.0) /
        (float)((double)local_10 + (double)(&DAT_008a2fd0)[-iVar1]) < param_4) {
      *(undefined4 *)(local_8 + 4) = 0;
      *(float *)(local_8 + 0x10) =
           (float)((double)local_c + (double)(&DAT_008a2fd0)[-iVar2]) / param_4;
      *(float *)(local_8 + 8) =
           ((float)((double)local_10 + (double)(&DAT_008a2fd0)[-iVar1]) - *(float *)(local_8 + 0x10)
           ) / 2.0;
      *(float *)(local_8 + 0xc) = (float)((double)local_c + (double)(&DAT_008a2fd0)[-iVar2]);
    }
    else {
      *(undefined4 *)(local_8 + 8) = 0;
      *(float *)(local_8 + 0xc) =
           (float)((double)local_10 + (double)(&DAT_008a2fd0)[-iVar1]) * param_4;
      *(float *)(local_8 + 0x10) = (float)((double)local_10 + (double)(&DAT_008a2fd0)[-iVar1]);
      *(float *)(local_8 + 4) =
           ((float)((double)local_c + (double)(&DAT_008a2fd0)[-iVar2]) - *(float *)(local_8 + 0xc))
           / 2.0;
    }
  }
  return;
}

