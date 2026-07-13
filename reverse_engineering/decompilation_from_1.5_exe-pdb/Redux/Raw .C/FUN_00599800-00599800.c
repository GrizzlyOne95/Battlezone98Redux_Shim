
void __thiscall FUN_00599800(int *param_1,int *param_2)

{
  char cVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  int *piVar4;
  int iVar5;
  float10 fVar6;
  undefined1 local_48 [4];
  undefined1 local_44 [4];
  undefined1 local_40 [4];
  float local_3c;
  float local_38;
  undefined4 local_34;
  float local_30;
  float local_2c;
  int *local_28;
  float local_24;
  undefined4 local_20;
  float *local_1c;
  int local_18;
  float local_14 [3];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_14[0] = 0.0;
  local_14[1] = 0.0;
  local_14[2] = 0.0;
  local_28 = param_1;
  (**(code **)(*param_1 + 0x28))(DAT_009175a0,DAT_009175a4,local_14,local_14 + 2);
  local_3c = 2.0 / (float)local_28[0x10];
  local_30 = 3.4028235e+38;
  *param_2 = 0;
  local_34 = DAT_00917a74;
  FUN_00422170();
  puVar2 = (undefined4 *)FID_conflict_begin(local_40);
  local_20 = *puVar2;
  while( true ) {
    uVar3 = FID_conflict_end(local_44);
    cVar1 = FID_conflict_operator__(uVar3);
    if (cVar1 == '\0') break;
    piVar4 = (int *)FUN_00421ec0();
    local_18 = *piVar4;
    iVar5 = (**(code **)(*(int *)(local_18 + 0x18) + 0x2c))();
    if ((iVar5 != 0) && (cVar1 = FUN_0045bbc0(), cVar1 == '\0')) {
      local_1c = (float *)(**(code **)(*(int *)(local_18 + 0x18) + 0xc))();
      local_24 = (*local_1c - local_14[0]) * (*local_1c - local_14[0]) +
                 (local_1c[2] - local_14[2]) * (local_1c[2] - local_14[2]);
      if (local_24 < local_30) {
        iVar5 = FUN_00462400();
        fVar6 = (float10)FUN_00462470(*(undefined4 *)(iVar5 + 0xc));
        fVar6 = (float10)FUN_0044fb20((float)fVar6);
        local_38 = (float)fVar6;
        local_2c = local_38 + local_3c;
        if (local_24 < local_2c * local_2c) {
          local_30 = local_24;
          *param_2 = local_18;
        }
      }
    }
    FUN_0046b260(local_48,0);
  }
  FUN_0083e885();
  return;
}

