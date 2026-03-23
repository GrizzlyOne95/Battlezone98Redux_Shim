
void __fastcall FUN_005f86e0(int param_1)

{
  int iVar1;
  undefined4 *puVar2;
  float10 fVar3;
  
  iVar1 = *(int *)(*(int *)(param_1 + 0x10) + 0x230);
  *(undefined4 *)(iVar1 + 0xd0) = 0;
  *(undefined4 *)(iVar1 + 0xc4) = 0;
  *(undefined4 *)(iVar1 + 200) = 0;
  *(undefined4 *)(iVar1 + 0xd4) = 0;
  switch(*(undefined4 *)(param_1 + 8)) {
  case 1:
    FUN_005f81f0();
    break;
  case 2:
  case 0xb:
  case 0xc:
    iVar1 = FUN_00462630(*(undefined4 *)(param_1 + 0x14));
    puVar2 = (undefined4 *)(**(code **)(*(int *)(iVar1 + 0x18) + 0xc))();
    *(undefined4 *)(param_1 + 0x28) = *puVar2;
    *(undefined4 *)(param_1 + 0x2c) = puVar2[1];
    *(undefined4 *)(param_1 + 0x30) = puVar2[2];
    FUN_00601070();
    break;
  case 3:
    FUN_006028d0();
    break;
  case 4:
    FUN_005f84f0();
    break;
  case 5:
    FUN_00605350();
    break;
  case 8:
  case 10:
    fVar3 = (float10)FUN_00822d80();
    *(float *)(param_1 + 0x100) = (float)fVar3;
  }
  return;
}

