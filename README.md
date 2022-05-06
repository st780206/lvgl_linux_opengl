# lvgl_linux_opengl
linux终端模式下运行lvgl并可以使用opengl



fb在启动后默认是TEXT模式，如何让fb启动默认为图形模式

framebuffer在内核启动时，默认的是以文本模式启动的（会有文本光标）
如果想以图形模式需要写应用程序时，重新设置：
int InitFrameBuffer(int* fb)
{
 struct fb_fix_screeninfo finfo;
 struct fb_var_screeninfo vinfo;
 int tty;
 //Open framebuffer device
 *fb = open ( "/dev/fb0", O_RDWR);
 if ( ! (*fb) ){
 printf("Can't open framebuffer device.\n");
 return -1;
 }
 //Get framebuffer device infomation
 if( ioctl ( *fb, FBIOGET_FSCREENINFO, &amp;finfo ) ){
 printf("Error reading fixed framebuffer information.\n");
 return -2;
 }
 fprintf(stderr, "Printing finfo:\n");
 fprintf(stderr, "tsmem_start = %p\n", (char *)finfo.smem_start);
 fprintf(stderr, "tsmem_len = %d\n", finfo.smem_len);
 fprintf(stderr, "ttype = %d\n", finfo.type);
 fprintf(stderr, "ttype_aux = %d\n", finfo.type_aux);
 fprintf(stderr, "tvisual = %d\n", finfo.visual);
 //fprintf(stderr, "txpanstep = %d\n", finfo.panstep);
 fprintf(stderr, "typanstep = %d\n", finfo.ypanstep);
 fprintf(stderr, "tywrapstep = %d\n", finfo.ywrapstep);
 fprintf(stderr, "tline_length = %d\n", finfo.line_length);
 fprintf(stderr, "tmmio_start = %p\n", (char *)finfo.mmio_start);
 fprintf(stderr, "tmmio_len = %d\n", finfo.mmio_len);
 fprintf(stderr, "taccel = %d\n", finfo.accel);

 if( ioctl ( *fb, FBIOGET_VSCREENINFO, &amp;vinfo ) ){
 printf("Error reading variable framebuffer information.\n");
 return -3;
 }
 fprintf(stderr, "Printing vinfo:\n");
 fprintf(stderr, "txres: %d\n", vinfo.xres);
 fprintf(stderr, "tyres: %d\n", vinfo.yres);
 fprintf(stderr, "txres_virtual: %d\n", vinfo.xres_virtual);
 fprintf(stderr, "tyres_virtual: %d\n", vinfo.yres_virtual);
 fprintf(stderr, "txoffset: %d\n", vinfo.xoffset);
 fprintf(stderr, "tyoffset: %d\n", vinfo.yoffset);
 fprintf(stderr, "tbits_per_pixel: %d\n", vinfo.bits_per_pixel);
 fprintf(stderr, "tgrayscale: %d\n", vinfo.grayscale);
 fprintf(stderr, "tnonstd: %d\n", vinfo.nonstd);
 fprintf(stderr, "tactivate: %d\n", vinfo.activate);
 fprintf(stderr, "theight: %d\n", vinfo.height);
 fprintf(stderr, "twidth: %d\n", vinfo.width);
 fprintf(stderr, "taccel_flags: %d\n", vinfo.accel_flags);
 fprintf(stderr, "tpixclock: %d\n", vinfo.pixclock);
 fprintf(stderr, "tleft_margin: %d\n", vinfo.left_margin);
 fprintf(stderr, "tright_margin: %d\n", vinfo.right_margin);
 fprintf(stderr, "tupper_margin: %d\n", vinfo.upper_margin);
 fprintf(stderr, "tlower_margin: %d\n", vinfo.lower_margin);
 fprintf(stderr, "thsync_len: %d\n", vinfo.hsync_len);
 fprintf(stderr, "tvsync_len: %d\n", vinfo.vsync_len);
 fprintf(stderr, "tsync: %d\n", vinfo.sync);
 fprintf(stderr, "tvmode: %d\n", vinfo.vmode);
 fprintf(stderr, " length offset\n");
 fprintf(stderr, "tred: %d/%d\n", vinfo.red.length, vinfo.red.offset);
 fprintf(stderr, "tgreen: %d/%d\n", vinfo.green.length, vinfo.green.offset);
 fprintf(stderr, "tblue: %d/%d\n", vinfo.blue.length, vinfo.blue.offset);
 fprintf(stderr, "talpha: %d/%d\n", vinfo.transp.length, vinfo.transp.offset);

 if( ( vinfo.bits_per_pixel/8 != BYTE_PER_PIXEL ) || <br> ( vinfo.xres != MAX_X ) || ( vinfo.yres != MAX_Y ) ){
 printf( "Display mode error: bits=%d x=%d y=%d\n", vinfo.width/8, vinfo.xres, vinfo.yres );
 return -4;
 }
 /*******************************************************************************************/
 /* 以下这这段就是设置fb控制台为文本模式 */
 tty = open ( "/dev/tty", O_RDONLY );
 if( !tty ){
 printf ( "Can't open /dev/tty device\n" );
 return -5;
 }

 if( ioctl( tty, KDSETMODE, KD_GRAPHICS ) ){ //KDSETMODE &lt;linux/kd.h&gt;; KD_GRAPHICS &lt;linux/kd.h&gt;
 printf ( "ioctl KDSETMODE\n" );
 return -6;
 }
 close ( tty );
 /****************************************************************************************/

 if((hzk16fp=fopen("hzk16","rb"))==NULL){
 printf ( "Can't open hzk16 file\n" );
 return -7;
 }

 if((hzk12fp=fopen("hzk12","rb"))==NULL){
 printf ( "Can't open hzk12 file\n" );
 return -8;
 }

 if((ascfp=fopen("asc1008","rb"))==NULL){
 printf ( "Can't open asc1008 file\n" );
 return -9;
 }

 fb_mem = mmap ( NULL, MAX_X*MAX_Y*BYTE_PER_PIXEL, PROT_READ|PROT_WRITE, MAP_SHARED, *fb, 0 );
 memset ( fb_mem, 0, MAX_X*MAX_Y*BYTE_PER_PIXEL );//clear screen
 return 0;

}

如果想让framebuffer启动时，默认以图形模式启动不知道该修改kernel源码哪里？

