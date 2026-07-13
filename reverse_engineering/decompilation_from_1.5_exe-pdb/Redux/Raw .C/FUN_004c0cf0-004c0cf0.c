
void __thiscall FUN_004c0cf0(int param_1,float param_2)

{
  char cVar1;
  undefined4 *puVar2;
  int iVar3;
  float10 fVar4;
  undefined1 local_94 [20];
  undefined1 local_80 [4];
  float local_7c;
  float local_78;
  float local_74;
  float local_70;
  float local_6c;
  float local_68;
  float local_64;
  float local_60;
  float local_5c;
  undefined *local_58;
  float local_54;
  undefined4 *local_50;
  int local_4c;
  undefined4 local_48;
  undefined4 local_44;
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
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_4c = param_1;
  if (0.0 < *(float *)(param_1 + 0x28)) {
    local_58 = &DAT_0094e2d4;
    FUN_00422170();
    puVar2 = (undefined4 *)FID_conflict_begin();
    local_44 = *puVar2;
    while( true ) {
      FID_conflict_end();
      cVar1 = FID_conflict_operator__();
      if (cVar1 == '\0') break;
      puVar2 = (undefined4 *)FUN_00421ec0();
      local_48 = *puVar2;
      FUN_004c0af0();
      fVar4 = (float10)FUN_007855e0((double)local_20,(double)local_18);
      local_70 = (float)fVar4;
      local_54 = local_1c - local_70;
      local_3c = (param_2 * *(float *)(local_4c + 0x28)) / (local_54 * 0.5 * local_54 + 1.0);
      local_74 = 2.0;
      fVar4 = (float10)FUN_00822d80();
      local_6c = (float)fVar4;
      local_40 = local_6c * local_74;
      fVar4 = (float10)FUN_00822970();
      local_7c = (float)fVar4;
      local_38 = local_7c * local_3c * 1.0;
      fVar4 = (float10)FUN_00822970();
      local_5c = (float)fVar4;
      local_34 = local_5c * local_3c * 0.3;
      fVar4 = (float10)FUN_00822970();
      local_64 = (float)fVar4;
      local_30 = local_64 * local_3c * 1.0;
      iVar3 = FUN_0045c490();
      local_50 = (undefined4 *)(iVar3 + 0x24);
      puVar2 = (undefined4 *)
               FUN_00440130(local_94,*local_50,*(undefined4 *)(iVar3 + 0x28),
                            *(undefined4 *)(iVar3 + 0x2c),local_38,local_34,local_30);
      local_14 = *puVar2;
      local_10 = puVar2[1];
      local_c = puVar2[2];
      *local_50 = local_14;
      local_50[1] = local_10;
      local_50[2] = local_c;
      fVar4 = (float10)FUN_00822970();
      local_68 = (float)fVar4;
      local_2c = local_68 * local_3c * 5.0;
      fVar4 = (float10)FUN_00822970();
      local_78 = (float)fVar4;
      local_28 = local_78 * local_3c * 2.0;
      fVar4 = (float10)FUN_00822970();
      local_60 = (float)fVar4;
      local_24 = local_60 * local_3c * 5.0;
      FUN_004a75b0();
      FUN_0046b260(local_80,0);
    }
  }
  FUN_0083e885();
  return;
}

