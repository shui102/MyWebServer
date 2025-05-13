#include "webserver.h"

WebServer::WebServer()
{
    //http_conn类对象
    // users = new http_conn[MAX_FD];

    //root文件夹路径
    char server_path[200];
    getcwd(server_path, 200);
    char root[6] = "/root";
    m_root = (char *)malloc(strlen(server_path) + strlen(root) + 1);
    strcpy(m_root, server_path);
    strcat(m_root, root);

    //定时器
    // users_timer = new client_data[MAX_FD];
}

WebServer::~WebServer(){
    close(m_epollfd);
    close(m_listenfd);
    close(m_pipefd[1]);
    close(m_pipefd[0]);
    // delete[] users;
    // delete[] users_timer;
    // delete m_pool;
}

void WebServer::init(int port , string user, string passWord, string databaseName,
    int log_write , int opt_linger, int trigmode, int sql_num,
    int thread_num, int close_log, int actor_model)
{
    m_port = port;
    m_user = user;
    m_passWord = passWord;
    m_databaseName = databaseName;
    m_log_write = log_write;
    m_OPT_LINGER = opt_linger;
    m_TRIGMode = trigmode;
    m_sql_num = sql_num;
    m_thread_num = thread_num;
    m_close_log = close_log;
    m_actormodel = actor_model;
}

void WebServer::log_write(){
    if(m_close_log == 0){
        if(m_log_write == 1)
        {
            Log::get_instance()->init("./ServerLog", m_close_log, 2000, 800000, 800);
            // printf("m_log_write = %d", m_log_write);
        }
  
        else{
            Log::get_instance()->init("./ServerLog", m_close_log, 2000, 800000, 0);
            // printf("m_log_write = %d", m_log_write);
        }
            
    }
}