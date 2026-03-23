
undefined1 __thiscall FUN_0059ca70(int param_1,undefined4 param_2)

{
  bool bVar1;
  char cVar2;
  undefined1 local_1c;
  
  cVar2 = FUN_004cd1b0(param_2,param_1 + 0x14c,4,"patrol_type");
  if ((cVar2 == '\0') || (cVar2 = FUN_004cf520(param_2,param_1 + 0x150,4,"my_craft"), cVar2 == '\0')
     ) {
    bVar1 = false;
  }
  else {
    bVar1 = true;
  }
  if ((bVar1) && (cVar2 = FUN_004cd1b0(param_2,param_1 + 0x154,4,"patrol_dir"), cVar2 != '\0')) {
    bVar1 = true;
  }
  else {
    bVar1 = false;
  }
  if ((bVar1) && (cVar2 = FUN_004e5cf0(param_2), cVar2 != '\0')) {
    local_1c = 1;
  }
  else {
    local_1c = 0;
  }
  return local_1c;
}

