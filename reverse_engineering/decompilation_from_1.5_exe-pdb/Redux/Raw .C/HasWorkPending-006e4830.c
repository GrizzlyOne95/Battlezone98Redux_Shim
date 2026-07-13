
/* Library Function - Single Match
    protected: virtual bool __thiscall Concurrency::details::SchedulerBase::HasWorkPending(void)
   
   Library: Visual Studio 2010 Debug */

bool __thiscall Concurrency::details::SchedulerBase::HasWorkPending(SchedulerBase *this)

{
  char cVar1;
  bool bVar2;
  
  cVar1 = FUN_006e5fe0();
  if ((cVar1 == '\0') && (bVar2 = HasWorkPending(this), !bVar2)) {
    return false;
  }
  return true;
}

