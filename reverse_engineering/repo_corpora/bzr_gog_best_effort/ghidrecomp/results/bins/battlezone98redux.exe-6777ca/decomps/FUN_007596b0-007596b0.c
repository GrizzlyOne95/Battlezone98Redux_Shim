
uint FUN_007596b0(undefined4 param_1,undefined4 param_2,uint param_3,undefined4 param_4)

{
  char cVar1;
  uint in_EAX;
  uint uVar2;
  undefined1 local_1c [16];
  undefined4 local_c;
  
  if (param_3 < 0x481) {
    local_c = param_2;
    FUN_00574b20(local_1c,&param_1);
    cVar1 = FUN_0073a900();
    if (cVar1 == '\0') {
      uVar2 = 0;
    }
    else {
      uVar2 = FUN_007592d0(local_1c,local_c,param_3,param_4);
    }
  }
  else {
    uVar2 = in_EAX & 0xffffff00;
  }
  return uVar2;
}

