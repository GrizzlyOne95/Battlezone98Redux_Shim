
undefined1 __thiscall FUN_004f4670(int param_1,undefined4 param_2)

{
  int iVar1;
  char cVar2;
  bool bVar3;
  undefined1 local_24;
  int local_c;
  
  cVar2 = FUN_004cd1b0(param_2,param_1 + 8,4,"objectiveCount");
  bVar3 = cVar2 != '\0';
  for (local_c = 0; local_c < *(int *)(param_1 + 8); local_c = local_c + 1) {
    iVar1 = param_1 + 0xc + local_c * 0x18;
    if ((bVar3) && (cVar2 = FUN_004cce90(param_2,iVar1,0x10,&DAT_00879d2c), cVar2 != '\0')) {
      bVar3 = true;
    }
    else {
      bVar3 = false;
    }
    if ((bVar3) && (cVar2 = FUN_004cd1b0(param_2,iVar1 + 0x14,4,"color"), cVar2 != '\0')) {
      bVar3 = true;
    }
    else {
      bVar3 = false;
    }
  }
  if ((bVar3) && (cVar2 = FUN_004cd360(param_2,param_1 + 0xfc,4,"objectiveLast"), cVar2 != '\0')) {
    local_24 = 1;
  }
  else {
    local_24 = 0;
  }
  return local_24;
}

