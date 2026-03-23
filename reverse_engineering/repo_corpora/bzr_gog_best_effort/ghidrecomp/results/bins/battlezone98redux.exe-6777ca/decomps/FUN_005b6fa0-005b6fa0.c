
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

bool __fastcall FUN_005b6fa0(int param_1)

{
  char cVar1;
  bool bVar2;
  undefined4 uVar3;
  float10 extraout_ST0;
  float10 fVar4;
  
  uVar3 = (**(code **)(*(int *)(*(int *)(param_1 + 0x2c) + 0x18) + 0xc))();
  cVar1 = FUN_00466d40(uVar3);
  if (cVar1 == '\0') {
    FUN_00822da0();
    if (*(float *)(param_1 + 0x18) + _DAT_008e7964 <= (float)extraout_ST0) {
      uVar3 = (**(code **)(*(int *)(*(int *)(param_1 + 0x2c) + 0x18) + 0xc))(param_1 + 0x1c);
      fVar4 = (float10)FUN_00462010(uVar3);
      bVar2 = (float)fVar4 < 25.0;
      FUN_005b7080();
    }
    else {
      bVar2 = false;
    }
  }
  else {
    bVar2 = true;
  }
  return bVar2;
}

