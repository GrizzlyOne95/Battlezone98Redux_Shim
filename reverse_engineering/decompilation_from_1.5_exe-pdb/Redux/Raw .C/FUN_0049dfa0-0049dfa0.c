
undefined4 * __thiscall
FUN_0049dfa0(undefined4 *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  uint uVar1;
  int iVar2;
  float fVar3;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00849538;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_004e54c0(param_2,param_3,1);
  local_8 = 0;
  *param_1 = BuildGoto::vftable;
  param_1[0x54] = param_4;
  *(undefined1 *)((int)param_1 + 0x13e) = 1;
  param_1[0x53] = 0;
  iVar2 = FUN_0049c590(uVar1);
  fVar3 = *(float *)(iVar2 + 0xc) + 10.0;
  param_1[0x55] = fVar3 * fVar3;
  FUN_005aecb0(param_4);
  ExceptionList = local_10;
  return param_1;
}

