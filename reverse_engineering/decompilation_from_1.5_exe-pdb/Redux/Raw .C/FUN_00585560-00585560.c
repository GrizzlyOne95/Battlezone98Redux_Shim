
void __fastcall FUN_00585560(int param_1)

{
  undefined4 uVar1;
  undefined1 local_14 [4];
  undefined4 local_10;
  int local_c;
  int local_8;
  
  local_8 = param_1;
  if (*(int *)(param_1 + 0x74) != 0) {
    FUN_0044dc60(*(int *)(param_1 + 0x14) + 0x20,0);
  }
  FUN_0062d4b0(*(undefined4 *)(local_8 + 0x14));
  FUN_0062d410(*(undefined4 *)(local_8 + 0x14),*(undefined4 *)(*(int *)(local_8 + 0xc) + 0x38));
  if (*(int *)(local_8 + 0xd8) != 0) {
    uVar1 = FUN_0062d370(*(undefined4 *)(local_8 + 0xd8),*(int *)(local_8 + 0xc) + 0x20);
    *(undefined4 *)(local_8 + 0xd8) = uVar1;
    if (*(int *)(local_8 + 0xd8) != 0) {
      FUN_0062d310(*(undefined4 *)(local_8 + 0xd8),*(int *)(local_8 + 0xc) + 0x20);
    }
  }
  local_10 = *(undefined4 *)(local_8 + 8);
  FUN_0042d920(local_14,local_10);
  FUN_00680620(local_8);
  while( true ) {
    local_c = FUN_0043ac70(0,*(undefined4 *)(local_8 + 0x14));
    *(int *)(local_8 + 0x70) = local_c;
    if (local_c == 0) break;
    FUN_0043aaa0(*(undefined4 *)(local_8 + 0x70));
  }
  return;
}

