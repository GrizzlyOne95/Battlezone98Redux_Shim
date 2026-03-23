
void __thiscall FUN_004c0680(int param_1,int param_2)

{
  char cVar1;
  float *pfVar2;
  float10 fVar3;
  undefined1 local_84 [12];
  double local_78;
  double local_70;
  undefined4 local_68;
  undefined4 local_64;
  int local_60;
  int local_5c;
  undefined8 *local_58;
  float local_54;
  float local_50;
  float local_4c;
  float local_48;
  float local_44;
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
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_5c = 0;
  local_58 = (undefined8 *)(param_1 + 0x28);
  local_60 = param_1;
  do {
    if (*(undefined8 **)(local_60 + 0x18028) <= local_58) {
      FUN_0083e885();
      return;
    }
    fVar3 = (float10)FUN_00453f80();
    local_70 = (double)fVar3;
    if (local_70 <= (double)*(float *)(local_58 + 5) + *(double *)(param_2 + 0x98)) {
      fVar3 = (float10)FUN_00453f80();
      local_78 = (double)fVar3;
      if (local_78 <= (double)*(float *)(local_58 + 5) + *(double *)(param_2 + 0x98)) {
        pfVar2 = (float *)FUN_006897e0(local_84,param_2,*local_58,
                                       (double)*(float *)(local_58 + 5) + (double)local_58[1],
                                       local_58[2]);
        local_54 = *pfVar2;
        local_50 = pfVar2[1];
        local_4c = pfVar2[2];
        local_3c = *(float *)(local_58 + 5);
        local_48 = local_54;
        local_44 = local_50;
        local_40 = local_4c;
        if (local_4c <= local_3c * 2.0) {
          if (local_5c != 0) goto LAB_004c06a8;
          local_5c = 1;
        }
        cVar1 = FUN_004c0560(param_2,&local_48);
        if (cVar1 != '\0') {
          FUN_0049bf10();
          local_64 = FUN_0083f040();
          local_38 = local_48 - local_3c;
          local_34 = local_44 + local_3c;
          local_30 = local_40;
          local_2c = local_48 + local_3c;
          local_28 = local_44 + local_3c;
          local_24 = local_40;
          local_20 = local_48 + local_3c;
          local_1c = local_44 - local_3c;
          local_18 = local_40;
          local_14 = local_48 - local_3c;
          local_10 = local_44 - local_3c;
          local_c = local_40;
          local_68 = DAT_00920ef4;
          DAT_00920ef4 = local_40 - local_3c;
          FUN_00417990();
          FUN_0068d2f0(param_2,local_64,&local_38,5);
          DAT_00920ef4 = (float)local_68;
        }
      }
    }
LAB_004c06a8:
    local_58 = local_58 + 6;
  } while( true );
}

