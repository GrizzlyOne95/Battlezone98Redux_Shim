
void __fastcall FUN_004f3890(int param_1)

{
  float10 fVar1;
  
  fVar1 = (float10)FUN_00822da0();
  if (*(float *)(param_1 + 0xfc) <= (float)fVar1) {
    *(undefined4 *)(param_1 + 0xfc) = 0x7149f2ca;
  }
  else {
    *(undefined4 *)(param_1 + 0xfc) = 0;
  }
  return;
}

