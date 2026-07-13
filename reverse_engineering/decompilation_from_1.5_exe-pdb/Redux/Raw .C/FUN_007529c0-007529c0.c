
int __thiscall FUN_007529c0(int param_1,int param_2)

{
  FID_conflict_operator_(param_2);
  *(undefined4 *)(param_1 + 0x18) = *(undefined4 *)(param_2 + 0x18);
  *(undefined4 *)(param_1 + 0x1c) = *(undefined4 *)(param_2 + 0x1c);
  FID_conflict_operator_(param_2 + 0x20);
  *(undefined1 *)(param_1 + 0x38) = *(undefined1 *)(param_2 + 0x38);
  FID_conflict_operator_(param_2 + 0x3c);
  FID_conflict_operator_(param_2 + 0x54);
  FUN_00489eb0(param_2 + 0x6c);
  return param_1;
}

