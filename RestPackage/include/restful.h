#ifndef RESTFUL_H_
#define RESTFUL_H_

#include <iostream>
#include <vector>
#include <map>

#include "curl.h"

using namespace std;

#pragma once;
#pragma comment(lib, "libcurld_imp.lib")

#ifdef RESTFUL_EXPORTS
#define RESTFUL_API	__declspec(dllexport)
#else
#define RESTFUL_API __declspec(dllimport)
#endif

namespace RESTFULLSPACE
{
	typedef enum
	{
		HEADER_ACCEPT = 0,
		HEADER_ACCEPT_CHARSET,

		HEADER_IBASETOKEN,
		HEADER_NULL = 48
	}HTTP_HEADER_TYPE_E;					//Http 消息头

	typedef enum
	{
		REST_REQUEST_MODE_GET = 0,
		REST_REQUEST_MODE_POST,
		REST_REQUEST_MODE_PUT,
		REST_REQUEST_MODE_DELETE
	}REST_REQUEST_MODE_E;	//Rest消息模式

	typedef enum
	{
		REST_SUCCESS =0,
		REST_FAIL,
		REST_INVALID,
		REST_NULL = -1
	}REST_RESP_CODE_E;			//Rest返回消息码

	class RESTFUL_API RestResponse
	{
	public:
		RestResponse();
		virtual ~RestResponse();
	};

	class RESTFUL_API RestRequest
	{
	public:
		RestRequest();
		virtual ~RestRequest();

		static void RestInit();			//Rest初始化Libcurl，使用之前必须初始化
		static void RestUnInit();		//Rest去初始化Libcurl，结束使用之前必须去初始化

	public:
		// http消息头添加属性
		virtual bool HeaderAddProperty(const HTTP_HEADER_TYPE_E property, const string value);
		// http消息体添加属性
		virtual bool BodyAddProperty(const string name, const string value);
		// http发送消息
		virtual int SendRequest(const string url, const REST_REQUEST_MODE_E mode, RestResponse& response, vector<string>& vecHeaders,	bool isRecvHeader = false);

	};

}

#endif