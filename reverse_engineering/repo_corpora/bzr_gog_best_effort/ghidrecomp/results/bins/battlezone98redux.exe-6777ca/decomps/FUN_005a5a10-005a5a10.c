
void __fastcall FUN_005a5a10(int param_1)

{
  int iVar1;
  undefined4 *puVar2;
  int *piVar3;
  undefined4 uVar4;
  float10 fVar5;
  float local_1c;
  
  iVar1 = *(int *)(*(int *)(param_1 + 0x10) + 0x230);
  *(undefined4 *)(iVar1 + 0xd0) = 0;
  *(undefined4 *)(iVar1 + 0xc4) = 0;
  *(undefined4 *)(iVar1 + 200) = 0;
  *(undefined4 *)(iVar1 + 0xd4) = 0;
  switch(*(undefined4 *)(param_1 + 8)) {
  case 1:
    *(undefined4 *)(param_1 + 0xc) = 4;
    break;
  case 2:
    iVar1 = FUN_00462630(*(undefined4 *)(param_1 + 0x14));
    if (iVar1 == 0) {
      *(undefined4 *)(param_1 + 0xc) = 0xd;
    }
    else {
      puVar2 = (undefined4 *)(**(code **)(*(int *)(iVar1 + 0x18) + 0xc))();
      *(undefined4 *)(param_1 + 0x28) = *puVar2;
      *(undefined4 *)(param_1 + 0x2c) = puVar2[1];
      *(undefined4 *)(param_1 + 0x30) = puVar2[2];
      FUN_00601070();
    }
    break;
  case 3:
    FUN_006028d0();
    break;
  case 4:
    piVar3 = (int *)FUN_00477980(*(undefined4 *)(param_1 + 0x10));
    local_1c = 1e+30;
    if (piVar3 != (int *)0x0) {
      uVar4 = (**(code **)(*(int *)(*piVar3 + 0x18) + 0xc))();
      uVar4 = (**(code **)(*(int *)(*(int *)(param_1 + 0x10) + 0x18) + 0xc))(uVar4);
      fVar5 = (float10)FUN_00462010(uVar4);
      local_1c = (float)fVar5;
    }
    if (local_1c <= 900.0) {
      *(undefined4 *)(param_1 + 0x110) = 0;
      *(undefined4 *)(param_1 + 0x114) = 0xc1200000;
    }
    else {
      *(undefined4 *)(param_1 + 0xc) = 2;
    }
  }
  return;
}

