
void FUN_004578a0(undefined4 *param_1,undefined4 param_2,float *param_3,float param_4,
                 undefined4 param_5)

{
  float fVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  float10 fVar4;
  
  fVar4 = (float10)FUN_004497c0(param_5);
  fVar1 = (float)fVar4;
  uVar2 = FUN_00449690(param_5);
  puVar3 = (undefined4 *)
           FUN_00446360((float)((double)(fVar1 * param_3[3]) + *(double *)(param_3 + 10)),
                        (float)((double)(fVar1 * param_3[4]) + *(double *)(param_3 + 0xc)),
                        -(float)((double)(fVar1 * param_3[5]) + *(double *)(param_3 + 0xe)),uVar2,
                        param_4,0);
  *param_1 = *puVar3;
  param_1[1] = puVar3[1];
  param_1[2] = puVar3[2];
  param_1[3] = puVar3[3];
  param_1[4] = puVar3[4];
  param_1[5] = puVar3[5];
  puVar3 = (undefined4 *)
           FUN_00446360((float)(*(double *)(param_3 + 10) - (double)(fVar1 * param_3[3])),
                        (float)(*(double *)(param_3 + 0xc) - (double)(fVar1 * param_3[4])),
                        -(float)(*(double *)(param_3 + 0xe) - (double)(fVar1 * param_3[5])),uVar2,
                        param_4,0x3f800000);
  param_1[6] = *puVar3;
  param_1[7] = puVar3[1];
  param_1[8] = puVar3[2];
  param_1[9] = puVar3[3];
  param_1[10] = puVar3[4];
  param_1[0xb] = puVar3[5];
  puVar3 = (undefined4 *)
           FUN_00446360((float)((double)(fVar1 * *param_3) + *(double *)(param_3 + 10)),
                        (float)((double)(fVar1 * param_3[1]) + *(double *)(param_3 + 0xc)),
                        -(float)((double)(fVar1 * param_3[2]) + *(double *)(param_3 + 0xe)),uVar2,
                        param_4 + 0.5,0);
  param_1[0xc] = *puVar3;
  param_1[0xd] = puVar3[1];
  param_1[0xe] = puVar3[2];
  param_1[0xf] = puVar3[3];
  param_1[0x10] = puVar3[4];
  param_1[0x11] = puVar3[5];
  puVar3 = (undefined4 *)
           FUN_00446360((float)(*(double *)(param_3 + 10) - (double)(fVar1 * *param_3)),
                        (float)(*(double *)(param_3 + 0xc) - (double)(fVar1 * param_3[1])),
                        -(float)(*(double *)(param_3 + 0xe) - (double)(fVar1 * param_3[2])),uVar2,
                        param_4 + 0.5,0x3f800000);
  param_1[0x12] = *puVar3;
  param_1[0x13] = puVar3[1];
  param_1[0x14] = puVar3[2];
  param_1[0x15] = puVar3[3];
  param_1[0x16] = puVar3[4];
  param_1[0x17] = puVar3[5];
  FUN_0083e885();
  return;
}

