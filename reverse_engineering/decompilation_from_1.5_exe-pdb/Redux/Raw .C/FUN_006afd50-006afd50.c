
undefined4 FUN_006afd50(undefined4 param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  
  if (param_2 < 0x2740) {
    if (param_2 == 0x273f) {
      FUN_006d8cc0(0x273f,0);
      return param_1;
    }
    if (param_2 < 0x2727) {
      if (param_2 == 0x2726) {
        FUN_006d8cc0(0x2726,0);
        return param_1;
      }
      if (param_2 == 0) {
        FUN_004fbb60();
        return param_1;
      }
      if (param_2 == 8) {
        FUN_006d8cc0(0xe,0);
        return param_1;
      }
    }
    else if (param_2 == 0x273c) {
      FUN_006d8f10(0x273c,0);
      return param_1;
    }
  }
  else if (param_2 < 0x2afb) {
    if (param_2 == 0x2afa) {
      FUN_006d8f10(0x2afa,0);
      return param_1;
    }
    if (param_2 == 0x277d) {
      FUN_006d8f10(0x277d,0);
      return param_1;
    }
    if (param_2 == 0x2af9) {
      FUN_006d8f10(0x2af9,0);
      return param_1;
    }
  }
  else if (param_2 == 0x2afb) {
    FUN_006d8f10(0x2afb,0);
    return param_1;
  }
  uVar1 = FUN_006abbb0();
  iVar2 = WSAGetLastError();
  FUN_00416430(iVar2,uVar1);
  return param_1;
}

