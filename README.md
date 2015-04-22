# H264Naked

[![Build Status](https://travis-ci.org/shi-yan/H264Naked.svg?branch=master)](https://travis-ci.org/shi-yan/H264Naked)

![screenshot](H264Naked.png)

[Mac Binary Download](builds/H264Naked_mac.zip "Download H264Naked for Mac")

A H264Naked is a raw data viewer for H264 video stream.

While working on a video decoding project, I found that video decoders are very picky about video stream's format. For unsupported video streams, those decoders usually don't generate any errors nor frames. As a result, debugging is quite difficult. One effective way I found is dumping raw frame data and comparing it with that of a working video. However, there aren't many options available for dumping the H264 raw info, therefore I wrote this tool. H264Naked is a wrapper around libh264stream.

[h264streamanalysis]http://sourceforge.net/projects/h264streamanalysis is another similar tool, but only available for windows.

For more options, see:
[h264 frame viewer question on Stackoverflow](http://stackoverflow.com/questions/6014904/h264-frame-viewer)
