#ifndef RESTFUL_H_
#define RESTFUL_H_

#include <iostream>
#include <vector>
#include <map>

#include "curl.h"
#include "json.h"
#include "commontype.h"

using namespace std;

#pragma once;
#pragma comment(lib, "libcurld_imp.lib")
//#pragma comment(lib, "json_vc71_libmtd.lib")

#ifdef WIN32
#ifdef RESTFUL_EXPORTS
#define RESTFUL_API	__declspec(dllexport)
#else
#define RESTFUL_API __declspec(dllimport)
#endif
#else
#define RESTFUL_API
#endif

namespace RESTFULLSPACE
{

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

	private:
		typedef map<HTTP_HEADER_TYPE_E, string> HeaderMap;
		HeaderMap m_mapHeader;		// �����Ϣͷ

//		Json::Value m_jsBody;

		std::string m_strPutBodyData;

		std::string m_strResponseData;

		std::vector<std::string> m_vecHeaders;
	};

}

#endif