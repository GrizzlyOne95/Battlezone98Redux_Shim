
void __fastcall FUN_005b2bd0(int param_1)

{
  int iVar1;
  int iVar2;
  undefined4 local_c;
  
  *(undefined4 *)(param_1 + 0x2c) = 0;
  iVar1 = *(int *)(param_1 + 0x24);
  iVar2 = *(int *)(param_1 + 0x28);
  for (local_c = 0; local_c < iVar1 * iVar2; local_c = local_c + 1) {
    *(undefined4 *)(*(int *)(param_1 + 0x34) + local_c * 4) = 0xffffffff;
  }
  *(undefined4 *)(param_1 + 0x38) = 0;
  return;
}

