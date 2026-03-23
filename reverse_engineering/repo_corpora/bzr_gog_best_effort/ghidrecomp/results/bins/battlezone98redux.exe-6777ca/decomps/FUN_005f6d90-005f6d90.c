
bool __fastcall FUN_005f6d90(int param_1)

{
  char cVar1;
  
  *(undefined4 *)(param_1 + 0x70) = 0x3f800000;
  *(undefined4 *)(param_1 + 0x6c) = 0;
  *(undefined4 *)(param_1 + 0x6c) = 0x43160000;
  *(undefined4 *)(param_1 + 0x74) = 0;
  FUN_00466be0(*(undefined4 *)(param_1 + 0x34),param_1 + 0x68,param_1 + 0x6c,param_1 + 0x70,
               param_1 + 0x74);
  *(float *)(param_1 + 0x78) = *(float *)(param_1 + 0x6c) / *(float *)(param_1 + 0x70);
  *(float *)(param_1 + 0x7c) = *(float *)(param_1 + 0x70) / *(float *)(param_1 + 0x6c);
  *(float *)(param_1 + 0x68) = *(float *)(param_1 + 0x68) * *(float *)(param_1 + 0x68);
  *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) * *(float *)(param_1 + 0x6c);
  cVar1 = FUN_005f9a30();
  return cVar1 != '\0';
}

