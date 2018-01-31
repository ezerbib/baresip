/**
 * @file gst_video_imx6/gst_video.c  Video codecs using Gstreamer 1.0
 *
 * Copyright (C) 2010 Creytiv.com
 * Copyright (C) 2014 Fadeev Alexander
 */


#include <re.h>
#include <rem.h>
#include <baresip.h>
#include <gst/gst.h>
#include "gst_video.h"


/**
 * @defgroup gst_video_imx6 gst_video_imx6
 *
 * This module implements video codecs using Gstreamer 1.0
 *
 * Currently only H.264 encoding is supported, but this can be extended
 * if needed. No decoding is done by this module, so that must be done by
 * another video-codec module.
 *
 * Thanks to Victor Sergienko and Fadeev Alexander for the
 * initial version, which was based on avcodec module.
 */


static struct vidcodec h264 = {
	.name      = "H264",
	.variant   = "packetization-mode=0",
	.encupdh   = gst_video_imx6_encoder_set,
	.ench      = gst_video_imx6_encode,
	.fmtp_ench = gst_video_imx6_fmtp_enc,
	.fmtp_cmph = gst_video_imx6_fmtp_cmp,
};


static int module_init(void)
{
	gst_init(NULL, NULL);

	vidcodec_register(baresip_vidcodecl(), &h264);

	info("gst_video_imx6: using gstreamer (%s)\n", gst_version_string());

	return 0;
}


static int module_close(void)
{
	vidcodec_unregister(&h264);

	gst_deinit();

	return 0;
}


EXPORT_SYM const struct mod_export DECL_EXPORTS(gst_video_imx6) = {
	"gst_video_imx6",
	"vidcodec",
	module_init,
	module_close
};
