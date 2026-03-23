
char * FUN_007591f0(undefined4 param_1)

{
  char cVar1;
  char *pcVar2;
  undefined4 uVar3;
  undefined1 local_18 [4];
  int local_14;
  undefined1 local_10 [4];
  int local_c;
  char local_5;
  
  local_14 = FUN_00764760();
  local_5 = '\x01';
  if (local_14 != 0) {
    local_c = FUN_0056f900();
    if (local_c != 0) {
      FUN_0042d8c0(local_10);
      FID_conflict_begin(local_18);
      while( true ) {
        cVar1 = FUN_00420f10(local_18);
        if (cVar1 == '\0') break;
        uVar3 = param_1;
        FUN_0042da60(param_1);
        cVar1 = FUN_0056f780(uVar3);
        if (cVar1 != '\0') {
          local_5 = '\0';
          break;
        }
        FUN_0042da80();
      }
    }
  }
  if (local_5 == '\0') {
    pcVar2 = "";
  }
  else {
    pcVar2 = " !!!Destination not in lobby!!!";
  }
  return pcVar2;
}

