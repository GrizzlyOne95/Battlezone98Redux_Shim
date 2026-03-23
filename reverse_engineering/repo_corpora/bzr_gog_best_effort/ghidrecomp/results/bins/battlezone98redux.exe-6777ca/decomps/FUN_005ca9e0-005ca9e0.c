
void FUN_005ca9e0(uint param_1)

{
  uint uVar1;
  int *piVar2;
  undefined *puVar3;
  
  puVar3 = &DAT_025cf554;
  while( true ) {
    uVar1 = size();
    if (uVar1 <= param_1) break;
    piVar2 = (int *)FUN_004e0020();
    (**(code **)(*(int *)(*piVar2 + 0x18) + 0x10))(*piVar2,puVar3);
  }
  return;
}

