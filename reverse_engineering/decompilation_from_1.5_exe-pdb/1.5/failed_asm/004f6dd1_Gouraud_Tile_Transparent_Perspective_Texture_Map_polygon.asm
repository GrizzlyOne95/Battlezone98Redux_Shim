; Entry: 004f6dd1
; Name: Gouraud_Tile_Transparent_Perspective_Texture_Map_polygon
; Signature: void Gouraud_Tile_Transparent_Perspective_Texture_Map_polygon(_GRAPHIC_BUFFER * param_1, POINT_3D * param_2, long param_3, POLYGON_SKIN param_4)
; Stop: 0x004f77b5
; Reason: Exception while decompiling 004f6dd1: process: timeout 
; Command: C:\Program Files\LLVM\bin\llvm-objdump.EXE -d --no-show-raw-insn --start-address=0x004f6dd1 --stop-address=0x004f77b5 C:\Users\istuart\Downloads\bzone15227\extracted\bzone.exe


C:\Users\istuart\Downloads\bzone15227\extracted\bzone.exe:	file format coff-i386

Disassembly of section .text:

00401000 <.text>:
  4f6dd1:      	pushl	%ebp
  4f6dd2:      	movl	%esp, %ebp
  4f6dd4:      	pushl	%ebx
  4f6dd5:      	pushl	%esi
  4f6dd6:      	pushl	%edi
  4f6dd7:      	movl	0x14(%ebp), %ebx
  4f6dda:      	pushl	%ebp
  4f6ddb:      	movl	0xcfdbc0, %eax
  4f6de0:      	subl	$0x700, %esp            # imm = 0x700
  4f6de6:      	cmpl	%ebx, %eax
  4f6de8:      	je	0x4f6e58 <.text+0xf5e58>
  4f6dea:      	movl	%ebx, 0xcfdbc0
  4f6df0:      	leal	0xcfdbd8, %edx
  4f6df6:      	movl	(%ebx), %eax
  4f6df8:      	movl	0x4(%ebx), %ecx
  4f6dfb:      	leal	0x8(%ebx), %esi
  4f6dfe:      	movl	%ecx, 0x4(%esp)
  4f6e02:      	movl	%eax, %edi
  4f6e04:      	addl	$0x3, %ecx
  4f6e07:      	addl	%esi, %edi
  4f6e09:      	leal	(%esi,%eax,2), %ebx
  4f6e0c:      	leal	(%eax,%eax,2), %eax
  4f6e0f:      	movl	%esi, -0x4(%edx)
  4f6e12:      	movl	%esi, -0x8(%edx)
  4f6e15:      	movl	%esi, -0xc(%edx)
  4f6e18:      	movl	%esi, -0x10(%edx)
  4f6e1b:      	movl	%esi, (%edx)
  4f6e1d:      	movl	%edi, 0x4(%edx)
  4f6e20:      	movl	%ebx, 0x8(%edx)
  4f6e23:      	addl	%eax, %esi
  4f6e25:      	addl	%eax, %edi
  4f6e27:      	addl	%eax, %ebx
  4f6e29:      	addl	$0xc, %edx
  4f6e2c:      	subl	$0x3, %ecx
  4f6e2f:      	jge	0x4f6e1b <.text+0xf5e1b>
  4f6e31:      	movl	0x4(%esp), %edx
  4f6e35:      	movl	0xcfdbd4(,%edx,4), %eax
  4f6e3c:      	movl	%eax, 0xcfdbd8(,%edx,4)
  4f6e43:      	movl	%eax, 0xcfdbdc(,%edx,4)
  4f6e4a:      	movl	%eax, 0xcfdbe0(,%edx,4)
  4f6e51:      	movl	%eax, 0xcfdbe4(,%edx,4)
  4f6e58:      	movl	0x14(%ebp), %ebx
  4f6e5b:      	movl	$0x186a0, %edx          # imm = 0x186A0
  4f6e60:      	movl	0xc(%ebp), %esi
  4f6e63:      	movl	0x10(%ebp), %eax
  4f6e66:      	movl	(%ebx), %ecx
  4f6e68:      	movl	0x4(%ebx), %edi
  4f6e6b:      	decl	%ecx
  4f6e6c:      	decl	%edi
  4f6e6d:      	fildl	0x4(%ebx)
  4f6e70:      	movl	%ecx, 0x18(%esp)
  4f6e74:      	movl	%edi, 0x1c(%esp)
  4f6e78:      	incl	%ecx
  4f6e79:      	movl	%esi, (%esp)
  4f6e7c:      	shll	$0x3, %eax
  4f6e7f:      	leal	0x8(%ebx), %edi
  4f6e82:      	fsubs	0x62c808
  4f6e88:      	fildl	(%ebx)
  4f6e8a:      	movl	%ecx, 0x10(%esp)
  4f6e8e:      	leal	(%eax,%eax,2), %ecx
  4f6e91:      	xorl	%eax, %eax
  4f6e93:      	movl	%edi, 0x24(%esp)
  4f6e97:      	fsubs	0x62c808
  4f6e9d:      	flds	0x62c808
  4f6ea3:      	fsubs	0x14(%esi,%eax)
  4f6ea7:      	flds	0x4(%esi,%eax)
  4f6eab:      	faddl	0x632380
  4f6eb1:      	fxch	%st(1)
  4f6eb3:      	flds	0xc(%esi,%eax)
  4f6eb7:      	fmul	%st(3), %st
  4f6eb9:      	flds	0x10(%esi,%eax)
  4f6ebd:      	fmul	%st(5), %st
  4f6ebf:      	fxch	%st(3)
  4f6ec1:      	fstpl	0x648(%esp)
  4f6ec8:      	fxch	%st(1)
  4f6eca:      	fmuls	0x62c810
  4f6ed0:      	fxch	%st(2)
  4f6ed2:      	fstps	0x10(%esi,%eax)
  4f6ed6:      	fstps	0xc(%esi,%eax)
  4f6eda:      	fstps	0x14(%esi,%eax)
  4f6ede:      	movl	0x648(%esp), %edi
  4f6ee5:      	movl	%eax, 0x328(%esp,%eax)
  4f6eec:      	movl	%eax, 0x58(%esp,%eax)
  4f6ef0:      	movl	%edi, 0x344(%esp,%eax)
  4f6ef7:      	addl	$0x18, %eax
  4f6efa:      	cmpl	%edx, %edi
  4f6efc:      	jg	0x4f6f02 <.text+0xf5f02>
  4f6efe:      	movl	%eax, %ebx
  4f6f00:      	movl	%edi, %edx
  4f6f02:      	cmpl	%ecx, %eax
  4f6f04:      	jne	0x4f6e9d <.text+0xf5e9d>
  4f6f06:      	subl	$0x18, %ebx
  4f6f09:      	leal	-0x18(%eax), %ecx
  4f6f0c:      	fcompp
  4f6f0e:      	movl	$0x0, 0x328(%esp,%eax)
  4f6f19:      	movl	%ecx, 0x40(%esp)
  4f6f1d:      	movl	0x8(%ebp), %edi
  4f6f20:      	movl	%ebx, 0x6d0(%esp)
  4f6f27:      	movl	%ebx, 0x6a0(%esp)
  4f6f2e:      	movl	%ebx, 0x6d4(%esp)
  4f6f35:      	movl	%esi, %ebp
  4f6f37:      	movl	0x20(%edi), %eax
  4f6f3a:      	movl	(%edi), %ecx
  4f6f3c:      	addl	%edx, %eax
  4f6f3e:      	movl	0x14(%edi), %esi
  4f6f41:      	movl	0x1c(%edi), %edi
  4f6f44:      	imull	%ecx
  4f6f46:      	addl	%edi, %esi
  4f6f48:      	movl	%ecx, 0xc(%esp)
  4f6f4c:      	addl	%eax, %esi
  4f6f4e:      	movl	0x344(%esp,%ebx), %edi
  4f6f55:      	movl	%esi, 0x20(%esp)
  4f6f59:      	movl	%ebx, 0x6a4(%esp)
  4f6f60:      	movl	0x6d4(%esp), %ecx
  4f6f67:      	movl	0x344(%esp,%ecx), %eax
  4f6f6e:      	movl	%edi, 0x4(%esp)
  4f6f72:      	cmpl	%eax, %edi
  4f6f74:      	jl	0x4f70a3 <.text+0xf60a3>
  4f6f7a:      	movl	0x340(%esp,%ecx), %edx
  4f6f81:      	movl	%ecx, %eax
  4f6f83:      	movl	%edx, 0x6d4(%esp)
  4f6f8a:      	cmpl	0x6a0(%esp), %edx
  4f6f91:      	je	0x4f77a9 <.text+0xf67a9>
  4f6f97:      	movl	0x344(%esp,%edx), %esi
  4f6f9e:      	movl	%edx, %ecx
  4f6fa0:      	cmpl	%esi, %edi
  4f6fa2:      	jge	0x4f6f7a <.text+0xf5f7a>
  4f6fa4:      	flds	0x14(%ebp,%edx)
  4f6fa8:      	fsubs	0x14(%ebp,%eax)
  4f6fac:      	flds	0x4(%ebp,%edx)
  4f6fb0:      	fsubs	0x4(%ebp,%eax)
  4f6fb4:      	flds	0x10(%ebp,%edx)
  4f6fb8:      	fsubs	0x10(%ebp,%eax)
  4f6fbc:      	fxch	%st(1)
  4f6fbe:      	fdivrs	0x62c808
  4f6fc4:      	flds	0xc(%ebp,%edx)
  4f6fc8:      	fsubs	0xc(%ebp,%eax)
  4f6fcc:      	fxch	%st(1)
  4f6fce:      	fmul	%st, %st(2)
  4f6fd0:      	flds	0x8(%ebp,%edx)
  4f6fd4:      	fsubs	0x8(%ebp,%eax)
  4f6fd8:      	fxch	%st(2)
  4f6fda:      	fmul	%st(1), %st
  4f6fdc:      	flds	(%ebp,%edx)
  4f6fe0:      	fsubs	(%ebp,%eax)
  4f6fe4:      	fxch	%st(3)
  4f6fe6:      	fmul	%st(2), %st
  4f6fe8:      	fxch	%st(4)
  4f6fea:      	fstps	0x6f0(%esp)
  4f6ff1:      	fstps	0x6ec(%esp)
  4f6ff8:      	fmul	%st, %st(3)
  4f6ffa:      	flds	0x4(%ebp,%eax)
  4f6ffe:      	faddl	0x632380
  4f7004:      	fxch	%st(2)
  4f7006:      	fmulp	%st, %st(1)
  4f7008:      	fxch	%st(3)
  4f700a:      	fstps	0x6fc(%esp)
  4f7011:      	fstpl	0x648(%esp)
  4f7018:      	fstps	0x6f8(%esp)
  4f701f:      	fildl	0x648(%esp)
  4f7026:      	fxch	%st(1)
  4f7028:      	fstps	0x6f4(%esp)
  4f702f:      	fsubs	0x4(%ebp,%eax)
  4f7033:      	flds	0x6f4(%esp)
  4f703a:      	flds	0x6f8(%esp)
  4f7041:      	fmul	%st(2), %st
  4f7043:      	flds	0x6ec(%esp)
  4f704a:      	fmul	%st(3), %st
  4f704c:      	flds	0x6fc(%esp)
  4f7053:      	fmul	%st(4), %st
  4f7055:      	fxch	%st(2)
  4f7057:      	fadds	0x8(%ebp,%eax)
  4f705b:      	flds	0x6f0(%esp)
  4f7062:      	fmul	%st(5), %st
  4f7064:      	fxch	%st(2)
  4f7066:      	fadds	0xc(%ebp,%eax)
  4f706a:      	fxch	%st(4)
  4f706c:      	fmulp	%st, %st(5)
  4f706e:      	fstps	0x6dc(%esp)
  4f7075:      	fadds	0x10(%ebp,%eax)
  4f7079:      	fxch	%st(3)
  4f707b:      	fadds	(%ebp,%eax)
  4f707f:      	fxch	%st(2)
  4f7081:      	fstps	0x6e0(%esp)
  4f7088:      	fadds	0x14(%ebp,%eax)
  4f708c:      	fxch	%st(2)
  4f708e:      	fstps	0x6e4(%esp)
  4f7095:      	fstps	0x6d8(%esp)
  4f709c:      	fstps	0x6e8(%esp)
  4f70a3:      	movl	0x6a4(%esp), %ecx
  4f70aa:      	cmpl	0x344(%esp,%ecx), %edi
  4f70b1:      	jl	0x4f71ce <.text+0xf61ce>
  4f70b7:      	movl	0x40(%esp,%ecx), %edx
  4f70bb:      	movl	%ecx, %eax
  4f70bd:      	movl	%edx, 0x6a4(%esp)
  4f70c4:      	movl	%edx, %ecx
  4f70c6:      	cmpl	0x344(%esp,%edx), %edi
  4f70cd:      	jge	0x4f70b7 <.text+0xf60b7>
  4f70cf:      	flds	0x14(%ebp,%edx)
  4f70d3:      	fsubs	0x14(%ebp,%eax)
  4f70d7:      	flds	0x4(%ebp,%edx)
  4f70db:      	fsubs	0x4(%ebp,%eax)
  4f70df:      	flds	0x10(%ebp,%edx)
  4f70e3:      	fsubs	0x10(%ebp,%eax)
  4f70e7:      	fxch	%st(1)
  4f70e9:      	fdivrs	0x62c808
  4f70ef:      	flds	0xc(%ebp,%edx)
  4f70f3:      	fsubs	0xc(%ebp,%eax)
  4f70f7:      	fxch	%st(1)
  4f70f9:      	fmul	%st, %st(2)
  4f70fb:      	flds	0x8(%ebp,%edx)
  4f70ff:      	fsubs	0x8(%ebp,%eax)
  4f7103:      	fxch	%st(2)
  4f7105:      	fmul	%st(1), %st
  4f7107:      	flds	(%ebp,%edx)
  4f710b:      	fsubs	(%ebp,%eax)
  4f710f:      	fxch	%st(3)
  4f7111:      	fmul	%st(2), %st
  4f7113:      	fxch	%st(4)
  4f7115:      	fstps	0x6c0(%esp)
  4f711c:      	fstps	0x6bc(%esp)
  4f7123:      	fmul	%st, %st(3)
  4f7125:      	flds	0x4(%ebp,%eax)
  4f7129:      	faddl	0x632380
  4f712f:      	fxch	%st(2)
  4f7131:      	fmulp	%st, %st(1)
  4f7133:      	fxch	%st(3)
  4f7135:      	fstps	0x6cc(%esp)
  4f713c:      	fstpl	0x648(%esp)
  4f7143:      	fstps	0x6c8(%esp)
  4f714a:      	fildl	0x648(%esp)
  4f7151:      	fxch	%st(1)
  4f7153:      	fstps	0x6c4(%esp)
  4f715a:      	fsubs	0x4(%ebp,%eax)
  4f715e:      	flds	0x6c4(%esp)
  4f7165:      	flds	0x6c8(%esp)
  4f716c:      	fmul	%st(2), %st
  4f716e:      	flds	0x6bc(%esp)
  4f7175:      	fmul	%st(3), %st
  4f7177:      	flds	0x6cc(%esp)
  4f717e:      	fmul	%st(4), %st
  4f7180:      	fxch	%st(2)
  4f7182:      	fadds	0x8(%ebp,%eax)
  4f7186:      	flds	0x6c0(%esp)
  4f718d:      	fmul	%st(5), %st
  4f718f:      	fxch	%st(2)
  4f7191:      	fadds	0xc(%ebp,%eax)
  4f7195:      	fxch	%st(4)
  4f7197:      	fmulp	%st, %st(5)
  4f7199:      	fstps	0x6ac(%esp)
  4f71a0:      	fadds	0x10(%ebp,%eax)
  4f71a4:      	fxch	%st(3)
  4f71a6:      	fadds	(%ebp,%eax)
  4f71aa:      	fxch	%st(2)
  4f71ac:      	fstps	0x6b0(%esp)
  4f71b3:      	fadds	0x14(%ebp,%eax)
  4f71b7:      	fxch	%st(2)
  4f71b9:      	fstps	0x6b4(%esp)
  4f71c0:      	fstps	0x6a8(%esp)
  4f71c7:      	fstps	0x6b8(%esp)
  4f71ce:      	flds	0x6d8(%esp)
  4f71d5:      	faddl	0x632380
  4f71db:      	flds	0x6a8(%esp)
  4f71e2:      	faddl	0x632380
  4f71e8:      	fxch	%st(1)
  4f71ea:      	fstpl	0x658(%esp)
  4f71f1:      	fstpl	0x650(%esp)
  4f71f8:      	movl	0x658(%esp), %edx
  4f71ff:      	movl	0x650(%esp), %ebx
  4f7206:      	cmpl	%edx, %ebx
  4f7208:      	je	0x4f76b8 <.text+0xf66b8>
  4f720e:      	jl	0x4f72f3 <.text+0xf62f3>
  4f7214:      	flds	0x6b8(%esp)
  4f721b:      	fsubs	0x6e8(%esp)
  4f7222:      	flds	0x6a8(%esp)
  4f7229:      	fsubs	0x6d8(%esp)
  4f7230:      	flds	0x6b4(%esp)
  4f7237:      	fsubs	0x6e4(%esp)
  4f723e:      	fxch	%st(1)
  4f7240:      	fdivrs	0x62c808
  4f7246:      	flds	0x6b0(%esp)
  4f724d:      	fsubs	0x6e0(%esp)
  4f7254:      	fxch	%st(2)
  4f7256:      	fmul	%st(1), %st
  4f7258:      	flds	0x6ac(%esp)
  4f725f:      	fsubs	0x6dc(%esp)
  4f7266:      	fxch	%st(3)
  4f7268:      	fmul	%st(2), %st
  4f726a:      	fxch	%st(1)
  4f726c:      	fstps	0x2c(%esp)
  4f7270:      	fxch	%st(1)
  4f7272:      	fmul	%st, %st(2)
  4f7274:      	fxch	%st(1)
  4f7276:      	fstps	0x28(%esp)
  4f727a:      	fmulp	%st, %st(2)
  4f727c:      	fildl	0x658(%esp)
  4f7283:      	fxch	%st(1)
  4f7285:      	fstps	0x30(%esp)
  4f7289:      	fsubs	0x6d8(%esp)
  4f7290:      	fld	%st(1)
  4f7292:      	faddl	0x632380
  4f7298:      	fxch	%st(2)
  4f729a:      	fmul	%st(1), %st
  4f729c:      	flds	0x2c(%esp)
  4f72a0:      	fxch	%st(3)
  4f72a2:      	fstpl	0x698(%esp)
  4f72a9:      	fadds	0x6e8(%esp)
  4f72b0:      	fxch	%st(2)
  4f72b2:      	flds	0x28(%esp)
  4f72b6:      	fmul	%st(2), %st
  4f72b8:      	fxch	%st(3)
  4f72ba:      	faddl	0x632380
  4f72c0:      	fxch	%st(3)
  4f72c2:      	flds	0x30(%esp)
  4f72c6:      	fmul	%st(3), %st
  4f72c8:      	fxch	%st(4)
  4f72ca:      	fstpl	0x680(%esp)
  4f72d1:      	fadds	0x6e0(%esp)
  4f72d8:      	fxch	%st(2)
  4f72da:      	fmulp	%st, %st(1)
  4f72dc:      	fxch	%st(2)
  4f72de:      	fadds	0x6dc(%esp)
  4f72e5:      	fxch	%st(2)
  4f72e7:      	fadds	0x6e4(%esp)
  4f72ee:      	jmp	0x4f73dd <.text+0xf63dd>
  4f72f3:      	movl	%ebx, 0x658(%esp)
  4f72fa:      	movl	%edx, %ebx
  4f72fc:      	movl	0x658(%esp), %edx
  4f7303:      	flds	0x6e8(%esp)
  4f730a:      	fsubs	0x6b8(%esp)
  4f7311:      	flds	0x6d8(%esp)
  4f7318:      	fsubs	0x6a8(%esp)
  4f731f:      	flds	0x6e4(%esp)
  4f7326:      	fsubs	0x6b4(%esp)
  4f732d:      	fxch	%st(1)
  4f732f:      	fdivrs	0x62c808
  4f7335:      	flds	0x6e0(%esp)
  4f733c:      	fsubs	0x6b0(%esp)
  4f7343:      	fxch	%st(2)
  4f7345:      	fmul	%st(1), %st
  4f7347:      	flds	0x6dc(%esp)
  4f734e:      	fsubs	0x6ac(%esp)
  4f7355:      	fxch	%st(3)
  4f7357:      	fmul	%st(2), %st
  4f7359:      	fxch	%st(1)
  4f735b:      	fstps	0x2c(%esp)
  4f735f:      	fxch	%st(1)
  4f7361:      	fmul	%st, %st(2)
  4f7363:      	fxch	%st(1)
  4f7365:      	fstps	0x28(%esp)
  4f7369:      	fmulp	%st, %st(2)
  4f736b:      	fildl	0x658(%esp)
  4f7372:      	fxch	%st(1)
  4f7374:      	fstps	0x30(%esp)
  4f7378:      	fsubs	0x6a8(%esp)
  4f737f:      	fld	%st(1)
  4f7381:      	faddl	0x632380
  4f7387:      	fxch	%st(2)
  4f7389:      	fmul	%st(1), %st
  4f738b:      	flds	0x2c(%esp)
  4f738f:      	fxch	%st(3)
  4f7391:      	fstpl	0x698(%esp)
  4f7398:      	fadds	0x6b8(%esp)
  4f739f:      	fxch	%st(2)
  4f73a1:      	flds	0x28(%esp)
  4f73a5:      	fmul	%st(2), %st
  4f73a7:      	fxch	%st(3)
  4f73a9:      	faddl	0x632380
  4f73af:      	fxch	%st(3)
  4f73b1:      	flds	0x30(%esp)
  4f73b5:      	fmul	%st(3), %st
  4f73b7:      	fxch	%st(4)
  4f73b9:      	fstpl	0x680(%esp)
  4f73c0:      	fadds	0x6b0(%esp)
  4f73c7:      	fxch	%st(2)
  4f73c9:      	fmulp	%st, %st(1)
  4f73cb:      	fxch	%st(2)
  4f73cd:      	fadds	0x6ac(%esp)
  4f73d4:      	fxch	%st(2)
  4f73d6:      	fadds	0x6b4(%esp)
  4f73dd:      	movl	0x698(%esp), %eax
  4f73e4:      	movl	0x20(%esp), %edi
  4f73e8:      	andl	$0xffff, %eax           # imm = 0xFFFF
  4f73ed:      	subl	%edx, %ebx
  4f73ef:      	orl	$0xfffe0000, %eax       # imm = 0xFFFE0000
  4f73f4:      	addl	%edx, %edi
  4f73f6:      	movl	%eax, 0x698(%esp)
  4f73fd:      	flds	0x28(%esp)
  4f7401:      	fmuls	0x62c814
  4f7407:      	flds	0x2c(%esp)
  4f740b:      	fmuls	0x62c814
  4f7411:      	flds	0x30(%esp)
  4f7415:      	fmuls	0x62c814
  4f741b:      	fxch	%st(2)
  4f741d:      	fstps	0x34(%esp)
  4f7421:      	fstps	0x38(%esp)
  4f7425:      	fstps	0x3c(%esp)
  4f7429:      	fxch	%st(2)
  4f742b:      	flds	0x62c80c
  4f7431:      	fdiv	%st(1), %st
  4f7433:      	fld	%st(3)
  4f7435:      	fmul	%st(1), %st
  4f7437:      	fld	%st(3)
  4f7439:      	fmulp	%st, %st(2)
  4f743b:      	faddl	0x632380
  4f7441:      	fxch	%st(1)
  4f7443:      	faddl	0x632380
  4f7449:      	fxch	%st(2)
  4f744b:      	fadds	0x3c(%esp)
  4f744f:      	fxch	%st(1)
  4f7451:      	fstpl	0x668(%esp)
  4f7458:      	fxch	%st(1)
  4f745a:      	fstpl	0x660(%esp)
  4f7461:      	flds	0x62c80c
  4f7467:      	fdiv	%st(1), %st
  4f7469:      	decl	%ebx
  4f746a:      	jmp	0x4f757b <.text+0xf657b>
  4f746f:      	flds	0x34(%esp)
  4f7473:      	faddp	%st, %st(3)
  4f7475:      	flds	0x38(%esp)
  4f7479:      	faddp	%st, %st(4)
  4f747b:      	fld	%st(2)
  4f747d:      	fmul	%st(1), %st
  4f747f:      	flds	0x3c(%esp)
  4f7483:      	fxch	%st(2)
  4f7485:      	fmul	%st(5), %st
  4f7487:      	fxch	%st(2)
  4f7489:      	faddp	%st, %st(3)
  4f748b:      	faddl	0x632380
  4f7491:      	fxch	%st(1)
  4f7493:      	faddl	0x632380
  4f7499:      	fld	%st(2)
  4f749b:      	fxch	%st(2)
  4f749d:      	fstpl	0x670(%esp)
  4f74a4:      	fstpl	0x678(%esp)
  4f74ab:      	fdivrs	0x62c80c
  4f74b1:      	movl	0x668(%esp), %ebp
  4f74b8:      	movl	0x660(%esp), %esi
  4f74bf:      	movl	0x678(%esp), %eax
  4f74c6:      	movl	0x670(%esp), %edx
  4f74cd:      	subl	%ebp, %eax
  4f74cf:      	subl	%esi, %edx
  4f74d1:      	sarl	$0x4, %eax
  4f74d4:      	movl	%ebx, 0x8(%esp)
  4f74d8:      	sarl	$0x4, %edx
  4f74db:      	movl	0x680(%esp), %ebx
  4f74e2:      	movl	%edx, 0x688(%esp)
  4f74e9:      	andl	$0xffff, %ebx           # imm = 0xFFFF
  4f74ef:      	movl	%eax, 0x690(%esp)
  4f74f6:      	orl	$0x1e0000, %ebx         # imm = 0x1E0000
  4f74fc:      	movb	(%edi), %dl
  4f74fe:      	movl	%ebp, %eax
  4f7500:      	movl	%esi, %edx
  4f7502:      	sarl	$0x10, %eax
  4f7505:      	sarl	$0x10, %edx
  4f7508:      	movl	0x1c(%esp), %ecx
  4f750c:      	andl	%ecx, %eax
  4f750e:      	movl	0x18(%esp), %ecx
  4f7512:      	andl	%ecx, %edx
  4f7514:      	movl	0x690(%esp), %ecx
  4f751b:      	addl	%ecx, %ebp
  4f751d:      	movl	0x688(%esp), %ecx
  4f7524:      	addl	%ecx, %esi
  4f7526:      	movl	0xcfdbd8(,%eax,4), %eax
  4f752d:      	movb	(%eax,%edx), %dl
  4f7530:      	cmpb	$-0x1, %dl
  4f7533:      	je	0x4f753f <.text+0xf653f>
  4f7535:      	movb	%bh, %dh
  4f7537:      	movb	0xd1e480(%edx), %al
  4f753d:      	movb	%al, (%edi)
  4f753f:      	incl	%edi
  4f7540:      	andl	$0xfffeffff, %ebx       # imm = 0xFFFEFFFF
  4f7546:      	movl	0x698(%esp), %ecx
  4f754d:      	addl	%ecx, %ebx
  4f754f:      	jge	0x4f74fe <.text+0xf64fe>
  4f7551:      	movl	%ebx, 0x680(%esp)
  4f7558:      	movl	0x8(%esp), %ebx
  4f755c:      	movl	0x670(%esp), %eax
  4f7563:      	movl	0x678(%esp), %edx
  4f756a:      	movl	%eax, 0x660(%esp)
  4f7571:      	movl	%edx, 0x668(%esp)
  4f7578:      	subl	$0x10, %ebx
  4f757b:      	cmpl	$0x10, %ebx
  4f757e:      	jge	0x4f746f <.text+0xf646f>
  4f7584:      	movl	0x680(%esp), %eax
  4f758b:      	movl	%ebx, %ecx
  4f758d:      	decl	%ebx
  4f758e:      	movl	0x668(%esp), %ebp
  4f7595:      	shll	$0x11, %ebx
  4f7598:      	andl	$0xffff, %eax           # imm = 0xFFFF
  4f759d:      	movl	0x660(%esp), %esi
  4f75a4:      	orl	%eax, %ebx
  4f75a6:      	cmpl	$0x0, %ecx
  4f75a9:      	je	0x4f7687 <.text+0xf6687>
  4f75af:      	fxch	%st(1)
  4f75b1:      	fsubs	0x3c(%esp)
  4f75b5:      	flds	0x30(%esp)
  4f75b9:      	fmuls	0x62c810(,%ecx,8)
  4f75c0:      	flds	0x28(%esp)
  4f75c4:      	fmuls	0x62c810(,%ecx,8)
  4f75cb:      	flds	0x2c(%esp)
  4f75cf:      	fmuls	0x62c810(,%ecx,8)
  4f75d6:      	fxch	%st(2)
  4f75d8:      	faddp	%st, %st(3)
  4f75da:      	faddp	%st, %st(4)
  4f75dc:      	faddp	%st, %st(4)
  4f75de:      	fdivrs	0x62c80c
  4f75e4:      	fmul	%st, %st(2)
  4f75e6:      	fildl	0x660(%esp)
  4f75ed:      	fxch	%st(1)
  4f75ef:      	fmul	%st(4), %st
  4f75f1:      	fildl	0x668(%esp)
  4f75f8:      	fxch	%st(2)
  4f75fa:      	fsubrp	%st, %st(4)
  4f75fc:      	fsubp	%st, %st(1)
  4f75fe:      	fxch	%st(2)
  4f7600:      	fmuls	0x62c814(,%ecx,8)
  4f7607:      	fxch	%st(2)
  4f7609:      	fmuls	0x62c814(,%ecx,8)
  4f7610:      	fxch	%st(2)
  4f7612:      	faddl	0x632380
  4f7618:      	fxch	%st(2)
  4f761a:      	faddl	0x632380
  4f7620:      	fxch	%st(2)
  4f7622:      	fstl	0x688(%esp)
  4f7629:      	fxch	%st(2)
  4f762b:      	fstl	0x690(%esp)
  4f7632:      	movb	(%edi), %dl
  4f7634:      	movl	%ebp, %eax
  4f7636:      	movl	%esi, %edx
  4f7638:      	sarl	$0x10, %eax
  4f763b:      	sarl	$0x10, %edx
  4f763e:      	movl	0x1c(%esp), %ecx
  4f7642:      	andl	%ecx, %eax
  4f7644:      	movl	0x18(%esp), %ecx
  4f7648:      	andl	%ecx, %edx
  4f764a:      	movl	0x690(%esp), %ecx
  4f7651:      	addl	%ecx, %ebp
  4f7653:      	movl	0x688(%esp), %ecx
  4f765a:      	addl	%ecx, %esi
  4f765c:      	movl	0xcfdbd8(,%eax,4), %eax
  4f7663:      	movb	(%eax,%edx), %dl
  4f7666:      	cmpb	$-0x1, %dl
  4f7669:      	je	0x4f7675 <.text+0xf6675>
  4f766b:      	movb	%bh, %dh
  4f766d:      	movb	0xd1e480(%edx), %al
  4f7673:      	movb	%al, (%edi)
  4f7675:      	incl	%edi
  4f7676:      	andl	$0xfffeffff, %ebx       # imm = 0xFFFEFFFF
  4f767c:      	movl	0x698(%esp), %ecx
  4f7683:      	addl	%ecx, %ebx
  4f7685:      	jge	0x4f7634 <.text+0xf6634>
  4f7687:      	sarl	$0x10, %ebp
  4f768a:      	movl	0x1c(%esp), %ecx
  4f768e:      	xorl	%edx, %edx
  4f7690:      	andl	%ecx, %ebp
  4f7692:      	sarl	$0x10, %esi
  4f7695:      	movl	0x18(%esp), %eax
  4f7699:      	movb	%bh, %dh
  4f769b:      	andl	%eax, %esi
  4f769d:      	movl	0xcfdbd8(,%ebp,4), %eax
  4f76a4:      	fcompp
  4f76a6:      	movb	(%eax,%esi), %dl
  4f76a9:      	fcompp
  4f76ab:      	cmpb	$-0x1, %dl
  4f76ae:      	je	0x4f76b8 <.text+0xf66b8>
  4f76b0:      	movb	0xd1e480(%edx), %al
  4f76b6:      	movb	%al, (%edi)
  4f76b8:      	flds	0x6b8(%esp)
  4f76bf:      	fadds	0x6cc(%esp)
  4f76c6:      	flds	0x6ac(%esp)
  4f76cd:      	fadds	0x6c8(%esp)
  4f76d4:      	flds	0x6b4(%esp)
  4f76db:      	fadds	0x6c0(%esp)
  4f76e2:      	flds	0x6b0(%esp)
  4f76e9:      	fadds	0x6bc(%esp)
  4f76f0:      	flds	0x6a8(%esp)
  4f76f7:      	fadds	0x6c4(%esp)
  4f76fe:      	fxch	%st(3)
  4f7700:      	fstps	0x6ac(%esp)
  4f7707:      	fstps	0x6b0(%esp)
  4f770e:      	fstps	0x6b4(%esp)
  4f7715:      	fstps	0x6a8(%esp)
  4f771c:      	fstps	0x6b8(%esp)
  4f7723:      	flds	0x6e8(%esp)
  4f772a:      	fadds	0x6fc(%esp)
  4f7731:      	flds	0x6dc(%esp)
  4f7738:      	fadds	0x6f8(%esp)
  4f773f:      	flds	0x6e4(%esp)
  4f7746:      	fadds	0x6f0(%esp)
  4f774d:      	flds	0x6e0(%esp)
  4f7754:      	fadds	0x6ec(%esp)
  4f775b:      	flds	0x6d8(%esp)
  4f7762:      	fadds	0x6f4(%esp)
  4f7769:      	fxch	%st(3)
  4f776b:      	fstps	0x6dc(%esp)
  4f7772:      	fstps	0x6e0(%esp)
  4f7779:      	fstps	0x6e4(%esp)
  4f7780:      	fstps	0x6d8(%esp)
  4f7787:      	fstps	0x6e8(%esp)
  4f778e:      	movl	0x20(%esp), %esi
  4f7792:      	movl	0xc(%esp), %eax
  4f7796:      	movl	(%esp), %ebp
  4f7799:      	addl	%eax, %esi
  4f779b:      	movl	0x4(%esp), %edi
  4f779f:      	movl	%esi, 0x20(%esp)
  4f77a3:      	incl	%edi
  4f77a4:      	jmp	0x4f6f60 <.text+0xf5f60>
  4f77a9:      	addl	$0x700, %esp            # imm = 0x700
  4f77af:      	popl	%ebp
  4f77b0:      	popl	%edi
  4f77b1:      	popl	%esi
  4f77b2:      	popl	%ebx
  4f77b3:      	popl	%ebp
  4f77b4:      	retl
