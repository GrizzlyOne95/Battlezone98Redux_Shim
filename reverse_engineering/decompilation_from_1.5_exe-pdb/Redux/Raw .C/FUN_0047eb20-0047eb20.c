
undefined1 __thiscall FUN_0047eb20(int param_1,undefined4 param_2)

{
  char cVar1;
  bool bVar2;
  undefined1 local_14;
  
  bVar2 = true;
  if (DAT_009173b7 == '\0') {
    cVar1 = FUN_004ce5e0(param_2,param_1 + 0x234,1);
    bVar2 = cVar1 != '\0';
  }
  else {
    *(undefined1 *)(param_1 + 0x234) = 0;
  }
  if ((bVar2) && (cVar1 = FUN_004dd370(param_2), cVar1 != '\0')) {
    local_14 = 1;
  }
  else {
    local_14 = 0;
  }
  FUN_004db100();
  if (*(float *)(param_1 + 0x200) <= 0.0 && *(float *)(param_1 + 0x200) != 0.0) {
    FUN_0062de40(*(undefined4 *)(param_1 + 0xf4),&DAT_01000200);
  }
  return local_14;
}

