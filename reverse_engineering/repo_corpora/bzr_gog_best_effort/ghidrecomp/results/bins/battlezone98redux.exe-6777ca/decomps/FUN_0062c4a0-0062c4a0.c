
int * FUN_0062c4a0(int param_1,undefined2 param_2,int param_3,int *param_4)

{
  int iVar1;
  float10 fVar2;
  int local_c;
  int *local_8;
  
  local_8 = (int *)0x0;
  local_c = 0;
  do {
    if (DAT_00920c7c <= local_c) {
LAB_0062c4ed:
      if (local_8 == (int *)0x0) {
        if (DAT_00920c7c == 0x1400) {
          FUN_007d65d0("You had exceeded the maximum number of entities allowed (%d). Please reduce the size of this mission and try again"
                       ,0x1400);
        }
        local_8 = (int *)(&DAT_02a1f570 + DAT_00920c7c * 0xe4);
        DAT_00920c7c = DAT_00920c7c + 1;
      }
      *local_8 = param_1;
      *(undefined2 *)(local_8 + 1) = param_2;
      local_8[10] = 0;
      if (param_3 != 0) {
        local_8[9] = 1;
        local_8[10] = param_3;
      }
      if (param_4 != (int *)0x0) {
        local_8[0xb] = *param_4;
        local_8[0xc] = param_4[1];
        local_8[0xd] = param_4[2];
        local_8[0xe] = param_4[3];
        local_8[0xf] = param_4[4];
        local_8[0x10] = 1;
      }
      FUN_0062e650(param_1,local_8 + 0x11,local_8 + 0x14);
      local_8[2] = (int)(((float)local_8[0x11] + (float)local_8[0x14]) * 0.5);
      local_8[3] = (int)(((float)local_8[0x12] + (float)local_8[0x15]) * 0.5);
      local_8[4] = (int)(((float)local_8[0x13] + (float)local_8[0x16]) * 0.5);
      fVar2 = (float10)FUN_0062e590(param_1,local_8[2],local_8[3],local_8[4]);
      local_8[5] = (int)(float)fVar2;
      iVar1 = FUN_0062dfe0(param_1);
      if (iVar1 != 0) {
        if (DAT_00920c78 != (int *)0x0) {
          FUN_00680870(DAT_00920c78);
        }
        DAT_00920c78 = local_8;
        FUN_00680920(local_8);
      }
      FUN_0062c420(local_8);
      FUN_00820180(local_8 + 6,local_8 + 2,1,*local_8 + 0x20);
      iVar1 = *(int *)(*local_8 + 0x84);
      if ((1 < iVar1) && ((iVar1 < 4 || (iVar1 == 10)))) {
        FUN_007838a0(local_8);
      }
      *(undefined1 *)((int)local_8 + 7) = 0;
      return local_8;
    }
    if (*(int *)(&DAT_02a1f570 + local_c * 0xe4) == 0) {
      local_8 = (int *)(&DAT_02a1f570 + local_c * 0xe4);
      goto LAB_0062c4ed;
    }
    local_c = local_c + 1;
  } while( true );
}

