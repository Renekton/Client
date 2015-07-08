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
	}HTTP_HEADER_TYPE_E;					//Http ��Ϣͷ

	typedef enum
	{
		REST_REQUEST_MODE_GET = 0,
		REST_REQUEST_MODE_POST,
		REST_REQUEST_MODE_PUT,
		REST_REQUEST_MODE_DELETE
	}REST_REQUEST_MODE_E;	//Rest��Ϣģʽ

	typedef enum
	{
		REST_SUCCESS =0,
		REST_FAIL,
		REST_INVALID,
		REST_NULL = -1
	}REST_RESP_CODE_E;			//Rest������Ϣ��

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

		static void RestInit();			//Rest��ʼ��Libcurl��ʹ��֮ǰ�����ʼ��
		static void RestUnInit();		//Restȥ��ʼ��Libcurl������ʹ��֮ǰ����ȥ��ʼ��

	public:
		// http��Ϣͷ�������
		virtual bool HeaderAddProperty(const HTTP_HEADER_TYPE_E property, const string value);
		// http��Ϣ���������
		virtual bool BodyAddProperty(const string name, const string value);
		// http������Ϣ
		virtual int SendRequest(const string url, const REST_REQUEST_MODE_E mode, RestResponse& response, vector<string>& vecHeaders,	bool isRecvHeader = false);

	};

}

#endif