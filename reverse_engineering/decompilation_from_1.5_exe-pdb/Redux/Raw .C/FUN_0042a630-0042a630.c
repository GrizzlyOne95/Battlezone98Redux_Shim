
undefined4 FUN_0042a630(FILE *param_1)

{
  int iVar1;
  undefined4 uVar2;
  size_t _Count;
  void *_DstBuf;
  size_t sVar3;
  
  iVar1 = fseek(param_1,0,2);
  if (iVar1 == 0) {
    _Count = ftell(param_1);
    if ((int)_Count < 0) {
      uVar2 = 0xfffffffd;
    }
    else if (_Count == 0) {
      uVar2 = 0;
    }
    else {
      _DstBuf = (void *)FUN_0083e9fc(_Count + 1,&DAT_00914ce1);
      if (_DstBuf == (void *)0x0) {
        uVar2 = 0xfffffffe;
      }
      else {
        *(undefined1 *)((int)_DstBuf + _Count) = 0;
        fseek(param_1,0,0);
        sVar3 = fread(_DstBuf,1,_Count,param_1);
        if (sVar3 == _Count) {
          uVar2 = FUN_0042df40(_DstBuf,sVar3);
          operator_delete__(_DstBuf);
        }
        else {
          operator_delete__(_DstBuf);
          uVar2 = 0xfffffffd;
        }
      }
    }
  }
  else {
    uVar2 = 0xfffffffd;
  }
  return uVar2;
}

