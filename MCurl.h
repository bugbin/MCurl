#ifndef _MCURL_H
#define _MCURL_H
#include <curl.h>
#include <string>
#include <pthread.h>
class MCURL{
public:
    MCURL();
    MCURL(long timeout);
    virtual ~MCURL();
    virtual void curl_send(std::string &url , std::string &data);
    virtual void resetOption();
    long m_timeout;
private:
    int init(long timeout = 0);
    inline static int global_init();

    virtual size_t callback_func(void *ptr , size_t size , size_t nmemb , void *usrptr);

    static int32_t m_count;
    static pthread_mutex_t m_count_lock;
    CURL * m_curl;
};
#endif
