
/* WARNING: Removing unreachable block (ram,0x007742b5) */

int __thiscall FUN_00774290(int param_1,int param_2)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  undefined1 local_14 [4];
  undefined1 local_10 [4];
  int local_c;
  undefined1 local_7;
  undefined1 local_6 [2];
  
  local_c = param_1;
  if (param_1 != param_2) {
    FID_conflict__Tidy(1,0);
    uVar2 = Getal(local_6);
    uVar3 = Getal(&local_7);
    cVar1 = operator!=<>(uVar3,uVar2);
    if (cVar1 == '\0') {
      uVar2 = FUN_00417780(param_2);
      FID_conflict__Assign_rv(uVar2);
    }
    else {
      puVar4 = (undefined4 *)FID_conflict_end(local_10);
      uVar2 = *puVar4;
      puVar4 = (undefined4 *)FID_conflict_begin(local_14);
      assign<>(*puVar4,uVar2);
    }
  }
  return local_c;
}

