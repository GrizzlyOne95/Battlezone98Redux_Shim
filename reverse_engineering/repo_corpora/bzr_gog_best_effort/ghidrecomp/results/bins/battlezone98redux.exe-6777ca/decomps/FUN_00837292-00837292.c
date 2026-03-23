
void FUN_00837292(undefined4 param_1)

{
  char *pcVar1;
  int iVar2;
  undefined4 uVar3;
  char *pcVar4;
  int iVar5;
  undefined4 uVar6;
  int local_74;
  undefined4 local_70;
  undefined1 local_6c [4];
  undefined4 local_68;
  undefined4 local_64;
  undefined4 local_60;
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined1 local_48 [64];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_70 = FUN_008376b6(param_1,&local_74);
  iVar5 = local_74;
  local_74 = local_74 + 2;
  pcVar1 = (char *)FUN_0082c225(param_1,local_74,"flnSu",0);
  iVar5 = iVar5 + 1;
  iVar2 = FUN_0082c9c5(param_1,iVar5);
  if (iVar2 == 0) {
    iVar2 = FUN_0082d490(param_1,iVar5);
    if (iVar2 == 6) {
      FUN_0082cc9e(param_1,&DAT_0086fd84,pcVar1);
      pcVar1 = (char *)FUN_0082d377(param_1,0xffffffff,0);
      FUN_0082cdd2(param_1,iVar5);
      uVar6 = local_70;
      FUN_0082d4cc(param_1,local_70,1);
      goto LAB_0083734a;
    }
    pcVar1 = "function or level expected";
  }
  else {
    uVar3 = FUN_0082d338(param_1,iVar5,local_6c);
    uVar6 = local_70;
    iVar5 = FUN_0082e171(local_70,uVar3);
    if (iVar5 == 0) {
      FUN_0082cd45(param_1);
      goto LAB_00837481;
    }
LAB_0083734a:
    iVar5 = FUN_0082e08b(uVar6,pcVar1,local_6c);
    if (iVar5 != 0) {
      FUN_0082c68b(param_1,0,2);
      pcVar4 = strchr(pcVar1,0x53);
      if (pcVar4 != (char *)0x0) {
        FUN_008377ef(param_1,"source",local_5c);
        FUN_008377ef(param_1,"short_src",local_48);
        FUN_008377cf(param_1,"linedefined",local_50);
        FUN_008377cf(param_1,"lastlinedefined",local_4c);
        FUN_008377ef(param_1,&DAT_008751c0,local_60);
      }
      pcVar4 = strchr(pcVar1,0x6c);
      if (pcVar4 != (char *)0x0) {
        FUN_008377cf(param_1,"currentline",local_58);
      }
      pcVar4 = strchr(pcVar1,0x75);
      if (pcVar4 != (char *)0x0) {
        FUN_008377cf(param_1,&DAT_0086fdf0,local_54);
      }
      pcVar4 = strchr(pcVar1,0x6e);
      if (pcVar4 != (char *)0x0) {
        FUN_008377ef(param_1,&DAT_00879d2c,local_68);
        FUN_008377ef(param_1,"namewhat",local_64);
      }
      pcVar4 = strchr(pcVar1,0x4c);
      if (pcVar4 != (char *)0x0) {
        FUN_0083780f(param_1,local_70,"activelines");
      }
      pcVar1 = strchr(pcVar1,0x66);
      if (pcVar1 != (char *)0x0) {
        FUN_0083780f(param_1,local_70,&DAT_0086fe10);
      }
      goto LAB_00837481;
    }
    pcVar1 = "invalid option";
    iVar5 = local_74;
  }
  FUN_0082b8e4(param_1,iVar5,pcVar1);
LAB_00837481:
  FUN_0083e885();
  return;
}

