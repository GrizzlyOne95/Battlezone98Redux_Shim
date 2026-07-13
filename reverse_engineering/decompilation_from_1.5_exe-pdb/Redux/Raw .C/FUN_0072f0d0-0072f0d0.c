
void FUN_0072f0d0(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  bool bVar1;
  iterator *piVar2;
  
  while( true ) {
    bVar1 = __FrameHandler3::HandlerMap::iterator::operator!=
                      ((iterator *)&param_1,(iterator *)&param_3);
    if (!bVar1) {
      return;
    }
    piVar2 = (iterator *)FUN_00730830();
    bVar1 = __FrameHandler3::HandlerMap::iterator::operator!=((iterator *)&param_1,piVar2);
    if (!bVar1) break;
    FUN_00731030(param_1,param_2,param_3,param_4);
    FUN_00730810();
  }
  return;
}

