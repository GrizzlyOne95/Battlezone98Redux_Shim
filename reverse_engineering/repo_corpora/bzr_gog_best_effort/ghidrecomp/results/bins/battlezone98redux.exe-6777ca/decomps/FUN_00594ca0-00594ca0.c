
void __fastcall FUN_00594ca0(int *param_1)

{
  float fVar1;
  float *pfVar2;
  float fVar3;
  float10 fVar4;
  undefined1 local_d8 [4];
  undefined1 local_d4 [4];
  undefined8 local_d0;
  undefined8 local_c8;
  float local_c0;
  int local_bc;
  undefined8 local_b8;
  int local_b0;
  float local_ac;
  float local_a8;
  int local_a4;
  undefined8 local_a0;
  int *local_98;
  float local_94;
  float local_90;
  float local_8c;
  char local_88 [128];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  DAT_00917554 = param_1;
  local_98 = param_1;
  local_b8 = FUN_00689eb0();
  fVar3 = (float)((ulonglong)local_b8 >> 0x20);
  fVar1 = (float)local_b8;
  local_98[2] = (int)(fVar3 * 10.0);
  local_98[3] = (int)(fVar1 * 20.0);
  local_98[4] = (int)(fVar1 * 80.0) + local_98[3];
  local_98[5] = (int)(fVar1 * 80.0) + local_98[4];
  local_98[6] = (int)(fVar1 * 80.0) + local_98[5];
  local_98[7] = (int)(fVar1 * 80.0) + local_98[6];
  local_98[8] = (int)(fVar1 * 80.0) + local_98[7];
  local_98[9] = (int)(fVar3 * 16.0);
  local_98[10] = (int)(fVar3 * 11.0);
  local_98[0xb] = (int)(fVar3 * 5.0);
  local_a0 = local_b8;
  FUN_00594290();
  FUN_005972d0();
  FUN_005981a0();
  FUN_00595c60();
  FUN_00595250();
  local_a4 = FUN_00417c70();
  if (local_a4 != 0) {
    pfVar2 = (float *)(**(code **)(*(int *)(local_a4 + 0x18) + 0xc))();
    local_94 = *pfVar2;
    local_90 = pfVar2[1];
    local_8c = pfVar2[2];
    (**(code **)(*local_98 + 0x28))(DAT_009175a0,DAT_009175a4,&local_a8,&local_ac);
    fVar4 = (float10)FUN_007855e0((double)local_a8,(double)local_ac);
    local_c0 = (float)fVar4;
    sprintf(local_88,
            " Cursor: X(%.2f) Y(%.2f) Z(%.2f) | User: X(%.2f) Y(%.2f) Z(%.2f) | Zoom (%.3f)",
            (double)local_a8,(double)local_c0,(double)local_ac,(double)local_94,(double)local_90,
            (double)local_8c,(double)(float)local_98[0x10]);
    local_c8 = FUN_00689eb0();
    local_b0 = (int)((float)local_c8 * 15.0);
    local_d0 = FUN_00689eb0();
    local_bc = *(int *)(DAT_00917580 + 4) - (int)((float)((ulonglong)local_d0 >> 0x20) * 15.0);
    FUN_004c0100(DAT_00917580,local_b0,local_bc,local_d8,local_d4,local_88,DAT_00917550,DAT_0091755c
                 ,DAT_00917584,0,0,0);
  }
  FUN_0050cda0();
  DAT_00917554 = (int *)0x0;
  FUN_0083e885();
  return;
}

