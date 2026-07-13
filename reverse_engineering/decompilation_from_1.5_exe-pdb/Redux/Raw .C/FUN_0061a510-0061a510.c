
void FUN_0061a510(void)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  float10 fVar5;
  undefined1 local_e8 [64];
  undefined1 local_a8 [64];
  float local_68;
  undefined4 local_64;
  float local_60;
  float local_5c;
  float local_58;
  int local_54;
  int *local_50;
  int *local_4c;
  undefined4 local_48 [16];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_64 = FUN_00439e60();
  fVar5 = (float10)FUN_00822d60();
  local_68 = (float)fVar5;
  local_4c = (int *)FUN_00439e70();
  if (((local_4c != (int *)0x0) && (*local_4c != 0)) && (iVar1 = FUN_0062c840(), iVar1 != 0)) {
    if (local_4c != DAT_0091842c) {
      DAT_0091842c = local_4c;
      if (DAT_008ead0c == 0) {
        if (DAT_008eaab0 == 0) {
          FUN_0061ab00(local_4c);
        }
        else {
          FUN_0061a940(local_4c);
        }
      }
      else {
        FUN_0061a780(local_4c);
      }
    }
    local_54 = FUN_0045c4f0(*local_4c);
    if (((local_54 != 0) && (local_50 = *(int **)(local_54 + 0xfc), local_50 != (int *)0x0)) &&
       (*local_50 != 0)) {
      if (local_4c[0x38] == 0) {
        puVar2 = (undefined4 *)FUN_0062e070(local_a8,local_50,0);
        puVar4 = local_48;
        for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
          *puVar4 = *puVar2;
          puVar2 = puVar2 + 1;
          puVar4 = puVar4 + 1;
        }
      }
      else {
        puVar2 = (undefined4 *)FUN_0067dac0(local_e8,local_4c);
        puVar4 = local_48;
        for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
          *puVar4 = *puVar2;
          puVar2 = puVar2 + 1;
          puVar4 = puVar4 + 1;
        }
      }
      FUN_00689090(local_64,local_48);
      if (DAT_009198f2 == '\0') {
        if (DAT_009198f0 == '\0') {
          if (DAT_009198f1 != '\0') {
            fVar5 = (float10)FUN_00822d60();
            local_58 = (float)fVar5;
            DAT_008ead10 = DAT_008ead10 - local_58 * 0.5 * DAT_008ead10;
            if (DAT_008ead10 < 0.99) {
              DAT_008ead10 = 0.99;
            }
          }
        }
        else {
          fVar5 = (float10)FUN_00822d60();
          local_60 = (float)fVar5;
          DAT_008ead10 = local_60 * 0.5 * DAT_008ead10 + DAT_008ead10;
          if (1.6 < DAT_008ead10) {
            DAT_008ead10 = 1.6;
          }
        }
      }
      else {
        DAT_008ead10 = 1.0;
      }
      uVar3 = FUN_00439e60();
      fVar5 = (float10)FUN_00619ff0(uVar3);
      local_5c = (float)fVar5;
      if (local_5c != DAT_008ead10) {
        uVar3 = FUN_00439e60(DAT_008ead10);
        FUN_006885c0(uVar3);
      }
    }
  }
  FUN_0083e885();
  return;
}

