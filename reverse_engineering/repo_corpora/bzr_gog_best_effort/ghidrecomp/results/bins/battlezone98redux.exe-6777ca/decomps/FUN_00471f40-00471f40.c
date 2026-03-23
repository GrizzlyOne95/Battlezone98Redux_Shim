
void __fastcall FUN_00471f40(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  
  iVar1 = *(int *)(*(int *)(param_1 + 0x10) + 0x230);
  *(undefined4 *)(iVar1 + 0xd0) = 0;
  *(undefined4 *)(iVar1 + 0xc4) = 0;
  *(undefined4 *)(iVar1 + 200) = 0;
  *(undefined4 *)(iVar1 + 0xd4) = 0;
  iVar1 = *(int *)(param_1 + 8);
  if (iVar1 == 1) {
    uVar2 = FUN_00462630(*(undefined4 *)(param_1 + 0x14));
    *(undefined4 *)(param_1 + 0x18) = uVar2;
    if ((*(int *)(param_1 + 0x18) == 0) || (*(int *)(*(int *)(param_1 + 0x10) + 0x300) == 0)) {
      *(undefined4 *)(param_1 + 8) = 0xd;
    }
    else {
      *(undefined4 *)(param_1 + 8) = 2;
      puVar3 = (undefined4 *)(**(code **)(*(int *)(*(int *)(param_1 + 0x18) + 0x18) + 0xc))();
      *(undefined4 *)(param_1 + 0x28) = *puVar3;
      *(undefined4 *)(param_1 + 0x2c) = puVar3[1];
      *(undefined4 *)(param_1 + 0x30) = puVar3[2];
      FUN_00601070();
    }
  }
  else if (iVar1 == 2) {
    FUN_00601070();
  }
  else if (iVar1 == 3) {
    FUN_006028d0();
  }
  return;
}

