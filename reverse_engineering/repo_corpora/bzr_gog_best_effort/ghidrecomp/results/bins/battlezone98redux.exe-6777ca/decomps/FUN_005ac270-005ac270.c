
void FUN_005ac270(int param_1,int param_2,char param_3)

{
  char cVar1;
  int iVar2;
  float *pfVar3;
  float10 fVar4;
  char local_a8 [44];
  undefined1 local_7c [12];
  undefined1 local_70 [12];
  undefined4 local_64;
  float local_60;
  undefined4 *local_5c;
  float local_58;
  int local_54;
  float local_50;
  float *local_4c;
  int local_48;
  float *local_44;
  undefined1 local_3d;
  int local_3c;
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
  local_54 = (**(code **)(*(int *)(param_1 + 0x18) + 0x2c))();
  local_4c = (float *)(local_54 + 0x44);
  FUN_005b2950((double)*local_4c,(double)*(float *)(local_54 + 0x4c),
               (double)*(float *)(local_54 + 0x50),(double)*(float *)(local_54 + 0x58),local_a8);
  if (local_a8[0] == '\0') {
    local_3d = 0;
    iVar2 = (*(code *)**(undefined4 **)(param_1 + 0x18))();
    local_44 = (float *)(iVar2 + 0x10c);
    local_64 = FUN_0045c4d0();
    while (cVar1 = FUN_00462710(&local_5c), cVar1 != '\0') {
      local_3c = FUN_00462630(*local_5c);
      if ((((local_3c != 0) && (local_3c != param_1)) &&
          ((param_3 != '\0' || (cVar1 = FUN_004db510(local_3c), cVar1 == '\0')))) &&
         ((((iVar2 = (*(code *)**(undefined4 **)(local_3c + 0x18))(), *(int *)(iVar2 + 0x1c) == 1 ||
            (iVar2 = (*(code *)**(undefined4 **)(local_3c + 0x18))(), *(int *)(iVar2 + 0x1c) == 6))
           || (iVar2 = (*(code *)**(undefined4 **)(local_3c + 0x18))(), *(int *)(iVar2 + 0x1c) == 4)
           ) && ((iVar2 = FUN_004624b0(), *(float *)(iVar2 + 4) <= 10.0 &&
                 (cVar1 = FUN_004b9830(), cVar1 == '\0')))))) {
        pfVar3 = (float *)(**(code **)(*(int *)(local_3c + 0x18) + 0xc))();
        local_14 = *pfVar3;
        local_10 = pfVar3[1];
        local_c = pfVar3[2];
        pfVar3 = (float *)FUN_00445260(local_70,&local_14,local_64);
        local_38 = *pfVar3;
        local_34 = pfVar3[1];
        local_30 = pfVar3[2];
        local_14 = local_38;
        local_10 = local_34;
        local_c = local_30;
        if (((*local_44 <= local_38) &&
            ((local_38 < local_44[3] || local_38 == local_44[3] && (local_44[1] <= local_34)))) &&
           ((local_34 < local_44[4] || local_34 == local_44[4] &&
            ((local_44[2] <= local_30 && (local_30 < local_44[5] || local_30 == local_44[5])))))) {
          fVar4 = (float10)FUN_004464c0();
          local_50 = (float)fVar4;
          local_20 = local_50 * 5.0;
          fVar4 = (float10)FUN_004464c0();
          local_58 = (float)fVar4;
          local_1c = local_58 * 5.0;
          fVar4 = (float10)FUN_004464c0();
          local_60 = (float)fVar4;
          local_18 = local_60 * 5.0 + 25.0;
          for (local_48 = param_2; local_48 != 0; local_48 = *(int *)(local_48 + 0x78)) {
            pfVar3 = (float *)FUN_00440210(local_7c,&local_20,local_48 + 0x20);
            local_2c = *pfVar3;
            local_28 = pfVar3[1];
            local_24 = pfVar3[2];
            local_20 = local_2c;
            local_1c = local_28;
            local_18 = local_24;
          }
          FUN_0046fb20(&local_20);
          local_3d = 1;
        }
      }
    }
  }
  FUN_0083e885();
  return;
}

