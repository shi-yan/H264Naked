# H264Naked

[![Build Status](https://travis-ci.org/shi-yan/H264Naked.svg?branch=master)](https://travis-ci.org/shi-yan/H264Naked)

A H264Naked is a data viewer for H264 video stream. While working on a video decoding project, I found that video decoders are very picky about video stream's format. For unsupported video streams, those decoders usually don't generate any errors or frames. It is difficult to debug this problem. One effective way I found is dumping raw format info and comparing it with a working video. However, there aren't many options available for dumping the H264 raw info.

H264Naked is a wrapper around libh264stream.
