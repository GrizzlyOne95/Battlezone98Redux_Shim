
void __thiscall FUN_004c0c40(int param_1,undefined4 param_2)

{
  int iVar1;
  
  *(undefined4 *)(param_1 + 0x28) = param_2;
  iVar1 = FUN_0043ac70("gquak01.wav",0);
  if (iVar1 != 0) {
    FUN_0043ae50(iVar1,(int)(*(float *)(param_1 + 0x28) * 10.0),0xfffffffe,0xfffffffe);
  }
  return;
}

