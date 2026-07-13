
void __fastcall FUN_005d0cc0(int param_1)

{
  int iVar1;
  undefined4 local_c;
  
  iVar1 = *(int *)(param_1 + 0x238);
  if ((*(uint *)(*(int *)(param_1 + 0xf4) + 0x14) & 0x200) == 0) {
    local_c = FUN_005ca740(param_1 + 0x108,*(undefined4 *)(param_1 + 0x174),
                           *(undefined4 *)(param_1 + 0x238));
  }
  else {
    local_c = 0;
  }
  *(undefined4 *)(param_1 + 0x238) = local_c;
  if ((*(int *)(param_1 + 0x238) == 0) || (iVar1 != 0)) {
    if ((*(int *)(param_1 + 0x238) == 0) && (iVar1 != 0)) {
      FUN_005ca980(*(undefined4 *)(param_1 + 0xf4));
    }
  }
  else {
    FUN_005ca920(*(undefined4 *)(param_1 + 0xf4));
  }
  return;
}

