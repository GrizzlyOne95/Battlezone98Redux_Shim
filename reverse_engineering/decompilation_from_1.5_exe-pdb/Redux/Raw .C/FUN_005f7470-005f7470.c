
bool __fastcall FUN_005f7470(int param_1)

{
  char cVar1;
  bool bVar2;
  undefined4 uVar3;
  float10 extraout_ST0;
  
  cVar1 = (**(code **)(**(int **)(param_1 + 0x34) + 0x68))();
  if (cVar1 == '\0') {
    bVar2 = false;
  }
  else {
    uVar3 = (**(code **)(*(int *)(*(int *)(param_1 + 0x60) + 0x18) + 0xc))();
    uVar3 = (**(code **)(*(int *)(*(int *)(param_1 + 0x34) + 0x18) + 0xc))(uVar3);
    FUN_00462010(uVar3);
    bVar2 = (float)extraout_ST0 < *(float *)(param_1 + 0x6c);
  }
  return bVar2;
}

