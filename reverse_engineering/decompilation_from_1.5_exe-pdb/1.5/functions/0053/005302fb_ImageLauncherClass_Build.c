/*
 * Entry: 005302fb
 * Name: ImageLauncherClass::Build
 * Namespace: ImageLauncherClass
 * Signature: Weapon * Build(ImageLauncherClass * this, _OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Weapon * __thiscall ImageLauncherClass::Build(ImageLauncherClass *this,_OBJ76 *param_1)

{
  ImageLauncher *pIVar1;
  
  pIVar1 = operator_new(0xd0);
  if (pIVar1 == (ImageLauncher *)0x0) {
    pIVar1 = (ImageLauncher *)0x0;
  }
  else {
    pIVar1 = ImageLauncher::ImageLauncher(pIVar1,param_1,this);
  }
  return (Weapon *)pIVar1;
}
