
void __fastcall FUN_00595c60(int *param_1)

{
  char cVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  int *piVar4;
  int iVar5;
  float10 fVar6;
  undefined1 local_50 [4];
  undefined1 local_4c [4];
  undefined1 local_48 [4];
  float local_44;
  float local_40;
  float local_3c;
  undefined4 local_38;
  float local_34;
  undefined4 local_30;
  uint local_2c;
  undefined4 local_28;
  float *local_24;
  int *local_20;
  int local_1c;
  char local_15;
  float local_14 [3];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_14[0] = 0.0;
  local_14[1] = 0.0;
  local_14[2] = 0.0;
  local_20 = param_1;
  (**(code **)(*param_1 + 0x28))(DAT_009175a0,DAT_009175a4,local_14,local_14 + 2);
  local_40 = 2.0 / (float)local_20[0x10];
  local_38 = DAT_00917a74;
  FUN_00422170();
  puVar2 = (undefined4 *)FID_conflict_begin(local_50);
  local_28 = *puVar2;
  while( true ) {
    uVar3 = FID_conflict_end(local_4c);
    cVar1 = FID_conflict_operator__(uVar3);
    if (cVar1 == '\0') break;
    piVar4 = (int *)FUN_00421ec0();
    local_1c = *piVar4;
    iVar5 = (**(code **)(*(int *)(local_1c + 0x18) + 0x2c))();
    if ((iVar5 != 0) && (cVar1 = FUN_0045bbc0(), cVar1 == '\0')) {
      local_15 = '\0';
      if ((local_20[0x1d] == 3) || ((local_20[0x1d] == 2 && (iVar5 = FUN_0045bdf0(), iVar5 != 0))))
      {
        local_24 = (float *)(**(code **)(*(int *)(local_1c + 0x18) + 0xc))();
        iVar5 = FUN_00462400();
        fVar6 = (float10)FUN_00462470(*(undefined4 *)(iVar5 + 0xc));
        fVar6 = (float10)FUN_0044fb20((float)fVar6);
        local_44 = (float)fVar6;
        local_34 = local_44 + local_40;
        local_3c = (*local_24 - local_14[0]) * (*local_24 - local_14[0]) +
                   (local_24[2] - local_14[2]) * (local_24[2] - local_14[2]);
        local_15 = local_3c < local_34 * local_34;
        local_2c = (uint)(byte)local_15;
      }
      if (local_15 == '\0') {
        local_30 = DAT_00917584;
      }
      else {
        local_30 = DAT_00917570;
      }
      FUN_00595460(local_1c,local_15,local_30);
    }
    FUN_0046b260(local_48,0);
  }
  FUN_0083e885();
  return;
}

