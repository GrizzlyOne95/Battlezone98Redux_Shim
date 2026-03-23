
void FUN_007d2e20(void)

{
  undefined1 local_4c [4];
  undefined1 local_48 [4];
  undefined1 local_44 [4];
  int local_40;
  int local_3c;
  float local_38;
  float local_34;
  float local_30;
  float local_2c;
  int local_28;
  int local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  float local_10;
  float local_c;
  int local_8;
  
  (**(code **)(**(int **)(DAT_00920ea0 + 0xc) + 0x148))
            (&local_3c,&local_40,local_4c,local_48,local_44);
  local_24 = local_3c;
  local_2c = 2.0 / (float)((double)local_3c + (double)(&DAT_008a2fd0)[-(local_3c >> 0x1f)]);
  local_28 = local_40;
  local_30 = 2.0 / (float)((double)local_40 + (double)(&DAT_008a2fd0)[-(local_40 >> 0x1f)]);
  local_14 = 0;
  local_1c = 0x3f800000;
  local_20 = 0;
  local_18 = 0x3f800000;
  if ((*(uint *)(local_8 + 0x14) & 4) != 0) {
    local_14 = 0x3f800000;
    local_1c = 0;
  }
  if ((*(uint *)(local_8 + 0x14) & 2) != 0) {
    local_20 = 0x3f800000;
    local_18 = 0;
  }
  local_10 = (*(float *)(local_8 + 4) - 0.5) * local_2c - 1.0;
  local_c = (*(float *)(local_8 + 8) - 0.5) * local_30 - 1.0;
  local_34 = *(float *)(local_8 + 0xc) * local_2c;
  local_38 = *(float *)(local_8 + 0x10) * local_30;
  (**(code **)(**(int **)(local_8 + 0x120) + 0x11c))(local_10,-local_c,0);
  (**(code **)(**(int **)(local_8 + 0x120) + 0x148))(local_20,local_14);
  (**(code **)(**(int **)(local_8 + 0x120) + 0x154))(local_8 + 0x104);
  (**(code **)(**(int **)(local_8 + 0x120) + 0x11c))(local_10 + local_34,-local_c,0);
  (**(code **)(**(int **)(local_8 + 0x120) + 0x148))(local_18,local_14);
  (**(code **)(**(int **)(local_8 + 0x120) + 0x154))(local_8 + 0x104);
  (**(code **)(**(int **)(local_8 + 0x120) + 0x11c))(local_10 + local_34,-local_c - local_38,0);
  (**(code **)(**(int **)(local_8 + 0x120) + 0x148))(local_18,local_1c);
  (**(code **)(**(int **)(local_8 + 0x120) + 0x154))(local_8 + 0x104);
  (**(code **)(**(int **)(local_8 + 0x120) + 0x11c))(local_10,-local_c - local_38,0);
  (**(code **)(**(int **)(local_8 + 0x120) + 0x148))(local_20,local_1c);
  (**(code **)(**(int **)(local_8 + 0x120) + 0x154))(local_8 + 0x104);
  (**(code **)(**(int **)(local_8 + 0x120) + 0x158))(2);
  (**(code **)(**(int **)(local_8 + 0x120) + 0x158))(1);
  (**(code **)(**(int **)(local_8 + 0x120) + 0x158))(0);
  (**(code **)(**(int **)(local_8 + 0x120) + 0x158))(0);
  (**(code **)(**(int **)(local_8 + 0x120) + 0x158))(3);
  (**(code **)(**(int **)(local_8 + 0x120) + 0x158))(2);
  (**(code **)(**(int **)(local_8 + 0x120) + 200))(0x11);
  return;
}

