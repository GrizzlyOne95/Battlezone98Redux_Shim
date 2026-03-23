
void FUN_005ec4c0(int *param_1)

{
  char cVar1;
  float *pfVar2;
  int iVar3;
  undefined4 uVar4;
  float10 fVar5;
  undefined1 local_5c [44];
  undefined4 *local_30;
  float local_2c;
  float local_28;
  int *local_24;
  float local_20;
  int *local_1c;
  int *local_18;
  float local_14;
  float local_10;
  float local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  pfVar2 = (float *)(**(code **)(param_1[6] + 0xc))();
  local_14 = *pfVar2;
  local_10 = pfVar2[1];
  local_c = pfVar2[2];
  local_20 = 30.0;
  FUN_005b28e0((double)local_14,(double)local_c,0x403e000000000000,local_5c);
  local_24 = (int *)0x0;
  local_2c = local_20 * local_20;
  while (cVar1 = FUN_00462710(&local_30), cVar1 != '\0') {
    local_18 = (int *)FUN_00462630(*local_30);
    if (local_18 != (int *)0x0) {
      for (local_1c = param_1; (local_1c != (int *)0x0 && (local_18 != local_1c));
          local_1c = (int *)local_1c[0x28]) {
      }
      if ((((local_1c == (int *)0x0) && (iVar3 = (**(code **)(*local_18 + 0x28))(), iVar3 != 0)) &&
          (cVar1 = FUN_0045bbc0(), cVar1 == '\0')) && (iVar3 = FUN_0045bdf0(), iVar3 == 0)) {
        uVar4 = (**(code **)(local_18[6] + 0xc))();
        (**(code **)(param_1[6] + 0xc))(uVar4);
        fVar5 = (float10)FUN_00462010();
        local_28 = (float)fVar5;
        if (local_28 <= local_2c) {
          local_24 = local_18;
          local_2c = local_28;
        }
      }
    }
  }
  if (local_24 != (int *)0x0) {
    FUN_005ed4b0(local_24);
  }
  FUN_0083e885();
  return;
}

