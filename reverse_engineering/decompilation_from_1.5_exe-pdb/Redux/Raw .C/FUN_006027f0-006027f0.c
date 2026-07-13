
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

bool __fastcall FUN_006027f0(int param_1)

{
  char cVar1;
  bool bVar2;
  undefined4 uVar3;
  float10 extraout_ST0;
  float10 fVar4;
  
  if ((*(uint *)(*(int *)(*(int *)(param_1 + 0x10) + 0x230) + 0x114) & 4) == 0) {
    uVar3 = (**(code **)(*(int *)(*(int *)(param_1 + 0x10) + 0x18) + 0xc))();
    cVar1 = FUN_00466d40(uVar3);
    if (cVar1 != '\0') {
      return true;
    }
  }
  FUN_00822d80();
  if (*(float *)(param_1 + 0x84) + _DAT_008e7964 <= (float)extraout_ST0) {
    uVar3 = (**(code **)(*(int *)(*(int *)(param_1 + 0x10) + 0x18) + 0xc))(param_1 + 0x88);
    fVar4 = (float10)FUN_00462010(uVar3);
    bVar2 = (float)fVar4 < 25.0;
    FUN_00602920();
  }
  else {
    bVar2 = false;
  }
  return bVar2;
}

