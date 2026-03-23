
undefined4 * __thiscall
FUN_006dc780(SchedulerBase *param_1,undefined4 *param_2,SchedulerBase *param_3)

{
  bool bVar1;
  char cVar2;
  undefined4 uVar3;
  int iVar4;
  
  bVar1 = Concurrency::details::SchedulerBase::HasWorkPending(param_1);
  if ((bVar1) || (bVar1 = Concurrency::details::SchedulerBase::HasWorkPending(param_3), bVar1)) {
    cVar2 = FUN_006d5440();
    if ((cVar2 != '\0') || (cVar2 = FUN_006d5440(), cVar2 != '\0')) {
      FUN_006ce150(param_2);
      return param_2;
    }
    cVar2 = FUN_006d1e00(*(undefined4 *)param_1);
    if (cVar2 != '\0') {
      uVar3 = get();
      cVar2 = FUN_006d1e00(uVar3);
      if (cVar2 != '\0') goto LAB_006dc835;
    }
    cVar2 = FUN_006d1dc0(*(undefined4 *)param_1);
    if (cVar2 != '\0') {
      uVar3 = get();
      cVar2 = FUN_006d1dc0(uVar3);
      if (cVar2 != '\0') {
LAB_006dc835:
        FUN_006ce150(param_2);
        return param_2;
      }
    }
    cVar2 = FUN_006d53e0();
    if (cVar2 != '\0') {
      *param_2 = *(undefined4 *)param_1;
      return param_2;
    }
    uVar3 = get();
    cVar2 = FUN_006d1e00(uVar3);
    if (cVar2 != '\0') {
      FUN_006ce130(param_2);
      return param_2;
    }
    uVar3 = get();
    cVar2 = FUN_006d1dc0(uVar3);
    if (cVar2 != '\0') {
      FUN_006ce110(param_2);
      return param_2;
    }
  }
  iVar4 = get();
  FUN_00447eb0(*(int *)param_1 - iVar4);
  return param_2;
}

