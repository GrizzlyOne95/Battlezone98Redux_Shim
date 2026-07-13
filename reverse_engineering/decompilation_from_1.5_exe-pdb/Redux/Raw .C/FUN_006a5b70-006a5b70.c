
void FUN_006a5b70(float param_1,undefined4 param_2,float param_3,int param_4,int param_5,
                 float *param_6,float *param_7,int param_8,int param_9)

{
  float fVar1;
  float fVar2;
  byte bVar3;
  int iVar4;
  undefined4 *puVar5;
  int iVar6;
  int iVar7;
  void *pvVar8;
  float10 fVar9;
  int local_58;
  uint local_40;
  uint local_38;
  char local_20 [12];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084fbc8;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  iVar6 = FUN_006a08c0((double)param_1,local_14);
  iVar4 = *(int *)(DAT_00920f04 + 0x88);
  iVar7 = FUN_006a0920((double)param_3);
  param_4 = iVar6 / iVar4 + param_4;
  param_5 = iVar7 / *(int *)(DAT_00920f04 + 0x88) + param_5;
  if ((((-1 < param_4) && (-1 < param_5)) && (param_4 < *(int *)(DAT_00920f04 + 0x84))) &&
     (param_5 < *(int *)(DAT_00920f04 + 0x80))) {
    puVar5 = *(undefined4 **)(DAT_00920f04 + param_8 * 4);
    iVar4 = *(int *)(*(int *)(puVar5[0x20] + param_5 * 4) + param_4 * 4);
    if (*(int *)(iVar4 + 4) == param_9) {
      fVar9 = (float10)FUN_006a0980();
      fVar1 = (float)fVar9;
      fVar9 = (float10)FUN_006a09b0();
      fVar2 = (float)fVar9;
      bVar3 = *(byte *)(DAT_009310a8 +
                       *(int *)(iVar4 + 0x40) * DAT_02c00ed8 + *(int *)(iVar4 + 0x44));
      if (bVar3 == 0xff) {
        FUN_007d6a70("New_Patrol_Coords: untested gridLayout at (%d, %d)\n",
                     *(undefined4 *)(iVar4 + 0x40));
      }
      if (bVar3 == 0) {
        sprintf(local_20,"bad_%d_%d",*(undefined4 *)(iVar4 + 0x44));
        pvVar8 = operator_new(0x18);
        local_8 = 0;
        if (pvVar8 == (void *)0x0) {
          local_58 = 0;
        }
        else {
          local_58 = FUN_00460390(local_20,2);
        }
        local_8 = 0xffffffff;
        **(float **)(local_58 + 8) = fVar1 + 4.0;
        *(float *)(*(int *)(local_58 + 8) + 4) = fVar2 + 4.0;
        *(float *)(*(int *)(local_58 + 8) + 8) = fVar1 + 12.0;
        *(float *)(*(int *)(local_58 + 8) + 0xc) = fVar2 + 12.0;
        pvVar8 = operator_new(0x18);
        local_8 = 1;
        if (pvVar8 != (void *)0x0) {
          FUN_0046f190(local_58,*puVar5,0,1,0xffffffff,0);
        }
        local_8 = 0xffffffff;
      }
      else {
        local_40 = rand();
        local_40 = local_40 % 5;
        local_38 = 0;
        while ((local_38 < 5 && ((1 << ((byte)local_40 & 0x1f) & (uint)bVar3) == 0))) {
          local_40 = local_40 + 1;
          if (4 < local_40) {
            local_40 = 0;
          }
          local_38 = local_38 + 1;
        }
        if (local_38 != 5) {
          *param_6 = *(float *)(&DAT_008ed9f8 + local_38 * 8) * 16.0 + fVar1;
          *param_7 = *(float *)(&DAT_008ed9fc + local_38 * 8) * 16.0 + fVar2;
        }
      }
    }
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

