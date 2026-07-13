
void __fastcall FUN_004d39f0(int param_1)

{
  undefined4 *puVar1;
  uint uVar2;
  int iVar3;
  
  uVar2 = FUN_004d3490();
  iVar3 = FUN_004d34b0(*(undefined4 *)(param_1 + 0x10));
  if (uVar2 < 5) {
    puVar1 = (undefined4 *)(*(int *)(&DAT_008e863c + uVar2 * 4) + iVar3 * 8);
    *(undefined4 *)(param_1 + 0x110) = *puVar1;
    *(undefined4 *)(param_1 + 0x114) = puVar1[1];
  }
  else {
    *(undefined4 *)(param_1 + 0x110) = 0;
    *(float *)(param_1 + 0x114) = (float)(iVar3 + 1) * -20.0;
  }
  return;
}

