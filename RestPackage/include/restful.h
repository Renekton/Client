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

		static void RestInit();			//Rest��ʼ��Libcurl��ʹ��֮ǰ�����ʼ��
		static void RestUnInit();		//Restȥ��ʼ��Libcurl������ʹ��֮ǰ����ȥ��ʼ��

	public:
		// http��Ϣͷ�������
		virtual bool HeaderAddProperty(const HTTP_HEADER_TYPE_E property, const string value);
		// http��Ϣ���������
		virtual bool BodyAddProperty(const string name, const string value);
		// http������Ϣ
		virtual int SendRequest(const string url, const REST_REQUEST_MODE_E requestMode, RestResponse& response, vector<string>& vecHeaders,	bool isRecvHeader = false);

	private:
		typedef map<HTTP_HEADER_TYPE_E, string> HeaderMap;
		HeaderMap m_mapHeader;		// �����Ϣͷ

		Json::Value m_jsBody;

		std::string m_strPutBodyData;

		std::string m_strResponseData;

		std::vector<std::string> m_vecHeaders;

		static size_t writeRespBodyData(const void* ptr, size_t size, size_t nmemb, void* stream);		// �ص���д������Ϣ������
		static size_t writeRespHeadData(const void* ptr, size_t size, size_t nmemb, void* stream);		// �ص���д������Ϣͷ����
		static size_t writeRespEmptyHeadData(const void* ptr, size_t size, size_t nmemb, void* stream);		// �ص��������ܷ��ص���Ϣ��дһ������Ϣͷ����
	};

}

#endif