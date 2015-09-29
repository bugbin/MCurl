#include "MCurl.h"
using namespace std;

pthread_mutex_t MCURL::m_count_lock = PTHREAD_MUTEX_INITIALIZER;

MCURL::MCURL()
{
    MCURL::global_init();

    pthread_mutex_lock(&MCURL::m_count_lock);
    MCURL::m_count++;
    pthread_mutex_unlock(&MCURL::m_count_lock);

    this->init();
}

MCURL::MCURL(long timeout)
{
    MCURL::global_init();

    pthread_mutex_lock(&MCURL::m_count_lock);
    MCURL::m_count++;
    pthread_mutex_unlock(&MCURL::m_count_lock);

    this->init(timeout);
}
MCURL::~MCURL()
{
    ::curl_easy_cleanup(m_curl);
    pthread_mutex_lock(&MCURL::m_count_lock);
    MCURL::m_count--;
    if(0 == MCURL::m_count){
        ::curl_global_cleanup();
    }
    pthread_mutex_unlock(&MCURL::m_count_lock);
}
void MCURL::init(long timeout)
{
    m_timeout = timeout;
    m_curl = NULL;
    m_curl = ::curl_easy_init();
    if(NULL == m_curl){
        //错误提示
        return -1;
    }
    return 0;
}

static int global_init()
{
    bool init_success = true;
    pthread_mutex_lock(&MCURL::m_count_lock);
    //TODO
    if(0 != m_count){
        int retcode = ::curl_global_init(CURL_GLOBAL_ALL);
        if(CURLE_OK != retcode){
            init_success = false;
        }
    }
    //
    pthread_mutex_unlock(&MCURL::m_count_lock);
    return (true == init_success ? 0 : -1);
}
void MCURL::resetOption(){
    ::curl_easy_reset(m_curl);
}
size_t MCURL::callback_func(void *ptr , size_t size , size_t nmemb , void *usrptr)
{
    return size * nmemb;
}

void MCURL::curl_send(string &url , string &data)
{
    resetOption();
   //TODO
   
   //
}
