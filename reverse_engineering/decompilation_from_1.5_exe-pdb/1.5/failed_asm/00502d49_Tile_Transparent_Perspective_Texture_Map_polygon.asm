; Entry: 00502d49
; Name: Tile_Transparent_Perspective_Texture_Map_polygon
; Signature: void Tile_Transparent_Perspective_Texture_Map_polygon(_GRAPHIC_BUFFER * param_1, POINT_3D * param_2, long param_3, POLYGON_SKIN param_4)
; Stop: 0x00503597
; Reason: Exception while decompiling 00502d49: process: timeout 
; Command: C:\Program Files\LLVM\bin\llvm-objdump.EXE -d --no-show-raw-insn --start-address=0x00502d49 --stop-address=0x00503597 C:\Users\istuart\Downloads\bzone15227\extracted\bzone.exe


C:\Users\istuart\Downloads\bzone15227\extracted\bzone.exe:	file format coff-i386

Disassembly of section .text:

00401000 <.text>:
  502d49:      	pushl	%ebp
  502d4a:      	movl	%esp, %ebp
  502d4c:      	pushl	%ebx
  502d4d:      	pushl	%esi
  502d4e:      	pushl	%edi
  502d4f:      	pushl	%ebp
  502d50:      	movl	0x14(%ebp), %ebx
  502d53:      	movl	0xcfdbc0, %eax
  502d58:      	subl	$0x6e0, %esp            # imm = 0x6E0
  502d5e:      	cmpl	%ebx, %eax
  502d60:      	je	0x502dd0 <.text+0x101dd0>
  502d62:      	movl	%ebx, 0xcfdbc0
  502d68:      	leal	0xcfdbd8, %edx
  502d6e:      	movl	(%ebx), %eax
  502d70:      	movl	0x4(%ebx), %ecx
  502d73:      	leal	0x8(%ebx), %esi
  502d76:      	movl	%ecx, 0x4(%esp)
  502d7a:      	movl	%eax, %edi
  502d7c:      	addl	$0x3, %ecx
  502d7f:      	addl	%esi, %edi
  502d81:      	leal	(%esi,%eax,2), %ebx
  502d84:      	leal	(%eax,%eax,2), %eax
  502d87:      	movl	%esi, -0x4(%edx)
  502d8a:      	movl	%esi, -0x8(%edx)
  502d8d:      	movl	%esi, -0xc(%edx)
  502d90:      	movl	%esi, -0x10(%edx)
  502d93:      	movl	%esi, (%edx)
  502d95:      	movl	%edi, 0x4(%edx)
  502d98:      	movl	%ebx, 0x8(%edx)
  502d9b:      	addl	%eax, %esi
  502d9d:      	addl	%eax, %edi
  502d9f:      	addl	%eax, %ebx
  502da1:      	addl	$0xc, %edx
  502da4:      	subl	$0x3, %ecx
  502da7:      	jge	0x502d93 <.text+0x101d93>
  502da9:      	movl	0x4(%esp), %edx
  502dad:      	movl	0xcfdbd4(,%edx,4), %eax
  502db4:      	movl	%eax, 0xcfdbd8(,%edx,4)
  502dbb:      	movl	%eax, 0xcfdbdc(,%edx,4)
  502dc2:      	movl	%eax, 0xcfdbe0(,%edx,4)
  502dc9:      	movl	%eax, 0xcfdbe4(,%edx,4)
  502dd0:      	movl	0x14(%ebp), %ebx
  502dd3:      	movl	$0x186a0, %edx          # imm = 0x186A0
  502dd8:      	movl	0xc(%ebp), %esi
  502ddb:      	movl	0x10(%ebp), %eax
  502dde:      	movl	(%ebx), %ecx
  502de0:      	movl	0x4(%ebx), %edi
  502de3:      	decl	%ecx
  502de4:      	decl	%edi
  502de5:      	fildl	0x4(%ebx)
  502de8:      	movl	%ecx, 0x18(%esp)
  502dec:      	movl	%edi, 0x1c(%esp)
  502df0:      	incl	%ecx
  502df1:      	movl	%esi, (%esp)
  502df4:      	shll	$0x3, %eax
  502df7:      	leal	0x8(%ebx), %edi
  502dfa:      	fildl	(%ebx)
  502dfc:      	movl	%ecx, 0x10(%esp)
  502e00:      	leal	(%eax,%eax,2), %ecx
  502e03:      	xorl	%eax, %eax
  502e05:      	movl	%edi, 0x24(%esp)
  502e09:      	flds	0x4(%esi,%eax)
  502e0d:      	faddl	0x632380
  502e13:      	flds	0xc(%esi,%eax)
  502e17:      	fmul	%st(2), %st
  502e19:      	flds	0x10(%esi,%eax)
  502e1d:      	fmul	%st(4), %st
  502e1f:      	fxch	%st(2)
  502e21:      	fstpl	0x648(%esp)
  502e28:      	fstps	0xc(%esi,%eax)
  502e2c:      	fstps	0x10(%esi,%eax)
  502e30:      	movl	0x648(%esp), %edi
  502e37:      	movl	%eax, 0x328(%esp,%eax)
  502e3e:      	movl	%eax, 0x58(%esp,%eax)
  502e42:      	movl	%edi, 0x344(%esp,%eax)
  502e49:      	addl	$0x18, %eax
  502e4c:      	cmpl	%edx, %edi
  502e4e:      	jg	0x502e54 <.text+0x101e54>
  502e50:      	movl	%eax, %ebx
  502e52:      	movl	%edi, %edx
  502e54:      	cmpl	%ecx, %eax
  502e56:      	jne	0x502e09 <.text+0x101e09>
  502e58:      	subl	$0x18, %ebx
  502e5b:      	leal	-0x18(%eax), %ecx
  502e5e:      	fcompp
  502e60:      	movl	$0x0, 0x328(%esp,%eax)
  502e6b:      	movl	%ecx, 0x40(%esp)
  502e6f:      	movl	0x8(%ebp), %edi
  502e72:      	movl	%ebx, 0x6b8(%esp)
  502e79:      	movl	%ebx, 0x690(%esp)
  502e80:      	movl	%ebx, 0x6bc(%esp)
  502e87:      	movl	%esi, %ebp
  502e89:      	movl	0x20(%edi), %eax
  502e8c:      	movl	(%edi), %ecx
  502e8e:      	addl	%edx, %eax
  502e90:      	movl	0x14(%edi), %esi
  502e93:      	movl	0x1c(%edi), %edi
  502e96:      	imull	%ecx
  502e98:      	addl	%edi, %esi
  502e9a:      	movl	%ecx, 0xc(%esp)
  502e9e:      	addl	%eax, %esi
  502ea0:      	movl	0x344(%esp,%ebx), %edi
  502ea7:      	movl	%esi, 0x20(%esp)
  502eab:      	movl	%ebx, 0x694(%esp)
  502eb2:      	movl	0x6bc(%esp), %ecx
  502eb9:      	movl	0x344(%esp,%ecx), %eax
  502ec0:      	movl	%edi, 0x4(%esp)
  502ec4:      	cmpl	%eax, %edi
  502ec6:      	jl	0x502fd0 <.text+0x101fd0>
  502ecc:      	movl	0x340(%esp,%ecx), %edx
  502ed3:      	movl	%ecx, %eax
  502ed5:      	movl	%edx, 0x6bc(%esp)
  502edc:      	cmpl	0x690(%esp), %edx
  502ee3:      	je	0x50358b <.text+0x10258b>
  502ee9:      	movl	0x344(%esp,%edx), %esi
  502ef0:      	movl	%edx, %ecx
  502ef2:      	cmpl	%esi, %edi
  502ef4:      	jge	0x502ecc <.text+0x101ecc>
  502ef6:      	flds	0x4(%ebp,%edx)
  502efa:      	fsubs	0x4(%ebp,%eax)
  502efe:      	flds	0x10(%ebp,%edx)
  502f02:      	fsubs	0x10(%ebp,%eax)
  502f06:      	fxch	%st(1)
  502f08:      	fdivrs	0x62c808
  502f0e:      	flds	0xc(%ebp,%edx)
  502f12:      	fsubs	0xc(%ebp,%eax)
  502f16:      	fxch	%st(1)
  502f18:      	fmul	%st, %st(2)
  502f1a:      	flds	0x8(%ebp,%edx)
  502f1e:      	fsubs	0x8(%ebp,%eax)
  502f22:      	fxch	%st(2)
  502f24:      	fmul	%st(1), %st
  502f26:      	flds	(%ebp,%edx)
  502f2a:      	fsubs	(%ebp,%eax)
  502f2e:      	fxch	%st(3)
  502f30:      	fmul	%st(2), %st
  502f32:      	fxch	%st(4)
  502f34:      	fstps	0x6d4(%esp)
  502f3b:      	flds	0x4(%ebp,%eax)
  502f3f:      	faddl	0x632380
  502f45:      	fxch	%st(3)
  502f47:      	fmulp	%st, %st(2)
  502f49:      	fstps	0x6d0(%esp)
  502f50:      	fxch	%st(1)
  502f52:      	fstpl	0x648(%esp)
  502f59:      	fstps	0x6d8(%esp)
  502f60:      	fildl	0x648(%esp)
  502f67:      	fxch	%st(1)
  502f69:      	fstps	0x6dc(%esp)
  502f70:      	fsubs	0x4(%ebp,%eax)
  502f74:      	flds	0x6d8(%esp)
  502f7b:      	flds	0x6dc(%esp)
  502f82:      	fmul	%st(2), %st
  502f84:      	flds	0x6d0(%esp)
  502f8b:      	fmul	%st(3), %st
  502f8d:      	fxch	%st(1)
  502f8f:      	fadds	0x8(%ebp,%eax)
  502f93:      	flds	0x6d4(%esp)
  502f9a:      	fmul	%st(4), %st
  502f9c:      	fxch	%st(2)
  502f9e:      	fadds	0xc(%ebp,%eax)
  502fa2:      	fxch	%st(3)
  502fa4:      	fmulp	%st, %st(4)
  502fa6:      	fstps	0x6c4(%esp)
  502fad:      	fadds	0x10(%ebp,%eax)
  502fb1:      	fxch	%st(2)
  502fb3:      	fadds	(%ebp,%eax)
  502fb7:      	fxch	%st(1)
  502fb9:      	fstps	0x6c8(%esp)
  502fc0:      	fxch	%st(1)
  502fc2:      	fstps	0x6cc(%esp)
  502fc9:      	fstps	0x6c0(%esp)
  502fd0:      	movl	0x694(%esp), %ecx
  502fd7:      	cmpl	0x344(%esp,%ecx), %edi
  502fde:      	jl	0x5030d6 <.text+0x1020d6>
  502fe4:      	movl	0x40(%esp,%ecx), %edx
  502fe8:      	movl	%ecx, %eax
  502fea:      	movl	%edx, 0x694(%esp)
  502ff1:      	movl	%edx, %ecx
  502ff3:      	cmpl	0x344(%esp,%edx), %edi
  502ffa:      	jge	0x502fe4 <.text+0x101fe4>
  502ffc:      	flds	0x4(%ebp,%edx)
  503000:      	fsubs	0x4(%ebp,%eax)
  503004:      	flds	0x10(%ebp,%edx)
  503008:      	fsubs	0x10(%ebp,%eax)
  50300c:      	fxch	%st(1)
  50300e:      	fdivrs	0x62c808
  503014:      	flds	0xc(%ebp,%edx)
  503018:      	fsubs	0xc(%ebp,%eax)
  50301c:      	fxch	%st(1)
  50301e:      	fmul	%st, %st(2)
  503020:      	flds	0x8(%ebp,%edx)
  503024:      	fsubs	0x8(%ebp,%eax)
  503028:      	fxch	%st(2)
  50302a:      	fmul	%st(1), %st
  50302c:      	flds	(%ebp,%edx)
  503030:      	fsubs	(%ebp,%eax)
  503034:      	fxch	%st(3)
  503036:      	fmul	%st(2), %st
  503038:      	fxch	%st(4)
  50303a:      	fstps	0x6ac(%esp)
  503041:      	flds	0x4(%ebp,%eax)
  503045:      	faddl	0x632380
  50304b:      	fxch	%st(3)
  50304d:      	fmulp	%st, %st(2)
  50304f:      	fstps	0x6a8(%esp)
  503056:      	fxch	%st(1)
  503058:      	fstpl	0x648(%esp)
  50305f:      	fstps	0x6b0(%esp)
  503066:      	fildl	0x648(%esp)
  50306d:      	fxch	%st(1)
  50306f:      	fstps	0x6b4(%esp)
  503076:      	fsubs	0x4(%ebp,%eax)
  50307a:      	flds	0x6b0(%esp)
  503081:      	flds	0x6b4(%esp)
  503088:      	fmul	%st(2), %st
  50308a:      	flds	0x6a8(%esp)
  503091:      	fmul	%st(3), %st
  503093:      	fxch	%st(1)
  503095:      	fadds	0x8(%ebp,%eax)
  503099:      	flds	0x6ac(%esp)
  5030a0:      	fmul	%st(4), %st
  5030a2:      	fxch	%st(2)
  5030a4:      	fadds	0xc(%ebp,%eax)
  5030a8:      	fxch	%st(3)
  5030aa:      	fmulp	%st, %st(4)
  5030ac:      	fstps	0x69c(%esp)
  5030b3:      	fadds	0x10(%ebp,%eax)
  5030b7:      	fxch	%st(2)
  5030b9:      	fadds	(%ebp,%eax)
  5030bd:      	fxch	%st(1)
  5030bf:      	fstps	0x6a0(%esp)
  5030c6:      	fxch	%st(1)
  5030c8:      	fstps	0x6a4(%esp)
  5030cf:      	fstps	0x698(%esp)
  5030d6:      	flds	0x6c0(%esp)
  5030dd:      	faddl	0x632380
  5030e3:      	flds	0x698(%esp)
  5030ea:      	faddl	0x632380
  5030f0:      	fxch	%st(1)
  5030f2:      	fstpl	0x658(%esp)
  5030f9:      	fstpl	0x650(%esp)
  503100:      	movl	0x658(%esp), %edx
  503107:      	movl	0x650(%esp), %ebx
  50310e:      	cmpl	%edx, %ebx
  503110:      	je	0x5034c4 <.text+0x1024c4>
  503116:      	jl	0x5031b8 <.text+0x1021b8>
  50311c:      	flds	0x698(%esp)
  503123:      	fsubs	0x6c0(%esp)
  50312a:      	flds	0x6a4(%esp)
  503131:      	fsubs	0x6cc(%esp)
  503138:      	fxch	%st(1)
  50313a:      	fdivrs	0x62c808
  503140:      	flds	0x6a0(%esp)
  503147:      	fsubs	0x6c8(%esp)
  50314e:      	fxch	%st(2)
  503150:      	fmul	%st(1), %st
  503152:      	flds	0x69c(%esp)
  503159:      	fsubs	0x6c4(%esp)
  503160:      	fxch	%st(3)
  503162:      	fmul	%st(2), %st
  503164:      	fxch	%st(1)
  503166:      	fstps	0x2c(%esp)
  50316a:      	fxch	%st(1)
  50316c:      	fmulp	%st, %st(2)
  50316e:      	fstps	0x28(%esp)
  503172:      	fildl	0x658(%esp)
  503179:      	fxch	%st(1)
  50317b:      	fstps	0x30(%esp)
  50317f:      	fsubs	0x6c0(%esp)
  503186:      	flds	0x2c(%esp)
  50318a:      	flds	0x28(%esp)
  50318e:      	fmul	%st(2), %st
  503190:      	flds	0x30(%esp)
  503194:      	fmul	%st(3), %st
  503196:      	fxch	%st(1)
  503198:      	fadds	0x6c8(%esp)
  50319f:      	fxch	%st(3)
  5031a1:      	fmulp	%st, %st(2)
  5031a3:      	fadds	0x6c4(%esp)
  5031aa:      	fxch	%st(1)
  5031ac:      	fadds	0x6cc(%esp)
  5031b3:      	jmp	0x50325f <.text+0x10225f>
  5031b8:      	movl	%ebx, 0x658(%esp)
  5031bf:      	movl	%edx, %ebx
  5031c1:      	movl	0x658(%esp), %edx
  5031c8:      	flds	0x6c0(%esp)
  5031cf:      	fsubs	0x698(%esp)
  5031d6:      	flds	0x6cc(%esp)
  5031dd:      	fsubs	0x6a4(%esp)
  5031e4:      	fxch	%st(1)
  5031e6:      	fdivrs	0x62c808
  5031ec:      	flds	0x6c8(%esp)
  5031f3:      	fsubs	0x6a0(%esp)
  5031fa:      	fxch	%st(2)
  5031fc:      	fmul	%st(1), %st
  5031fe:      	flds	0x6c4(%esp)
  503205:      	fsubs	0x69c(%esp)
  50320c:      	fxch	%st(3)
  50320e:      	fmul	%st(2), %st
  503210:      	fxch	%st(1)
  503212:      	fstps	0x2c(%esp)
  503216:      	fxch	%st(1)
  503218:      	fmulp	%st, %st(2)
  50321a:      	fstps	0x28(%esp)
  50321e:      	fildl	0x658(%esp)
  503225:      	fxch	%st(1)
  503227:      	fstps	0x30(%esp)
  50322b:      	fsubs	0x698(%esp)
  503232:      	flds	0x2c(%esp)
  503236:      	flds	0x28(%esp)
  50323a:      	fmul	%st(2), %st
  50323c:      	flds	0x30(%esp)
  503240:      	fmul	%st(3), %st
  503242:      	fxch	%st(1)
  503244:      	fadds	0x6a0(%esp)
  50324b:      	fxch	%st(3)
  50324d:      	fmulp	%st, %st(2)
  50324f:      	fadds	0x69c(%esp)
  503256:      	fxch	%st(1)
  503258:      	fadds	0x6a4(%esp)
  50325f:      	movl	0x20(%esp), %edi
  503263:      	subl	%edx, %ebx
  503265:      	addl	%edx, %edi
  503267:      	flds	0x28(%esp)
  50326b:      	fmuls	0x62c814
  503271:      	flds	0x2c(%esp)
  503275:      	fmuls	0x62c814
  50327b:      	flds	0x30(%esp)
  50327f:      	fmuls	0x62c814
  503285:      	fxch	%st(2)
  503287:      	fstps	0x34(%esp)
  50328b:      	fstps	0x38(%esp)
  50328f:      	fstps	0x3c(%esp)
  503293:      	fxch	%st(1)
  503295:      	flds	0x62c80c
  50329b:      	fdiv	%st(1), %st
  50329d:      	fld	%st(2)
  50329f:      	fmul	%st(1), %st
  5032a1:      	fld	%st(4)
  5032a3:      	fmulp	%st, %st(2)
  5032a5:      	faddl	0x632380
  5032ab:      	fxch	%st(1)
  5032ad:      	faddl	0x632380
  5032b3:      	fxch	%st(2)
  5032b5:      	fadds	0x3c(%esp)
  5032b9:      	fxch	%st(1)
  5032bb:      	fstpl	0x688(%esp)
  5032c2:      	fxch	%st(1)
  5032c4:      	fstpl	0x680(%esp)
  5032cb:      	fxch	%st(2)
  5032cd:      	flds	0x62c80c
  5032d3:      	fdiv	%st(3), %st
  5032d5:      	decl	%ebx
  5032d6:      	jmp	0x5033bc <.text+0x1023bc>
  5032db:      	flds	0x34(%esp)
  5032df:      	faddp	%st, %st(2)
  5032e1:      	flds	0x38(%esp)
  5032e5:      	faddp	%st, %st(3)
  5032e7:      	fld	%st(1)
  5032e9:      	fmul	%st(1), %st
  5032eb:      	flds	0x3c(%esp)
  5032ef:      	fxch	%st(2)
  5032f1:      	fmul	%st(4), %st
  5032f3:      	fxch	%st(2)
  5032f5:      	faddp	%st, %st(5)
  5032f7:      	faddl	0x632380
  5032fd:      	fxch	%st(1)
  5032ff:      	faddl	0x632380
  503305:      	fld	%st(4)
  503307:      	fxch	%st(2)
  503309:      	fstpl	0x660(%esp)
  503310:      	fstpl	0x670(%esp)
  503317:      	fdivrs	0x62c80c
  50331d:      	movl	0x688(%esp), %ebp
  503324:      	movl	0x680(%esp), %esi
  50332b:      	movl	0x670(%esp), %eax
  503332:      	movl	0x660(%esp), %edx
  503339:      	subl	%ebp, %eax
  50333b:      	subl	%esi, %edx
  50333d:      	sarl	$0x4, %eax
  503340:      	movl	%ebx, 0x8(%esp)
  503344:      	sarl	$0x4, %edx
  503347:      	movl	%eax, 0x678(%esp)
  50334e:      	movl	%edx, 0x668(%esp)
  503355:      	movl	$0x10, %ebx
  50335a:      	movb	(%edi), %dl
  50335c:      	movl	%ebp, %eax
  50335e:      	movl	0x678(%esp), %ecx
  503365:      	sarl	$0x10, %eax
  503368:      	movl	0x1c(%esp), %edx
  50336c:      	addl	%ecx, %ebp
  50336e:      	andl	%edx, %eax
  503370:      	movl	%esi, %edx
  503372:      	movl	0x668(%esp), %ecx
  503379:      	sarl	$0x10, %edx
  50337c:      	movl	0xcfdbd8(,%eax,4), %eax
  503383:      	addl	%ecx, %esi
  503385:      	movl	0x18(%esp), %ecx
  503389:      	incl	%edi
  50338a:      	andl	%ecx, %edx
  50338c:      	movb	(%eax,%edx), %al
  50338f:      	cmpb	$-0x1, %al
  503391:      	je	0x503396 <.text+0x102396>
  503393:      	movb	%al, -0x1(%edi)
  503396:      	decl	%ebx
  503397:      	jne	0x50335c <.text+0x10235c>
  503399:      	movl	0x8(%esp), %ebx
  50339d:      	movl	0x660(%esp), %eax
  5033a4:      	movl	0x670(%esp), %edx
  5033ab:      	movl	%eax, 0x680(%esp)
  5033b2:      	movl	%edx, 0x688(%esp)
  5033b9:      	subl	$0x10, %ebx
  5033bc:      	cmpl	$0x10, %ebx
  5033bf:      	jge	0x5032db <.text+0x1022db>
  5033c5:      	cmpl	$0x0, %ebx
  5033c8:      	movl	0x688(%esp), %ebp
  5033cf:      	movl	0x680(%esp), %esi
  5033d6:      	je	0x50349e <.text+0x10249e>
  5033dc:      	fxch	%st(3)
  5033de:      	fsubs	0x3c(%esp)
  5033e2:      	flds	0x30(%esp)
  5033e6:      	fmuls	0x62c810(,%ebx,8)
  5033ed:      	flds	0x28(%esp)
  5033f1:      	fmuls	0x62c810(,%ebx,8)
  5033f8:      	flds	0x2c(%esp)
  5033fc:      	fmuls	0x62c810(,%ebx,8)
  503403:      	fxch	%st(2)
  503405:      	faddp	%st, %st(3)
  503407:      	faddp	%st, %st(3)
  503409:      	faddp	%st, %st(3)
  50340b:      	fdivrs	0x62c80c
  503411:      	fmul	%st, %st(1)
  503413:      	fildl	0x680(%esp)
  50341a:      	fxch	%st(1)
  50341c:      	fmul	%st(3), %st
  50341e:      	fildl	0x688(%esp)
  503425:      	fxch	%st(2)
  503427:      	fsubrp	%st, %st(3)
  503429:      	fsubp	%st, %st(1)
  50342b:      	fxch	%st(1)
  50342d:      	fmuls	0x62c814(,%ebx,8)
  503434:      	fxch	%st(1)
  503436:      	fmuls	0x62c814(,%ebx,8)
  50343d:      	fxch	%st(1)
  50343f:      	faddl	0x632380
  503445:      	fxch	%st(1)
  503447:      	faddl	0x632380
  50344d:      	fxch	%st(1)
  50344f:      	fstl	0x668(%esp)
  503456:      	fxch	%st(1)
  503458:      	fstl	0x678(%esp)
  50345f:      	movb	(%edi), %dl
  503461:      	movl	%ebp, %eax
  503463:      	movl	0x678(%esp), %ecx
  50346a:      	sarl	$0x10, %eax
  50346d:      	movl	0x1c(%esp), %edx
  503471:      	addl	%ecx, %ebp
  503473:      	andl	%edx, %eax
  503475:      	movl	%esi, %edx
  503477:      	movl	0x668(%esp), %ecx
  50347e:      	sarl	$0x10, %edx
  503481:      	movl	0xcfdbd8(,%eax,4), %eax
  503488:      	addl	%ecx, %esi
  50348a:      	movl	0x18(%esp), %ecx
  50348e:      	incl	%edi
  50348f:      	andl	%ecx, %edx
  503491:      	movb	(%eax,%edx), %al
  503494:      	cmpb	$-0x1, %al
  503496:      	je	0x50349b <.text+0x10249b>
  503498:      	movb	%al, -0x1(%edi)
  50349b:      	decl	%ebx
  50349c:      	jne	0x503461 <.text+0x102461>
  50349e:      	sarl	$0x10, %ebp
  5034a1:      	movl	0x1c(%esp), %eax
  5034a5:      	sarl	$0x10, %esi
  5034a8:      	andl	%eax, %ebp
  5034aa:      	fcompp
  5034ac:      	movl	0x18(%esp), %ecx
  5034b0:      	movl	0xcfdbd8(,%ebp,4), %eax
  5034b7:      	andl	%ecx, %esi
  5034b9:      	fcompp
  5034bb:      	movb	(%eax,%esi), %al
  5034be:      	cmpb	$-0x1, %al
  5034c0:      	je	0x5034c4 <.text+0x1024c4>
  5034c2:      	movb	%al, (%edi)
  5034c4:      	flds	0x69c(%esp)
  5034cb:      	fadds	0x6b4(%esp)
  5034d2:      	flds	0x6a4(%esp)
  5034d9:      	fadds	0x6ac(%esp)
  5034e0:      	flds	0x6a0(%esp)
  5034e7:      	fadds	0x6a8(%esp)
  5034ee:      	flds	0x698(%esp)
  5034f5:      	fadds	0x6b0(%esp)
  5034fc:      	fxch	%st(3)
  5034fe:      	fstps	0x69c(%esp)
  503505:      	fstps	0x6a0(%esp)
  50350c:      	fstps	0x6a4(%esp)
  503513:      	fstps	0x698(%esp)
  50351a:      	flds	0x6c4(%esp)
  503521:      	fadds	0x6dc(%esp)
  503528:      	flds	0x6cc(%esp)
  50352f:      	fadds	0x6d4(%esp)
  503536:      	flds	0x6c8(%esp)
  50353d:      	fadds	0x6d0(%esp)
  503544:      	flds	0x6c0(%esp)
  50354b:      	fadds	0x6d8(%esp)
  503552:      	fxch	%st(3)
  503554:      	fstps	0x6c4(%esp)
  50355b:      	fstps	0x6c8(%esp)
  503562:      	fstps	0x6cc(%esp)
  503569:      	fstps	0x6c0(%esp)
  503570:      	movl	0x20(%esp), %esi
  503574:      	movl	0xc(%esp), %eax
  503578:      	movl	(%esp), %ebp
  50357b:      	addl	%eax, %esi
  50357d:      	movl	0x4(%esp), %edi
  503581:      	movl	%esi, 0x20(%esp)
  503585:      	incl	%edi
  503586:      	jmp	0x502eb2 <.text+0x101eb2>
  50358b:      	addl	$0x6e0, %esp            # imm = 0x6E0
  503591:      	popl	%ebp
  503592:      	popl	%edi
  503593:      	popl	%esi
  503594:      	popl	%ebx
  503595:      	popl	%ebp
  503596:      	retl
