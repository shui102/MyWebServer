#include "config.h"

Config::Config()
{
    //端口号,默认9006
    PORT = 9006;

    //日志写入方式，默认同步
    LOGWrite = 0;

    //触发组合模式,默认listenfd LT + connfd LT
    TRIGMode = 0;

    //listenfd触发模式，默认LT
    LISTENTrigmode = 0;

    //connfd触发模式，默认LT
    CONNTrigmode = 0;

    //优雅关闭链接，默认不使用
    OPT_LINGER = 0;

    //数据库连接池数量,默认8
    sql_num = 8;

    //线程池内的线程数量,默认8
    thread_num = 8;

    //关闭日志,默认不关闭
    close_log = 0;

    //并发模型,默认是proactor
    actor_model = 0;


}

void Config::display_usage(){
    printf(
        "用法: server [选项]...\n"
        "选项列表:\n"
        " -p <端口号>              设置服务器监听端口号 (默认: 9006)\n"
        " -l <日志写入方式>        设置日志写入方式 (0: 同步, 1: 异步, 默认: 0)\n"
        " -m <触发模式>            设置触发模式 (0~3, 默认: 0)\n"
        "                           0: listenfd LT + connfd LT\n"
        "                           1: listenfd LT + connfd ET\n"
        "                           2: listenfd ET + connfd LT\n"
        "                           3: listenfd ET + connfd ET\n"
        " -o <优雅关闭连接>        是否使用优雅关闭连接 (0: 不使用, 1: 使用, 默认: 0)\n"
        " -s <数据库连接数>        设置数据库连接池连接数 (默认: 8)\n"
        " -t <线程数>              设置线程池内线程数量 (默认: 8)\n"
        " -c <关闭日志>            是否关闭日志 (0: 不关闭, 1: 关闭, 默认: 0)\n"
        " -a <并发模型>            选择并发模型 (0: Proactor, 1: Reactor, 默认: 0)\n"
        " -h                      显示此帮助信息\n"
        "示例:\n"
        " server -p 8080 -t 16 -c 1\n"
    );  
}

void Config::parse_arg(int argc, char*argv[]){
    int opt;
    const char *str = "p:l:m:o:s:t:c:a:h";
    while((opt = getopt(argc, argv, str)) != -1){
        switch (opt)
        {
        case 'p':
        {
            PORT = atoi(optarg);
            printf("p = %d\n", PORT);
            break;
        }
        case 'l':
        {
            LOGWrite = atoi(optarg);
            break;
        }
        case 'm':
        {
            TRIGMode = atoi(optarg);
            break;
        }
        case 'o':
        {
            OPT_LINGER = atoi(optarg);
            break;
        }
        case 's':
        {
            sql_num = atoi(optarg);
            break;
        }
        case 't':
        {
            thread_num = atoi(optarg);
            break;
        }
        case 'c':
        {
            close_log = atoi(optarg);
            break;
        }
        case 'a':
        {
            actor_model = atoi(optarg);
            break;
        }
        case 'h':
        {
            display_usage();
            break;
        }
        default:
            break;

        }
    }
}