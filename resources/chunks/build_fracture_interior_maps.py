"""Build the fracture/chunk cap texture set from one colour image.

    python resources/chunks/build_fracture_interior_maps.py SOURCE.png OUT_DIR

SOURCE is the tileable "burnt machinery with embers" colour image (AI-generated
for this project, 1500x1500). Writes openshim_fracture_interior{,_n,_s,_e}.png
(512x512) to OUT_DIR: the colour map with its top/bottom seam cross-faded, a
normal map from blurred luminance, a low specular map (embers 0) and an
emissive map of the ember pixels. Convert each to BC1 DDS with a full mip chain
(texconv -f BC1_UNORM -m 0) and copy them here; the plugin embeds them
(fracture_interior_textures.rc). Needs Pillow and numpy.
"""
import sys, numpy as np
from PIL import Image, ImageFilter
src, out = sys.argv[1], sys.argv[2]
im = Image.open(src).convert('RGB').resize((1024,1024), Image.LANCZOS)
a = np.asarray(im).astype(np.float32)/255
# seam check: mean abs diff across wrap edge vs interior neighbour rows
def edge(a):
    return float(np.abs(a[0]-a[-1]).mean()), float(np.abs(a[500]-a[501]).mean()), float(np.abs(a[:,0]-a[:,-1]).mean()), float(np.abs(a[:,500]-a[:,501]).mean())
print('seam before', edge(a))
H=a.shape[0]; band=64
w=np.ones(H,np.float32)
t=np.arange(band)/band; w[:band]=0.5+0.5*t; w[-band:]=(0.5+0.5*t)[::-1]
a=a*w[:,None,None]+np.roll(a,H//2,0)*(1-w[:,None,None])
print('seam after', edge(a))
r,g,b = a[...,0],a[...,1],a[...,2]
mx = a.max(-1); mn = a.min(-1); sat = (mx-mn)/np.maximum(mx,1e-4)
ember = np.clip((r-0.33)/0.3,0,1)*np.clip((sat-0.4)/0.3,0,1)*(r>g)*(g>b)
ember = np.asarray(Image.fromarray((ember*255).astype(np.uint8)).filter(ImageFilter.MaxFilter(3)).filter(ImageFilter.GaussianBlur(1.2))).astype(np.float32)/255
print('ember coverage %.3f' % (ember>0.2).mean())
emis = np.clip(a*np.clip(ember*1.6,0,1)[...,None]*1.3,0,1)
lum = 0.299*r+0.587*g+0.114*b
h = np.asarray(Image.fromarray((lum*255).astype(np.uint8)).filter(ImageFilter.GaussianBlur(1.5))).astype(np.float32)/255
dx = (np.roll(h,-1,1)-np.roll(h,1,1))*0.5; dy = (np.roll(h,-1,0)-np.roll(h,1,0))*0.5
k = 6.0
# Green is the slope along +v, which runs DOWN the image in D3D (BZBase builds
# its tangent frame from screen derivatives), so both components are negated.
n = np.dstack([-dx*k, -dy*k, np.ones_like(h)]); n /= np.linalg.norm(n,axis=-1,keepdims=True)
nrm = (n*0.5+0.5)
spec = np.clip(0.06 + 0.45*np.clip((lum-0.12)/0.5,0,1),0,1)*(1-ember)
def save(arr, name):
    if arr.ndim==2: arr=np.dstack([arr]*3)
    Image.fromarray((np.clip(arr,0,1)*255+0.5).astype(np.uint8)).resize((512,512), Image.LANCZOS).save(f'{out}/{name}.png')
save(a,'openshim_fracture_interior'); save(nrm,'openshim_fracture_interior_n'); save(spec,'openshim_fracture_interior_s'); save(emis,'openshim_fracture_interior_e')
