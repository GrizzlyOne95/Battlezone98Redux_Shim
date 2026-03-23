
void __fastcall FUN_0060a240(int param_1)

{
  char cVar1;
  float10 fVar2;
  undefined1 local_24 [4];
  undefined1 local_20 [4];
  undefined4 local_1c;
  undefined4 local_18;
  uint local_14;
  undefined4 local_10;
  int local_c;
  int local_8;
  
  *(undefined4 *)(param_1 + 0x74) = 0;
  local_8 = param_1;
  local_10 = FUN_00417ca0();
  local_14 = FUN_00417f90();
  for (local_c = 0; local_c < 5; local_c = local_c + 1) {
    if ((1 << ((byte)local_c & 0x1f) & local_14) != 0) {
      local_18 = FUN_00417f60(local_c);
      cVar1 = FUN_00466890(local_18,local_24,&local_1c,local_20);
      if (cVar1 != '\0') {
        fVar2 = (float10)FUN_0044fb20(*(undefined4 *)(local_8 + 0x74),local_1c);
        *(float *)(local_8 + 0x74) = (float)fVar2;
      }
    }
  }
  fVar2 = (float10)FUN_00456080(*(undefined4 *)(local_8 + 0x74),0x43fa0000);
  *(float *)(local_8 + 0x74) = (float)fVar2;
  return;
}

