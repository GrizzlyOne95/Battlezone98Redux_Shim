
void __fastcall FUN_0073dd40(int *param_1)

{
  int iVar1;
  
  FUN_0041f830();
  *(undefined1 *)(param_1 + 0x18) = 0;
  FUN_0041f830();
  *(undefined1 *)((int)param_1 + 0x61) = 0;
  *(undefined1 *)((int)param_1 + 0x62) = 0;
  FUN_00765be0();
  (**(code **)(*param_1 + 0x70))();
  *(undefined1 *)((int)param_1 + 0x21) = 1;
  iVar1 = FUN_0056f900();
  if ((iVar1 == 0) || (*(char *)(iVar1 + 0xb0) == '\0')) {
    *(undefined1 *)((int)param_1 + 0x21) = 1;
    FUN_007464e0(2);
  }
  else {
    FUN_007464e0(4);
  }
  *(bool *)(param_1 + 8) = DAT_009183ec == 0;
  return;
}

