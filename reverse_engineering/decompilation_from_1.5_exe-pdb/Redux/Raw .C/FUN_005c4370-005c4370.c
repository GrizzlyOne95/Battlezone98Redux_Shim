
void __fastcall FUN_005c4370(int param_1)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 uVar3;
  undefined1 local_1c;
  
  iVar2 = *(int *)(param_1 + 0x20);
  if (iVar2 == 2) {
    iVar2 = *(int *)(*(int *)(param_1 + 0x28) + 0xb4);
    puVar1 = (undefined4 *)(*(int *)(iVar2 + 8) + -8 + *(int *)(iVar2 + 4) * 8);
    *(undefined4 *)(param_1 + 0x2c) = *puVar1;
    *(undefined4 *)(param_1 + 0x30) = 0xbf800000;
    *(undefined4 *)(param_1 + 0x34) = puVar1[1];
    iVar2 = FUN_004dc010();
    uVar3 = FUN_00477590(iVar2);
    *(undefined4 *)(param_1 + 0x24) = uVar3;
    if ((iVar2 == 0) ||
       (iVar2 = (*(code *)**(undefined4 **)(iVar2 + 0x18))(), *(int *)(iVar2 + 0x1c) != 7)) {
      local_1c = 0;
    }
    else {
      local_1c = 1;
    }
    *(undefined1 *)(param_1 + 0x48) = local_1c;
  }
  else if (iVar2 == 3) {
    uVar3 = FUN_004dc010();
    uVar3 = FUN_00477590(uVar3);
    *(undefined4 *)(param_1 + 0x24) = uVar3;
  }
  else if (iVar2 == 6) {
    uVar3 = FUN_004dc010();
    uVar3 = FUN_00477590(uVar3);
    *(undefined4 *)(param_1 + 0x24) = uVar3;
  }
  return;
}

