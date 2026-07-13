
undefined4 * FUN_00773800(undefined4 *param_1)

{
  bool bVar1;
  undefined4 uVar2;
  undefined4 in_stack_00000018;
  undefined4 in_stack_0000001c;
  
  while( true ) {
    bVar1 = __FrameHandler3::HandlerMap::iterator::operator!=
                      ((iterator *)&stack0x00000008,(iterator *)&stack0x00000010);
    if (!bVar1) break;
    FUN_00730830();
    uVar2 = FUN_00772230();
    uVar2 = FUN_00417780(uVar2);
    FUN_00730830(uVar2);
    FUN_00772230();
    FUN_00489e20(uVar2);
  }
  *param_1 = in_stack_00000018;
  param_1[1] = in_stack_0000001c;
  return param_1;
}

