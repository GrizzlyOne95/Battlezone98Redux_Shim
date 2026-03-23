
undefined4 * __thiscall
FUN_006de060(SchedulerBase *param_1,undefined4 *param_2,SchedulerBase *param_3)

{
  bool bVar1;
  char cVar2;
  undefined4 uVar3;
  uint uVar4;
  
  bVar1 = Concurrency::details::SchedulerBase::HasWorkPending(param_1);
  if ((bVar1) || (bVar1 = Concurrency::details::SchedulerBase::HasWorkPending(param_3), bVar1)) {
    cVar2 = FUN_006d7470();
    if ((cVar2 != '\0') || (cVar2 = FUN_006d5440(), cVar2 != '\0')) {
      FUN_006d1a70(param_2);
      return param_2;
    }
    cVar2 = FUN_006d52d0(*(undefined4 *)param_1,*(undefined4 *)(param_1 + 4));
    if (cVar2 != '\0') {
      uVar3 = get();
      cVar2 = FUN_006d1dc0(uVar3);
      if (cVar2 != '\0') goto LAB_006de11d;
    }
    cVar2 = FUN_006d5280(*(undefined4 *)param_1,*(undefined4 *)(param_1 + 4));
    if (cVar2 != '\0') {
      uVar3 = get();
      cVar2 = FUN_006d1e00(uVar3);
      if (cVar2 != '\0') {
LAB_006de11d:
        FUN_006d1a70(param_2);
        return param_2;
      }
    }
    cVar2 = FUN_006d73e0();
    if (cVar2 != '\0') {
      uVar3 = *(undefined4 *)(param_1 + 4);
      *param_2 = *(undefined4 *)param_1;
      param_2[1] = uVar3;
      return param_2;
    }
    uVar3 = get();
    cVar2 = FUN_006d1e00(uVar3);
    if (cVar2 != '\0') {
      FUN_006d1a30(param_2);
      return param_2;
    }
    uVar3 = get();
    cVar2 = FUN_006d1dc0(uVar3);
    if (cVar2 != '\0') {
      FUN_006d1a50(param_2);
      return param_2;
    }
  }
  uVar4 = get();
  FUN_006c9a90(uVar4 + *(int *)param_1,*(int *)(param_1 + 4) + (uint)CARRY4(uVar4,*(uint *)param_1))
  ;
  return param_2;
}

