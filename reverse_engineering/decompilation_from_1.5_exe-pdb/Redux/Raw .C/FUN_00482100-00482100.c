
void __thiscall FUN_00482100(int param_1,undefined4 param_2)

{
  char cVar1;
  int iVar2;
  undefined4 *puVar3;
  float10 fVar4;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  if ((*(uint *)(*(int *)(param_1 + 0x228) + 0x114) & 4) == 0) {
    iVar2 = FUN_00417c70();
    if (iVar2 != 0) {
      cVar1 = FUN_004db510(iVar2);
      if (cVar1 != '\0') {
        iVar2 = FUN_00462610();
        if (iVar2 == param_1) {
          puVar3 = (undefined4 *)FUN_00462490();
          local_14 = *puVar3;
          local_10 = puVar3[1];
          local_c = puVar3[2];
          fVar4 = (float10)FUN_004428b0(&local_14,*(int *)(param_1 + 0xf4) + 0x20);
          fVar4 = (float10)FUN_00447ed0((float)fVar4 * -5.0,0xbf800000,0x3f800000);
          *(float *)(*(int *)(param_1 + 0x228) + 0xc4) = (float)fVar4;
          goto LAB_00482208;
        }
      }
    }
    *(float *)(*(int *)(param_1 + 0x228) + 0xc4) =
         *(float *)(*(int *)(param_1 + 0xf8) + 0x170) * 0.1;
  }
LAB_00482208:
  FUN_005a7d70(param_2);
  FUN_0083e885();
  return;
}

