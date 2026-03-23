
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0061a140(int param_1)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 *puVar3;
  float10 fVar4;
  undefined1 local_5a4 [472];
  undefined1 local_3cc [472];
  undefined1 local_1f4 [472];
  float local_1c;
  int local_18;
  undefined4 local_14;
  int local_10;
  undefined4 *local_c;
  undefined4 *local_8;
  
  _DAT_008ead68 = 1;
  local_14 = FUN_00417780(&DAT_02cecee0);
  if (param_1 == 1) {
    fVar4 = (float10)FUN_0067dcf0(0x3f800000);
    local_1c = (float)fVar4;
    fVar4 = (float10)FUN_0061a130(local_1c * _DAT_008ead08);
    puVar1 = (undefined4 *)FUN_00688370(local_1f4,local_14,0x3fb2b8c2,(float)fVar4);
    puVar3 = &DAT_008eaae0;
    for (iVar2 = 0x76; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar3 = *puVar1;
      puVar1 = puVar1 + 1;
      puVar3 = puVar3 + 1;
    }
  }
  else {
    local_c = &DAT_008eaae0;
    fVar4 = (float10)FUN_0061a130(DAT_008eaaf0,DAT_008eab10);
    puVar1 = (undefined4 *)FUN_00688370(local_3cc,local_14,local_c[9],(float)fVar4);
    puVar3 = local_c;
    for (iVar2 = 0x76; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar3 = *puVar1;
      puVar1 = puVar1 + 1;
      puVar3 = puVar3 + 1;
    }
  }
  for (local_10 = DAT_008ead14; local_10 < 8; local_10 = local_10 + 1) {
    iVar2 = local_10 * 0x238;
    local_8 = (undefined4 *)(&DAT_02cebcf0 + iVar2);
    puVar1 = (undefined4 *)
             FUN_00688370(local_5a4,local_14,*(undefined4 *)(iVar2 + 0x2cebd14),
                          *(undefined4 *)(iVar2 + 0x2cebd1c),*(undefined4 *)(iVar2 + 0x2cebd00),
                          *(undefined4 *)(iVar2 + 0x2cebd20));
    puVar3 = local_8;
    for (iVar2 = 0x76; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar3 = *puVar1;
      puVar1 = puVar1 + 1;
      puVar3 = puVar3 + 1;
    }
  }
  if (param_1 == 1) {
    DAT_008eacb8 = 0;
    DAT_008eaad4 = 1;
    DAT_008eaad8 = 0;
    DAT_008eacbc = 0x3f060a92;
    DAT_008eacc0 = 0x3f060a92;
    DAT_008eacc4 = 0;
    DAT_008eacc8 = 0;
    DAT_008eacd4 = 0x41a00000;
    DAT_008eacd8 = 0x41a00000;
    DAT_008eaad0 = 0;
    local_18 = FUN_0062c840();
    if (local_18 != 0) {
      FUN_0061d120(local_18,1);
    }
    DAT_008ead10 = 0x3f800000;
  }
  return;
}

