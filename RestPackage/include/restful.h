#ifndef RESTFUL_H_
#define RESTFUL_H_

#include <iostream>
#include <vector>
#include <map>

#include "curl.h"
#include "json.h"
#include "commontype.h"

using namespace std;

namespace RESTFULLSPACE
{

	class RESTFUL_API RestResponse
	{
	public:
		RestResponse();
		virtual ~RestResponse();

	public:
		void setResponseData(std::string& value);
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
		virtual int SendRequest(const string url, const REST_REQUEST_MODE_E requestMode, RestResponse& response, vector<string>& vecHeaders,	bool isRecvHeader = false);

	private:
		typedef map<HTTP_HEADER_TYPE_E, string> HeaderMap;
		HeaderMap m_mapHeader;		// 存放消息头

		Json::Value m_jsBody;

		std::string m_strPutBodyData;

		std::string m_strResponseData;

		std::vector<std::string> m_vecHeaders;

		static size_t writeRespBodyData(const void* ptr, size_t size, size_t nmemb, void* stream);		// 回调，写返回消息体内容
		static size_t writeRespHeadData(const void* ptr, size_t size, size_t nmemb, void* stream);		// 回调，写返回消息头内容
		static size_t writeRespEmptyHeadData(const void* ptr, size_t size, size_t nmemb, void* stream);		// 回调，不接受返回的消息，写一个空消息头内容
	};

}

#endif