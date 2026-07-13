
void __thiscall FUN_004c0930(int param_1,double *param_2,undefined4 *param_3,float param_4)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  undefined2 *puVar3;
  float fVar4;
  undefined1 local_10 [8];
  byte local_8;
  byte bStack_7;
  
  if (*(uint *)(param_1 + 0x18028) < param_1 + 0x18028U) {
    fVar4 = (float)*(int *)(param_1 + 0x1802c) + param_4 * *(float *)(param_1 + 0x18034);
    if (fVar4 < (float)(*(int *)(param_1 + 0x1802c) + *(int *)(param_1 + 0x18030))) {
      puVar1 = *(undefined4 **)(param_1 + 0x18028);
      *(int *)(param_1 + 0x18028) = *(int *)(param_1 + 0x18028) + 0x30;
      *puVar1 = *(undefined4 *)param_2;
      puVar1[1] = *(undefined4 *)((int)param_2 + 4);
      puVar1[2] = *(undefined4 *)(param_2 + 1);
      puVar1[3] = *(undefined4 *)((int)param_2 + 0xc);
      puVar1[4] = *(undefined4 *)(param_2 + 2);
      puVar1[5] = *(undefined4 *)((int)param_2 + 0x14);
      puVar1[6] = *param_3;
      puVar1[7] = param_3[1];
      puVar1[8] = param_3[2];
      puVar1[9] = fVar4;
      puVar1[10] = *(undefined4 *)(param_1 + 0x18038);
      uVar2 = FUN_00780dc0((int)((double)DAT_02cc50e4 * *param_2),
                           (int)((double)DAT_02cc50e4 * param_2[2]));
      puVar3 = (undefined2 *)FUN_00780fd0(local_10,uVar2);
      local_8 = (byte)*puVar3;
      bStack_7 = (byte)((ushort)*puVar3 >> 8);
      puVar1[0xb] = (((int)((uint)local_8 * 7) >> 3) + 0x20U & 0xff) << 0x10 | 0xff000000 |
                    (((int)((uint)bStack_7 * 7) >> 3) + 0x20U & 0xff) << 8 |
                    ((int)((uint)*(byte *)(puVar3 + 1) * 7) >> 3) + 0x20U & 0xff;
    }
  }
  return;
}

