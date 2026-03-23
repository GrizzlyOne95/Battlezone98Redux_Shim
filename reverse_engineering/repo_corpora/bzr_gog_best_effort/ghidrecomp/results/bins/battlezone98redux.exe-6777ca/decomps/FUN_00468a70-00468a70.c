
void FUN_00468a70(int param_1,char param_2)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  float *pfVar4;
  undefined4 *puVar5;
  float10 fVar6;
  undefined1 local_68 [4];
  undefined1 local_64 [4];
  undefined1 local_60 [4];
  undefined1 local_5c [4];
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 *local_48;
  float *local_44;
  float local_40;
  float local_3c;
  float local_38;
  float local_34;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  float local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  if (DAT_0260d178 != 0) {
    iVar2 = (*(code *)**(undefined4 **)(param_1 + 0x18))();
    if (*(int *)(iVar2 + 0x1c) == 5) {
      iVar2 = (**(code **)(*(int *)(param_1 + 0x18) + 0x2c))();
      local_48 = (undefined4 *)(iVar2 + 0x44);
      local_18 = *local_48;
      local_14 = *(undefined4 *)(iVar2 + 0x4c);
      local_10 = *(undefined4 *)(iVar2 + 0x50);
      local_c = *(undefined4 *)(iVar2 + 0x58);
      if (param_2 == '\0') {
        FUN_0046b370(&local_4c,&param_1);
        uVar3 = FID_conflict_begin(local_60);
        cVar1 = FUN_00420f10(uVar3);
        if (cVar1 != '\0') {
          iVar2 = FUN_00422150();
          local_18 = *(undefined4 *)(iVar2 + 4);
          local_14 = *(undefined4 *)(iVar2 + 8);
          local_10 = *(undefined4 *)(iVar2 + 0xc);
          local_c = *(undefined4 *)(iVar2 + 0x10);
          local_58 = local_4c;
          FUN_00429560(local_68,local_4c);
        }
      }
      else {
        puVar5 = (undefined4 *)FUN_0046b2c0(&param_1);
        *puVar5 = local_18;
        puVar5[1] = local_14;
        puVar5[2] = local_10;
        puVar5[3] = local_c;
      }
      FUN_00469840(local_18,local_14,local_10,local_c,param_2);
    }
    else {
      if (param_2 == '\0') {
        FUN_0046b370(&local_50,&param_1);
        uVar3 = FID_conflict_begin(local_5c);
        cVar1 = FUN_00420f10(uVar3);
        if (cVar1 != '\0') {
          iVar2 = FUN_00422150();
          local_28 = *(float *)(iVar2 + 4);
          local_24 = *(float *)(iVar2 + 8);
          local_20 = *(float *)(iVar2 + 0xc);
          local_1c = *(float *)(iVar2 + 0x10);
          local_54 = local_50;
          FUN_00429560(local_64,local_50);
        }
      }
      else {
        uVar3 = (**(code **)(*(int *)(param_1 + 0x18) + 0x30))(&local_40,&local_34);
        FUN_0062e650(uVar3);
        if ((param_2 != '\0') &&
           (((local_34 < local_40 || (local_30 < local_3c)) || (local_2c < local_38))))
        goto LAB_004690d8;
        local_44 = (float *)FUN_0045c4d0();
        DAT_00917380 = 4;
        DAT_0260d158 = (float)((double)(*local_44 * local_40 + local_44[6] * local_38) +
                              *(double *)(local_44 + 10));
        DAT_0260d15c = (float)((double)(local_44[2] * local_40 + local_44[8] * local_38) +
                              *(double *)(local_44 + 0xe));
        DAT_0260d160 = (float)((double)(*local_44 * local_34 + local_44[6] * local_38) +
                              *(double *)(local_44 + 10));
        DAT_0260d164 = (float)((double)(local_44[2] * local_34 + local_44[8] * local_38) +
                              *(double *)(local_44 + 0xe));
        DAT_0260d168 = (float)((double)(*local_44 * local_34 + local_44[6] * local_2c) +
                              *(double *)(local_44 + 10));
        DAT_0260d16c = (float)((double)(local_44[2] * local_34 + local_44[8] * local_2c) +
                              *(double *)(local_44 + 0xe));
        DAT_0260d170 = (float)((double)(*local_44 * local_40 + local_44[6] * local_2c) +
                              *(double *)(local_44 + 10));
        DAT_0260d174 = (float)((double)(local_44[2] * local_40 + local_44[8] * local_2c) +
                              *(double *)(local_44 + 0xe));
        fVar6 = (float10)FUN_00456080(DAT_0260d168,DAT_0260d170);
        fVar6 = (float10)FUN_00456080(DAT_0260d158,DAT_0260d160,(float)fVar6);
        fVar6 = (float10)FUN_00456080((float)fVar6);
        local_28 = (float)fVar6;
        fVar6 = (float10)FUN_00456080(DAT_0260d16c,DAT_0260d174);
        fVar6 = (float10)FUN_00456080(DAT_0260d15c,DAT_0260d164,(float)fVar6);
        fVar6 = (float10)FUN_00456080((float)fVar6);
        local_24 = (float)fVar6;
        fVar6 = (float10)FUN_0044fb20(DAT_0260d168,DAT_0260d170);
        fVar6 = (float10)FUN_0044fb20(DAT_0260d158,DAT_0260d160,(float)fVar6);
        fVar6 = (float10)FUN_0044fb20((float)fVar6);
        local_20 = (float)fVar6;
        fVar6 = (float10)FUN_0044fb20(DAT_0260d16c,DAT_0260d174);
        fVar6 = (float10)FUN_0044fb20(DAT_0260d15c,DAT_0260d164,(float)fVar6);
        fVar6 = (float10)FUN_0044fb20((float)fVar6);
        local_1c = (float)fVar6;
        pfVar4 = (float *)FUN_0046b2c0(&param_1);
        *pfVar4 = local_28;
        pfVar4[1] = local_24;
        pfVar4[2] = local_20;
        pfVar4[3] = local_1c;
      }
      FUN_004698a0(local_28,local_24,local_20,local_1c,param_2);
      DAT_00917380 = 0;
    }
  }
LAB_004690d8:
  FUN_0083e885();
  return;
}

