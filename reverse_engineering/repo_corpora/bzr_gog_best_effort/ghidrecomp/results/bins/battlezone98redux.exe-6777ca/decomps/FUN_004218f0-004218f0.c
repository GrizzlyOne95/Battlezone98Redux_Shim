
fpos<int> * FUN_004218f0(fpos<int> *param_1)

{
  char cVar1;
  int _Origin;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  longlong lVar5;
  undefined8 local_10;
  int local_8;
  
  local_10 = FUN_004236a0();
  lVar5 = FUN_00421b00();
  _Origin = (int)(lVar5 - local_10);
  iVar4 = (int)((ulonglong)(lVar5 - local_10) >> 0x20);
  if (*(int *)(local_8 + 0x50) != 0) {
    cVar1 = FUN_00423330();
    if (cVar1 != '\0') {
      iVar2 = fsetpos(*(FILE **)(local_8 + 0x50),&local_10);
      if (iVar2 == 0) {
        if (_Origin != 0 || iVar4 != 0) {
          iVar4 = _fseeki64(*(FILE **)(local_8 + 0x50),CONCAT44(1,iVar4),_Origin);
          if (iVar4 != 0) goto LAB_00421989;
        }
        iVar4 = fgetpos(*(FILE **)(local_8 + 0x50),&local_10);
        if (iVar4 == 0) {
          uVar3 = FUN_004170c0();
          *(undefined4 *)(local_8 + 0x48) = uVar3;
          FUN_00423580();
          std::fpos<int>::fpos<int>
                    (param_1,*(int *)(local_8 + 0x48),CONCAT44(_Origin,local_10._4_4_));
          return param_1;
        }
      }
    }
  }
LAB_00421989:
  std::fpos<int>::fpos<int>(param_1,*(__int64 *)_BADOFF_exref);
  return param_1;
}

