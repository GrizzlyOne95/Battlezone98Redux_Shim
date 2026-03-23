
undefined4 FUN_0059c140(void)

{
  CMetaFileDC *this;
  undefined4 local_18;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084711c;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  this = operator_new(0x1150);
  local_8 = 0;
  if (this == (CMetaFileDC *)0x0) {
    local_18 = 0;
  }
  else {
    local_18 = CMetaFileDC::CMetaFileDC(this);
  }
  ExceptionList = local_10;
  return local_18;
}

