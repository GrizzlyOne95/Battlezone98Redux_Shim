/*
 * Entry: 00530255
 * Name: ImageLauncher::~ImageLauncher
 * Namespace: ImageLauncher
 * Signature: void ~ImageLauncher(ImageLauncher * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ImageLauncher::~ImageLauncher(ImageLauncher *this)

{
  *(undefined ***)this = &_vftable_;
  Launcher::~Launcher((Launcher *)this);
  return;
}
