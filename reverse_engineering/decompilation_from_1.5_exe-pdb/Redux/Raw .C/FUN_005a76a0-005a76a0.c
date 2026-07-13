
void __thiscall FUN_005a76a0(int param_1,undefined4 param_2)

{
  int iVar1;
  float10 fVar2;
  int *local_c;
  int local_8;
  
  local_8 = param_1;
  if (-1 < *(int *)(param_1 + 0x238)) {
    iVar1 = FUN_0062a540(*(undefined4 *)(param_1 + 0x238),&local_c);
    if ((iVar1 != 0) || (*local_c != 1)) {
      FUN_0062a5d0(*(undefined4 *)(local_8 + 0x238));
      *(undefined4 *)(local_8 + 0x238) = 0xffffffff;
      iVar1 = *(int *)(local_8 + 0xf0);
      fVar2 = (float10)FUN_0062e590(*(undefined4 *)(local_8 + 0xf4),*(undefined4 *)(iVar1 + 8),
                                    *(undefined4 *)(iVar1 + 0xc),*(undefined4 *)(iVar1 + 0x10));
      *(float *)(*(int *)(local_8 + 0xf0) + 0x14) = (float)fVar2;
      FUN_004db100();
    }
  }
  FUN_0047fcb0(param_2);
  return;
}

