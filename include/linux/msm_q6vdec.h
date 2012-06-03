/****************************************************************************
 ****************************************************************************
 ***
 ***   This header was automatically generated from a Linux kernel header
 ***   of the same name, to make information necessary for userspace to
 ***   call into the kernel available to libc.  It contains only constants,
 ***   structures, and macros generated from the original header, and thus,
 ***   contains no copyrightable information.
 ***
 ***   To edit the content of this header, modify the corresponding
 ***   source file (e.g. under external/kernel-headers/original/) then
 ***   run bionic/libc/kernel/tools/update_all.py
 ***
 ***   Any manual change here will be lost the next time this script will
 ***   be run. You've been warned!
 ***
 ****************************************************************************
 ****************************************************************************/
#ifndef _MSM_VDEC_H_
#define _MSM_VDEC_H_
#include <linux/types.h>
#define VDEC_IOCTL_MAGIC 'v'
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
#define VDEC_IOCTL_INITIALIZE _IOWR(VDEC_IOCTL_MAGIC, 1, struct vdec_init)
#define VDEC_IOCTL_SETBUFFERS _IOW(VDEC_IOCTL_MAGIC, 2, struct vdec_buffer)
#define VDEC_IOCTL_QUEUE _IOWR(VDEC_IOCTL_MAGIC, 3,   struct vdec_input_buf)
#define VDEC_IOCTL_REUSEFRAMEBUFFER _IOW(VDEC_IOCTL_MAGIC, 4, unsigned int)
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
#define VDEC_IOCTL_FLUSH _IOW(VDEC_IOCTL_MAGIC, 5, unsigned int)
#define VDEC_IOCTL_EOS _IO(VDEC_IOCTL_MAGIC, 6)
#define VDEC_IOCTL_GETMSG _IOR(VDEC_IOCTL_MAGIC, 7, struct vdec_msg)
#define VDEC_IOCTL_CLOSE _IO(VDEC_IOCTL_MAGIC, 8)
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
#define VDEC_IOCTL_FREEBUFFERS _IOW(VDEC_IOCTL_MAGIC, 9, struct vdec_buf_info)
#define VDEC_IOCTL_GETDECATTRIBUTES _IOR(VDEC_IOCTL_MAGIC, 10,   struct vdec_dec_attributes)
#define VDEC_IOCTL_GETVERSION _IOR(VDEC_IOCTL_MAGIC, 11, struct vdec_version)
enum {
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 VDEC_FRAME_DECODE_OK,
 VDEC_FRAME_DECODE_ERR,
 VDEC_FATAL_ERR,
 VDEC_FLUSH_FINISH,
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 VDEC_EOS,
 VDEC_FRAME_FLUSH,
 VDEC_STREAM_SWITCH,
 VDEC_SUSPEND_FINISH,
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 VDEC_BUFFER_CONSUMED
};
enum {
 VDEC_FLUSH_INPUT,
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 VDEC_FLUSH_OUTPUT,
 VDEC_FLUSH_ALL
};
enum {
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 VDEC_BUFFER_TYPE_INPUT,
 VDEC_BUFFER_TYPE_OUTPUT,
 VDEC_BUFFER_TYPE_INTERNAL1,
 VDEC_BUFFER_TYPE_INTERNAL2,
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
};
enum {
 VDEC_QUEUE_SUCCESS,
 VDEC_QUEUE_FAILED,
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 VDEC_QUEUE_BADSTATE,
};
enum {
 VDEC_COLOR_FORMAT_NV21 = 0x01,
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 VDEC_COLOR_FORMAT_NV21_YAMOTO = 0x02
 };
struct vdec_input_buf_info {
 u32 offset;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 u32 data;
 u32 size;
 int timestamp_lo;
 int timestamp_hi;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 int avsync_state;
 u32 flags;
};
struct vdec_buf_desc {
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 u32 bufsize;
 u32 num_min_buffers;
 u32 num_max_buffers;
};
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
struct vdec_buf_req {
 u32 max_input_queue_size;
 struct vdec_buf_desc input;
 struct vdec_buf_desc output;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 struct vdec_buf_desc dec_req1;
 struct vdec_buf_desc dec_req2;
};
struct vdec_region_info {
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 u32 src_id;
 u32 offset;
 u32 size;
};
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
struct vdec_config {
 u32 fourcc;
 u32 width;
 u32 height;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 u32 order;
 u32 notify_enable;
 u32 vc1_rowbase;
 u32 h264_startcode_detect;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 u32 h264_nal_len_size;
 u32 postproc_flag;
 u32 fruc_enable;
 u32 color_format;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
};
struct vdec_vc1_panscan_regions {
 int num;
 int width[4];
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 int height[4];
 int xoffset[4];
 int yoffset[4];
};
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
struct vdec_cropping_window {
 u32 x1;
 u32 y1;
 u32 x2;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 u32 y2;
};
struct vdec_frame_info {
 u32 status;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 u32 offset;
 u32 data1;
 u32 data2;
 int timestamp_lo;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 int timestamp_hi;
 int cal_timestamp_lo;
 int cal_timestamp_hi;
 u32 dec_width;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 u32 dec_height;
 struct vdec_cropping_window cwin;
 u32 picture_type[2];
 u32 picture_format;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 u32 vc1_rangeY;
 u32 vc1_rangeUV;
 u32 picture_resolution;
 u32 frame_disp_repeat;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 u32 repeat_first_field;
 u32 top_field_first;
 u32 interframe_interp;
 struct vdec_vc1_panscan_regions panscan;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 u32 concealed_macblk_num;
 u32 flags;
 u32 performance_stats;
 u32 data3;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
};
struct vdec_buf_info {
 u32 buf_type;
 struct vdec_region_info region;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 u32 num_buf;
 u32 islast;
};
struct vdec_buffer {
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 u32 pmem_id;
 struct vdec_buf_info buf;
};
struct vdec_sequence {
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 u8 *header;
 u32 len;
};
struct vdec_config_sps {
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 struct vdec_config cfg;
 struct vdec_sequence seq;
};
#define VDEC_MSG_REUSEINPUTBUFFER 1
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
#define VDEC_MSG_FRAMEDONE 2
struct vdec_msg {
 u32 id;
 union {
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 u32 buf_id;
 struct vdec_frame_info vfr_info;
 };
};
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
struct vdec_init {
 struct vdec_config_sps sps_cfg;
 struct vdec_buf_req *buf_req;
};
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
struct vdec_input_buf {
 u32 pmem_id;
 struct vdec_input_buf_info buffer;
 struct vdec_queue_status *queue_status;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
};
struct vdec_queue_status {
 u32 status;
};
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
struct vdec_dec_attributes {
 u32 fourcc;
 u32 profile;
 u32 level;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 u32 dec_pic_width;
 u32 dec_pic_height;
 struct vdec_buf_desc input;
 struct vdec_buf_desc output;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 struct vdec_buf_desc dec_req1;
 struct vdec_buf_desc dec_req2;
};
struct vdec_version {
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 u32 major;
 u32 minor;
};
#endif
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
