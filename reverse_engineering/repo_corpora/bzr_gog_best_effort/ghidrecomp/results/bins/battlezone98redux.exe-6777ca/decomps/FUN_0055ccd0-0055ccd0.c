
undefined1 __thiscall FUN_0055ccd0(int param_1,undefined4 param_2)

{
  bool bVar1;
  char cVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined1 local_20;
  
  if (DAT_009173b7 == '\0') {
    cVar2 = FUN_004ccf20(param_2,param_1 + 0x54,0x1d,"b_array");
    uVar3 = 6;
    if ((cVar2 == '\0') ||
       (cVar2 = FUN_004cd360(param_2,param_1 + 0x74,0x18,"f_array"), cVar2 == '\0')) {
      bVar1 = false;
    }
    else {
      bVar1 = true;
    }
    uVar4 = 0x15;
    if ((bVar1) && (cVar2 = FUN_004cd1b0(param_2,param_1 + 0x90,0x54,"h_array"), cVar2 != '\0')) {
      bVar1 = true;
    }
    else {
      bVar1 = false;
    }
    if ((bVar1) &&
       (cVar2 = FUN_004cd1b0(param_2,param_1 + 0xe8,0x10,"i_array",4,uVar4,uVar3), cVar2 != '\0')) {
      bVar1 = true;
    }
    else {
      bVar1 = false;
    }
    if ((bVar1) && (cVar2 = FUN_0045d830(param_2), cVar2 != '\0')) {
      local_20 = 1;
    }
    else {
      local_20 = 0;
    }
  }
  else {
    local_20 = FUN_0045d830(param_2);
  }
  return local_20;
}

