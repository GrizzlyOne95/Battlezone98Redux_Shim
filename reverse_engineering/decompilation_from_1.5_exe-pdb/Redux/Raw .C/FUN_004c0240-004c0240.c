
void __fastcall FUN_004c0240(int param_1)

{
  uint uVar1;
  undefined4 uVar2;
  undefined1 local_24 [16];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00849508;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  *(int *)(param_1 + 0x18028) = param_1 + 0x28;
  local_14 = uVar1;
  FUN_00589430("dust.odf");
  local_8 = 0;
  FUN_0047b6c0(0xc8e4c134,0xc1fe0e54,local_24,"dust.0");
  uVar2 = FUN_0068bed0(local_24,uVar1);
  *(undefined4 *)(param_1 + 0x1802c) = uVar2;
  FUN_00589760(0xc8e4c134,0x2e9fa32f,param_1 + 0x18030,0x20);
  FUN_00589800(0xc8e4c134,0xfeb0cc2b,param_1 + 0x18034,0x3f99999a);
  *(float *)(param_1 + 0x18034) = (float)*(int *)(param_1 + 0x18030) / *(float *)(param_1 + 0x18034)
  ;
  FUN_00589800(0xc8e4c134,0x922db093,param_1 + 0x18038,0x3fc00000);
  FUN_00589800(0xc8e4c134,0x7bb4f7d1,param_1 + 0x1803c,0x3f800000);
  *(float *)(param_1 + 0x1803c) =
       ((*(float *)(param_1 + 0x1803c) - 1.0) * *(float *)(param_1 + 0x18038) *
       *(float *)(param_1 + 0x18034)) / (float)*(int *)(param_1 + 0x18030);
  local_8 = 0xffffffff;
  FUN_00589530();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

