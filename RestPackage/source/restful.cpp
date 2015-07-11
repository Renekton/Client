#include "restful.h"

namespace RESTFULLSPACE
{

	RestResponse::RestResponse()
	{

	}

	RestResponse::~RestResponse()
	{
  
	}

	void RestResponse::setResponseData(std::string& value)
	{

	}

	RestRequest::RestRequest():m_jsBody(0)
	{
		m_mapHeader.clear();
		m_strPutBodyData.clear();
		m_strResponseData.clear();
		m_vecHeaders.clear();

		// �����Ϣͷ
		std::string tempStrHeader;

		tempStrHeader.clear();
		tempStrHeader = str_headerMap[HEADER_CONTENT_TYPE] + ":text/html;charset=utf-8";
		m_mapHeader.insert(std::make_pair<HTTP_HEADER_TYPE_E, std::string>(HEADER_CONTENT_TYPE, tempStrHeader));

		tempStrHeader.clear();
		tempStrHeader = str_headerMap[HEADER_CONNECTION] + ":Keep-Alive";
		m_mapHeader.insert(std::make_pair<HTTP_HEADER_TYPE_E, std::string>(HEADER_CONNECTION, tempStrHeader));

		tempStrHeader.clear();
		tempStrHeader = str_headerMap[HEADER_CACHE_CONTROL] + ":no-cache";
		m_mapHeader.insert(std::make_pair<HTTP_HEADER_TYPE_E, std::string>(HEADER_CACHE_CONTROL, tempStrHeader));

		tempStrHeader.clear();
		tempStrHeader = str_headerMap[HEADER_PRAGMA] + ":no-cache";
		m_mapHeader.insert(std::make_pair<HTTP_HEADER_TYPE_E, std::string>(HEADER_ACCEPT_LANGUAGE, tempStrHeader));

	}

	RestRequest::~RestRequest()
	{
		m_mapHeader.clear();
		//m_jsBody;
		m_strPutBodyData.clear();
		m_strResponseData.clear();
		m_vecHeaders.clear();
	}

	void RestRequest::RestInit()
	{
		curl_global_init(CURL_GLOBAL_DEFAULT);		// ��ʼ��libcurl
	}

	void RestRequest::RestUnInit()
	{
		curl_global_cleanup();									//ȥ��ʼ��libcurl
	}

	bool RestRequest::HeaderAddProperty(const HTTP_HEADER_TYPE_E property, const string value)
	{
		return true;
	}

	bool RestRequest::BodyAddProperty(const string name, const string value)
	{
		return true;
	}

	size_t RestRequest::writeRespBodyData(const void* ptr, size_t size, size_t nmemb, void* stream)
	{
		return 0;
	}

	size_t RestRequest::writeRespHeadData(const void* ptr, size_t size, size_t nmemb, void* stream)
	{
		return 0;
	}

	size_t RestRequest::writeRespEmptyHeadData(const void* ptr, size_t size, size_t nmemb, void* stream)
	{
		return 0;
	}

	int RestRequest::SendRequest(
		const string url, 
		const REST_REQUEST_MODE_E requestMode, 
		RestResponse& response, 
		vector<string>& vecHeaders,
		bool isRecvHeader)
	{
		CURL* hCurl = NULL;
		hCurl = curl_easy_init();			// libcurl ��ʼ��curlָ��
		if (NULL == hCurl)
		{
			return REST_NULL;
		}

		curl_easy_setopt(hCurl, CURLOPT_URL, url.c_str());	// provide the URL to use in the request
		curl_easy_setopt(hCurl, CURLOPT_SSLVERSION, CURL_SSLVERSION_TLSv1);	// set preferred TLS/SSL version; Attention: Now TLSv1 is much more in security 
		curl_easy_setopt(hCurl, CURLOPT_SSL_VERIFYPEER, 0L); // verify the peer's SSL certificate
		curl_easy_setopt(hCurl, CURLOPT_SSL_VERIFYHOST, 0L); // verify the certificate's name against host
		curl_easy_setopt(hCurl, CURLOPT_HEADER, 0L); // pass headers to the data stream

		// set headers
		struct curl_slist* ptrHeaders = NULL;	// libcurl��װHeader��ָ�룬�� headers��ӵ��˽ṹ��
		HeaderMap::iterator iter = m_mapHeader.begin();
		HeaderMap::iterator iterEnd = m_mapHeader.end();
		for ( ; iter != iterEnd; iter++)
		{
			ptrHeaders = curl_slist_append(ptrHeaders, iter->second.c_str());
		}

		int iNum = vecHeaders.size();				// �������headers�������
		for (int i=0; i< iNum; i++)
		{
			ptrHeaders = curl_slist_append(ptrHeaders, vecHeaders[i].c_str());		// �˴�ע��header �ĸ�ʽ��������Ҫת��
		}
		curl_easy_setopt(hCurl, CURLOPT_HTTPHEADER, ptrHeaders);

		curl_easy_setopt(hCurl, CURLOPT_WRITEFUNCTION, writeRespBodyData);	// ��������Ϣ��д��
		curl_easy_setopt(hCurl, CURLOPT_WRITEDATA, this);	// �ø���Ķ�����������Ϣ

		if (isRecvHeader)		// �Ƿ���ܷ��ص���Ϣͷ
		{
			curl_easy_setopt(hCurl, CURLOPT_HEADERFUNCTION, writeRespHeadData);	// �����ص���Ϣͷд��
		}
		else
		{
			curl_easy_setopt(hCurl, CURLOPT_HEADERFUNCTION, writeRespHeadData);	// �����ܷ��ص���Ϣͷ������дһ���յ���Ϣͷ
		}
		curl_easy_setopt(hCurl, CURLOPT_WRITEDATA, this);

		// set request mode
		std::string strBodyData;			// put��post���󣬸�����body
		strBodyData.clear();

		switch(requestMode)
		{
		case REST_REQUEST_MODE_GET:
			curl_easy_setopt(hCurl, CURLOPT_HTTPGET, 1L);
			break;
		case REST_REQUEST_MODE_POST:
			break;
		case REST_REQUEST_MODE_PUT:
			break;
		case REST_REQUEST_MODE_DELETE:
			break;
		default:
			curl_slist_free_all(ptrHeaders);
			curl_easy_cleanup(hCurl);
			return REST_INVALID_PARAM;
		}

		// set error response
		char errorBuffer[256];
		memset(errorBuffer, 0, 256);
		curl_easy_setopt(hCurl, CURLOPT_ERRORBUFFER, errorBuffer);

		// send the request
		CURLcode res = curl_easy_perform(hCurl);
		if (CURLE_OK != res)
		{
			if(isRecvHeader)
			{

			}

			curl_slist_free_all(ptrHeaders);
			curl_easy_cleanup(hCurl);
			
			return REST_FAIL;
		}
		//set response
		response.setResponseData(m_strResponseData);

		curl_slist_free_all(ptrHeaders);
		curl_easy_cleanup(hCurl);		// libcurl ���curlָ��
		return REST_SUCCESS;
	}
}