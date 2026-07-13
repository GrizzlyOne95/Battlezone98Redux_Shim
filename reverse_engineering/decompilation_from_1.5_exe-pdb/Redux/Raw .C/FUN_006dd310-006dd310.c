
undefined4 * __thiscall
FUN_006dd310(SchedulerBase *param_1,undefined4 *param_2,SchedulerBase *param_3)

{
  undefined4 uVar1;
  bool bVar2;
  char cVar3;
  undefined8 uVar4;
  
  bVar2 = Concurrency::details::SchedulerBase::HasWorkPending(param_1);
  if ((bVar2) || (bVar2 = Concurrency::details::SchedulerBase::HasWorkPending(param_3), bVar2)) {
    cVar3 = FUN_006d7470();
    if ((cVar3 != '\0') || (cVar3 = FUN_006d7470(), cVar3 != '\0')) {
      FUN_006d1a70(param_2);
      return param_2;
    }
    cVar3 = FUN_006d52d0(*(undefined4 *)param_1,*(undefined4 *)(param_1 + 4));
    if (cVar3 != '\0') {
      uVar4 = FUN_006c94e0();
      cVar3 = FUN_006d52d0(uVar4);
      if (cVar3 != '\0') goto LAB_006dd3d0;
    }
    cVar3 = FUN_006d5280(*(undefined4 *)param_1,*(undefined4 *)(param_1 + 4));
    if (cVar3 != '\0') {
      uVar4 = FUN_006c94e0();
      cVar3 = FUN_006d5280(uVar4);
      if (cVar3 != '\0') {
LAB_006dd3d0:
        FUN_006d1a70(param_2);
        return param_2;
      }
    }
    cVar3 = FUN_006d73e0();
    if (cVar3 != '\0') {
      uVar1 = *(undefined4 *)(param_1 + 4);
      *param_2 = *(undefined4 *)param_1;
      param_2[1] = uVar1;
      return param_2;
    }
    uVar4 = FUN_006c94e0();
    cVar3 = FUN_006d52d0(uVar4);
    if (cVar3 != '\0') {
      FUN_006d1a50(param_2);
      return param_2;
    }
    uVar4 = FUN_006c94e0();
    cVar3 = FUN_006d5280(uVar4);
    if (cVar3 != '\0') {
      FUN_006d1a30(param_2);
      return param_2;
    }
  }
  uVar4 = FUN_006c94e0();
  FUN_006c9a90(*(uint *)param_1 - (uint)uVar4,
               (*(int *)(param_1 + 4) - (int)((ulonglong)uVar4 >> 0x20)) -
               (uint)(*(uint *)param_1 < (uint)uVar4));
  return param_2;
}

