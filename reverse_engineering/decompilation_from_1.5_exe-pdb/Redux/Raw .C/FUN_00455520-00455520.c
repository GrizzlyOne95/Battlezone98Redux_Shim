
undefined4 * __thiscall FUN_00455520(undefined4 *param_1,int param_2,undefined4 param_3,int param_4)

{
  uint uVar1;
  undefined4 uVar2;
  undefined2 *puVar3;
  undefined1 local_1c [8];
  byte local_14;
  byte bStack_13;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00846d28;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_00448f10(param_2,param_3,param_4);
  local_8 = 0;
  *param_1 = SpriteRender::vftable;
  param_1[0x1c] = 0xffffffff;
  if (*(char *)(param_2 + 0x184) != '\0') {
    uVar2 = FUN_00780dc0((int)((double)DAT_02cc50e4 * *(double *)(param_4 + 0x28)),
                         (int)((double)DAT_02cc50e4 * *(double *)(param_4 + 0x38)),uVar1);
    puVar3 = (undefined2 *)FUN_00780fd0(local_1c,uVar2);
    local_14 = (byte)*puVar3;
    bStack_13 = (byte)((ushort)*puVar3 >> 8);
    param_1[0x1c] =
         (((int)((uint)local_14 * 7) >> 3) + 0x20U & 0xff) << 0x10 | 0xff000000 |
         (((int)((uint)bStack_13 * 7) >> 3) + 0x20U & 0xff) << 8 |
         ((int)((uint)*(byte *)(puVar3 + 1) * 7) >> 3) + 0x20U & 0xff;
  }
  ExceptionList = local_10;
  return param_1;
}

