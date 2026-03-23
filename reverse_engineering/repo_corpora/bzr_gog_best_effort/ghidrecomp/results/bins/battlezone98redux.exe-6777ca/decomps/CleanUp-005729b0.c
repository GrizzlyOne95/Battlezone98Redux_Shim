
/* Library Function - Single Match
    public: static void __stdcall CPngImage::CleanUp(void)
   
   Library: Visual Studio 2010 Debug */

void CPngImage::CleanUp(void)

{
  if (DAT_00917f48 != (undefined4 *)0x0) {
    if (DAT_00917f48 != (undefined4 *)0x0) {
      (**(code **)*DAT_00917f48)(1);
    }
    DAT_00917f48 = (undefined4 *)0x0;
  }
  return;
}

