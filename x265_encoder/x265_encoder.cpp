/**
The x265 encoder is designed using the x265 open source project of 
the H.265/HEVC, which is the latest video coding standard.It achieves 
a reduction in memory capacity while maintaining the almost video quality. 

Bo Liu
liubo068@hotmail.com

https://github.com/BoLiu86/x265_encoder.git
*/

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

#if defined (__cplusplus)
extern "C"
{
#include "x265.h"
};
#else
#include "x265.h"
#endif

int main(int argc, char *argv[])
{
	x265_param *pParam = nullptr;
	x265_encoder *pEncoder = nullptr;
	x265_picture *pPicInit = nullptr;

	//set code picture information
	int frame_num = 0;
	int width = 0, height = 0;
	int luma_size;
	int cspType = X265_CSP_I420;

	FILE *src_fp = nullptr;
	FILE *dst_fp = nullptr;
	char *buffer = nullptr;
	x265_nal *pNal = nullptr;
	uint32_t iNal = 0;
	int ret;

	//open original input YUV contents and the output h265 stream
	src_fp = fopen(argv[1], "rb");
	dst_fp = fopen(argv[2], "wb");

	//set video resolutions according to different videos
	if (strstr(argv[1], "2560x1600"))
		width = 2560, height = 1600;
	else if (strstr(argv[1], "1920x1080"))
		width = 1920, height = 1080;
	else if (strstr(argv[1], "832x480"))
		width = 832, height = 480;
	else if (strstr(argv[1], "416x240"))
		width = 416, height = 240;
	else if (strstr(argv[1], "1280x720"))
		width = 1280, height = 720;

	if (src_fp == nullptr || dst_fp == nullptr)
	{
		return -1;
	}

	//param alloc
	pParam = x265_param_alloc();
	x265_param_default(pParam);

	//SPS,PPS, and VPS onformation
	pParam->bRepeatHeaders = 1;
	pParam->internalCsp = cspType;
	pParam->sourceWidth = width;
	pParam->sourceHeight = height;
	pParam->fpsNum = 30;
	pParam->fpsDenom = 1; // fpsNum/fpsDenom = 25/1 = 25 fps

	//encoder initialization
	pEncoder = x265_encoder_open(pParam);
	if (pEncoder == nullptr)
	{
		printf("Fail to open the encoder.\n");
		return 0;
	}

	luma_size = pParam->sourceWidth*pParam->sourceHeight;

	pPicInit = x265_picture_alloc();
	x265_picture_init(pParam, pPicInit);

	if (cspType == X265_CSP_I420)
	{
		buffer = new char[luma_size * 3 / 2];
		pPicInit->planes[0] = buffer;
		pPicInit->planes[1] = buffer + luma_size;
		pPicInit->planes[2] = buffer + luma_size * 5 / 4;
		pPicInit->stride[0] = width;
		pPicInit->stride[1] = width / 2;
		pPicInit->stride[2] = width / 2;
	}
	else
	{
		cout << "Fail to match ColorSpace.\n" << endl;
		return -1;
	}

	//detect and set the number of frames to be encoded for encoding
	if (frame_num == 0)
	{
		fseek(src_fp, 0, SEEK_END); //set the flag at the end of the stream
		switch (cspType)
		{
		case X265_CSP_I420:
			frame_num = ftell(src_fp) / (luma_size * 3 / 2);
			break;

		default:
			cout << "Fail to match ColorSpace." << endl;
			break;
		}
		fseek(src_fp, 0, SEEK_SET);
	}
	
	//loop encoding
	for (int i = 0; i < frame_num; i++)
	{
		if (cspType == X265_CSP_I420)
		{
			fread(pPicInit->planes[0], 1, luma_size, src_fp);
			fread(pPicInit->planes[1], 1, luma_size / 4, src_fp);
			fread(pPicInit->planes[2], 1, luma_size / 4, src_fp);
		}
		else
		{
			cout << "Fail to match ColorSpace." << endl;
			return -1;
		}

		ret = x265_encoder_encode(pEncoder, &pNal, &iNal, pPicInit, NULL);
		cout << "Successd Encode " << i << "frames." << endl;

		for (int j = 0; j < iNal; j++)
		{
			fwrite(pNal[j].payload, 1, pNal[j].sizeBytes, dst_fp);
		}
	}

	//Flush encoder
	while (1)
	{
		ret = x265_encoder_encode(pEncoder, &pNal, &iNal, NULL, NULL);
		if (ret == 0)
		{
			break;
		}

		cout << "Flush 1 frame." << endl;

		for (int j = 0; j < iNal; j++)
		{
			fwrite(pNal[j].payload, 1, pNal[j].sizeBytes, dst_fp);
		}
	}

	x265_encoder_close(pEncoder);
	x265_picture_free(pPicInit);
	x265_param_free(pParam);
	delete buffer;
	fclose(src_fp);
	fclose(dst_fp);

	return 0;
}