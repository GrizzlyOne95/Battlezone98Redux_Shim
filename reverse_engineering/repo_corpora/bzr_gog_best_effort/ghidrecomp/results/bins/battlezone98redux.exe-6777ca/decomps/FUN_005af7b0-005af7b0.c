
void __fastcall FUN_005af7b0(int param_1)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  float *pfVar4;
  int *piVar5;
  undefined1 local_6c [12];
  undefined1 local_60 [12];
  undefined1 local_54 [4];
  undefined1 local_50 [4];
  undefined1 local_4c [4];
  undefined *local_48;
  int local_44;
  undefined4 local_40;
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
  local_3c = param_1;
  if (*(char *)(param_1 + 0x309) != '\0') {
    uVar2 = FUN_00462630(*(undefined4 *)(param_1 + 0x30c));
    *(undefined4 *)(local_3c + 0x310) = uVar2;
    if (*(int *)(local_3c + 0x310) != 0) {
      puVar3 = (undefined4 *)
               (**(code **)(*(int *)(*(int *)(local_3c + 0x310) + 0x18) + 0xc))
                         (*(undefined4 *)(local_3c + 0x108),*(undefined4 *)(local_3c + 0x10c),
                          *(undefined4 *)(local_3c + 0x110));
      pfVar4 = (float *)FUN_004401a0(local_60,*puVar3,puVar3[1],puVar3[2]);
      local_38 = *pfVar4;
      local_34 = pfVar4[1];
      local_30 = pfVar4[2];
      local_20 = local_38;
      local_1c = local_34;
      local_18 = local_30;
      if (local_38 * local_38 + local_30 * local_30 <= 100.0) goto LAB_005afa02;
      FUN_007d6a70("powerSource is too far\n");
      *(undefined1 *)(*(int *)(local_3c + 0x310) + 0x239) = 0;
    }
    *(undefined4 *)(local_3c + 0x30c) = 0;
    local_48 = &DAT_009b63fc;
    FUN_00422170();
    puVar3 = (undefined4 *)FID_conflict_begin(local_50);
    local_40 = *puVar3;
    while( true ) {
      uVar2 = FID_conflict_end(local_4c);
      cVar1 = FID_conflict_operator__(uVar2);
      if (cVar1 == '\0') break;
      piVar5 = (int *)FUN_00421ec0();
      local_44 = *piVar5;
      if (*(char *)(local_44 + 0x239) == '\0') {
        puVar3 = (undefined4 *)
                 (**(code **)(*(int *)(local_44 + 0x18) + 0xc))
                           (*(undefined4 *)(local_3c + 0x108),*(undefined4 *)(local_3c + 0x10c),
                            *(undefined4 *)(local_3c + 0x110));
        pfVar4 = (float *)FUN_004401a0(local_6c,*puVar3,puVar3[1],puVar3[2]);
        local_2c = *pfVar4;
        local_28 = pfVar4[1];
        local_24 = pfVar4[2];
        local_14 = local_2c;
        local_10 = local_28;
        local_c = local_24;
        if (local_2c * local_2c + local_24 * local_24 < 100.0) {
          *(int *)(local_3c + 0x310) = local_44;
          goto LAB_005afa02;
        }
      }
      FUN_0046b260(local_54,0);
    }
    *(undefined4 *)(local_3c + 0x310) = 0;
  }
LAB_005afa02:
  FUN_0083e885();
  return;
}

