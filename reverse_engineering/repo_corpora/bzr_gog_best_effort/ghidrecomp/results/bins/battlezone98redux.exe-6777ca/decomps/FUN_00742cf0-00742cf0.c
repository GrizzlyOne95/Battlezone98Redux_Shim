
undefined4 FUN_00742cf0(void)

{
  char cVar1;
  undefined4 uVar2;
  undefined1 local_28 [16];
  undefined1 local_18 [16];
  int *local_8;
  
  cVar1 = FUN_0073a900();
  if (cVar1 == '\0') {
    uVar2 = 0;
  }
  else {
    (**(code **)(*local_8 + 0x68))(local_28,local_8 + 10);
    (**(code **)(*local_8 + 0x38))(local_18);
    uVar2 = FUN_0056f780(local_18);
  }
  return uVar2;
}

